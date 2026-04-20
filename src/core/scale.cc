// ================================================================================================
//
// WakanaPixel - This software for creating digital art converts picture into pixel art.
//
// Copyright (C) 2026-2026 Wakana Shimamura
//
// This file is part of WakanaPixel.
//
// WakanaPixel is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// WakanaPixel is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with WakanaPixel. If not, see <https://www.gnu.org/licenses/>.
//
// https://github.com/wakanashimamura/WakanaPixel
//
// ================================================================================================

#include "core/scale.h"

#include "core/pixel_bits.h"
#include "model/settings.h"

#include <QPainter>
#include <QPoint>
#include <QRect>

#include <limits>
#include <vector>

QSize calcScaledSize(const QSize& imageSize, const QSize& screenSize) {
  double factorW = static_cast<double>(screenSize.width()) / imageSize.width();
  double factorH = static_cast<double>(screenSize.height()) / imageSize.height();

  double factor = std::min(factorW, factorH);

  QSize size;
  size.setWidth(std::round(imageSize.width() * factor));
  size.setHeight(std::round(imageSize.height() * factor));

  return size;
}

QSize calcWidthFromHeight(const QSize& imageSize, int height) {
  return calcScaledSize(imageSize, QSize(INT_MAX, height));
}

QSize calcHeightFromWidth(const QSize& imageSize, int width) {
  return calcScaledSize(imageSize, QSize(width, INT_MAX));
}

QImage scale(const QImage& image, QSize size, RoundMode mode) {
  // Return empty image if input is invali
  if (image.isNull()) {
    return image;
  }
  if (size.isEmpty()) {
    return QImage();
  }

  QImage result(size.width(), size.height(), image.format());

  MutablePixelBits resultBits(result);
  ReadOnlyPixelBits imageBits(image);

  // Calculate the scaling factor determine how much larger or smaller the output image will be
  double scaleY = static_cast<double>(imageBits.height()) / size.height();
  double scaleX = static_cast<double>(imageBits.width()) / size.width();

  // Precompute X-coordinates to avoid repeated calculations, improving performance.
  std::vector<int> pixelsX;
  pixelsX.reserve(size.width());
  for (int x = 0; x < size.width(); ++x) {
    // Map X coordinates to source pixels
    pixelsX.push_back(std::clamp(round(x * scaleX, mode), 0, imageBits.width() - 1));
  }

  for (int y = 0; y < size.height(); ++y) {
    // Map Y coordinates to source pixels
    int pixelY = std::clamp(round(y * scaleY, mode), 0, imageBits.height() - 1);

    for (int x = 0; x < size.width(); ++x) {
      resultBits[y][x] = imageBits[pixelY][pixelsX[x]];
    }
  }
  return result;
}

QImage upScale(const QImage& image, int factor) {
  if (factor <= 0) {
    return QImage();
  }
  return scale(image, image.size() * factor, RoundMode::Round);
}

DownScaleConfig buildDownScaleConfig(
    DownScaleData& data, const QSize& imageSize, const QSize& screenSize, const QSize& currentScale
) {
  DownScaleConfig config;

  config.targetSize         = currentScale;
  config.range              = screenSize;
  config.widthEnabled       = true;
  config.heightEnabled      = true;
  config.ResizeModeDisabled = true;

  switch (data.mode) {
    case DownScaleMode::Original:
      if (isOutOfBounds(imageSize, screenSize)) {
        config.targetSize = calcScaledSize(imageSize, screenSize);
      } else {
        config.targetSize = imageSize;
      }
      config.widthEnabled  = false;
      config.heightEnabled = false;
      break;

    case DownScaleMode::CustomCanvas:
      config.ResizeModeDisabled = false;
      break;

    case DownScaleMode::Width:
      config.range         = calcScaledSize(imageSize, screenSize);
      config.targetSize    = calcHeightFromWidth(imageSize, currentScale.width());
      config.widthEnabled  = true;
      config.heightEnabled = false;
      break;

    case DownScaleMode::Height:
      config.range         = calcScaledSize(imageSize, screenSize);
      config.targetSize    = calcWidthFromHeight(imageSize, currentScale.height());
      config.widthEnabled  = false;
      config.heightEnabled = true;
      break;

    case DownScaleMode::Preset:
      config.widthEnabled       = false;
      config.heightEnabled      = false;
      config.ResizeModeDisabled = false;
      config.targetSize         = data.size;
      break;

    default:
      break;
  }

  return config;
}

CropGeometry computeCropGeometry(QSize imageSize, QSize screenSize) {
  bool portrait = isPortrait(imageSize);

  QSize size = portrait ? calcHeightFromWidth(imageSize, screenSize.width())
                        : calcWidthFromHeight(imageSize, screenSize.height());

  // Scale along the other axis if the image does not fill the screen
  if (size.height() < screenSize.height()) {
    size = portrait ? calcWidthFromHeight(imageSize, screenSize.height())
                    : calcHeightFromWidth(imageSize, screenSize.width());

    return CropGeometry(
        size,
        portrait ? size.width() - screenSize.width() : size.height() - screenSize.height(),
        portrait ? CropMode::Horizontal : CropMode::Vertical
    );
  }

  return CropGeometry(
      size,
      portrait ? size.height() - screenSize.height() : size.width() - screenSize.width(),
      portrait ? CropMode::Vertical : CropMode::Horizontal
  );
}

QImage fitImage(const QImage& image, QSize screenSize, RoundMode mode) {
  QImage scaledImage = scale(image, calcScaledSize(image.size(), screenSize), mode);

  QImage result(screenSize, image.format());
  result.fill(Qt::black);

  QPainter painter(&result);

  QPoint point(
      (screenSize.width() - scaledImage.width()) / 2,
      (screenSize.height() - scaledImage.height()) / 2
  );

  painter.drawImage(point, scaledImage);
  painter.end();

  return result;
}

QImage cropImage(const QImage& image, QSize screenSize, int position, RoundMode mode) {
  CropGeometry geometry = computeCropGeometry(image.size(), screenSize);

  Q_ASSERT_X(position <= geometry.maxPosition, "cropImage", "position out of bounds");

  QRect source(
      geometry.mode == CropMode::Vertical ? 0 : position,
      geometry.mode == CropMode::Vertical ? position : 0,
      screenSize.width(),
      screenSize.height()
  );

  QImage result(screenSize, image.format());
  QPainter painter(&result);

  painter.drawImage(QPoint(), scale(image, geometry.size, mode), source);

  painter.end();

  return result;
}