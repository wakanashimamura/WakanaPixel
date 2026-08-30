// ================================================================================================
//
// WakanaPixel - Software for creating digital art by converting images into pixel art.
//
// Copyright (C) 2026 Wakana Shimamura
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
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with WakanaPixel. If not, see <https://www.gnu.org/licenses/>.
//
// Repository: https://github.com/wakanashimamura/WakanaPixel
//
// ================================================================================================

#include "resize.h"

#include "resize_utils.h"

#include <QPainter>
#include <QPoint>
#include <QRect>

QImage resize(const QImage& image, const ScalingAlgorithm& scaler, ResizeParams params) {
  if (image.isNull() || params.targetSize.isEmpty()) {
    return {};
  }

  QSize size      = resizeRect(image.size(), params.targetSize, params.resizeMode);
  QImage dstImage = scaler.scale(image, size, params.roundingMode);

  if (params.resizeMode == ResizeMode::Fit) {
    return centerImageOnCanvas(dstImage, params.targetSize);
  }

  if (params.resizeMode == ResizeMode::Fill) {
    return cropImage(dstImage, params.targetSize, params.cropOffset);
  }

  return dstImage;
}

QImage centerImageOnCanvas(const QImage& image, const QSize& targetSize) {
  Q_ASSERT_X(
      image.width() == targetSize.width() || image.height() == targetSize.height(),
      Q_FUNC_INFO,
      "Invalid image sizes: at least one dimension of image size must match targetSize."
  );

  QImage dstImage(targetSize, image.format());
  dstImage.fill(Qt::black);

  QPainter painter(&dstImage);

  QPoint point(
      (targetSize.width() - image.width()) / 2,
      (targetSize.height() - image.height()) / 2
  );

  painter.drawImage(point, image);
  painter.end();

  return dstImage;
}

QImage cropImage(const QImage& image, const QSize& targetSize, int cropOffset) {
  Q_ASSERT_X(
      image.width() == targetSize.width() || image.height() == targetSize.height(),
      Q_FUNC_INFO,
      "Invalid image sizes: at least one dimension of image size must match targetSize."
  );

  CropAxis cropAxis = defineCropAxis(image.size(), targetSize);

  if (cropAxis == CropAxis::None) {
    return image;
  }

  int maxOffset    = maxCropOffset(cropAxis, image.size(), targetSize);
  const int offset = std::clamp(cropOffset, 0, maxOffset);

  QImage dstImage(targetSize, image.format());
  dstImage.fill(Qt::black);

  QPainter painter(&dstImage);

  QRect rect(
      cropAxis == CropAxis::Vertical ? 0 : offset,
      cropAxis == CropAxis::Horizontal ? 0 : offset,
      targetSize.width(),
      targetSize.height()
  );

  painter.drawImage(QPoint(), image, rect);
  painter.end();

  return dstImage;
}
