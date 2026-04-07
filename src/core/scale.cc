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

#include <vector>

QSize fitImageToScreen(QSize imageSize, QSize screenSize) {
  if (imageSize.width() > screenSize.width() || imageSize.height() > screenSize.height()) {
    double factorW = static_cast<double>(screenSize.width()) / imageSize.width();
    double factorH = static_cast<double>(screenSize.height()) / imageSize.height();

    double factor = std::min(factorW, factorH);

    QSize size;
    size.setWidth(std::round(imageSize.width() * factor));
    size.setHeight(std::round(imageSize.height() * factor));
    return size;
  }

  return imageSize;
}

QImage scale(const QImage& image, const ScaleParams& params) {
  // Return empty image if input is invali
  if (image.isNull()) {
    return image;
  }
  if (params.size.isEmpty()) {
    return QImage();
  }

  QImage result(params.size.width(), params.size.height(), image.format());

  MutablePixelBits resultBits(result);
  ReadOnlyPixelBits imageBits(image);

  // Calculate the scaling factor determine how much larger or smaller the output image will be
  double scaleY = static_cast<double>(imageBits.height()) / params.size.height();
  double scaleX = static_cast<double>(imageBits.width()) / params.size.width();

  // Precompute X-coordinates to avoid repeated calculations, improving performance.
  std::vector<int> pixelsX;
  pixelsX.reserve(params.size.width());
  for (int x = 0; x < params.size.width(); ++x) {
    // Map X coordinates to source pixels
    pixelsX.push_back(std::clamp(round(x * scaleX, params.mode), 0, imageBits.width() - 1));
  }

  for (int y = 0; y < params.size.height(); ++y) {
    // Map Y coordinates to source pixels
    int pixelY = std::clamp(round(y * scaleY, params.mode), 0, imageBits.height() - 1);

    for (int x = 0; x < params.size.width(); ++x) {
      resultBits[y][x] = imageBits[pixelY][pixelsX[x]];
    }
  }
  return result;
}

QImage upScale(const QImage& image, int factor) {
  if (factor <= 0) {
    return QImage();
  }

  return scale(image, {image.size() * factor, RoundMode::Round});
}
