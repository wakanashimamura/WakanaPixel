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

#include "resize_geometry.h"

#include <QPainter>
#include <QPoint>
#include <QRect>

QImage resize(
    const QImage& image,
    QSize size,
    ResizeMode mode,
    ScalingAlgorithm* scaler,
    const ScalingParams* scalingParams,
    int cropOffset
) {
  switch (mode) {
    case ResizeMode::Original:
      if (image.size().width() > size.width() && image.size().height() > size.height()) {
        return resizeToFit(image, size, scaler, scalingParams);
      }
      return image;
    case ResizeMode::Exact:
      return scaler->scale(image, size, scalingParams);

    case ResizeMode::Fit:
      return resizeToFitWithPadding(image, size, scaler, scalingParams);

    case ResizeMode::Fill:
      return resizeToFill(image, size, cropOffset, scaler, scalingParams);

    case ResizeMode::Width:
      return resizeHeightByWidth(image, size.width(), scaler, scalingParams);

    case ResizeMode::Height:
      return resizeWidthByHeight(image, size.height(), scaler, scalingParams);
  }
}

QImage resizeToFitWithPadding(
    const QImage& image,
    QSize targetSize,
    ScalingAlgorithm* scaler,
    const ScalingParams* scalingParams
) {
  QSize newSize      = calculateAspectFitSize(image.size(), targetSize);
  QImage scaledImage = scaler->scale(image, newSize, scalingParams);

  QImage dstImage(targetSize, image.format());
  dstImage.fill(Qt::black);
  QPainter painter(&dstImage);

  QPoint point(
      (targetSize.width() - newSize.width()) / 2,
      (targetSize.height() - newSize.height()) / 2
  );

  painter.drawImage(point, scaledImage);
  painter.end();

  return dstImage;
}

QImage resizeToFit(
    const QImage& image,
    QSize targetSize,
    ScalingAlgorithm* scaler,
    const ScalingParams* scalingParams
) {
  QSize newSize = calculateAspectFitSize(image.size(), targetSize);
  return scaler->scale(image, newSize, scalingParams);
}

QImage resizeWidthByHeight(
    const QImage& image, int height, ScalingAlgorithm* scaler, const ScalingParams* scalingParams
) {
  QSize newSize = calculateWidthByHeight(image.size(), height);
  return scaler->scale(image, newSize, scalingParams);
}

QImage resizeHeightByWidth(
    const QImage& image, int width, ScalingAlgorithm* scaler, const ScalingParams* scalingParams
) {
  QSize newSize = calculateHeightByWidth(image.size(), width);
  return scaler->scale(image, newSize, scalingParams);
}

QImage resizeToFill(
    const QImage& image,
    QSize targetSize,
    int cropOffset,
    ScalingAlgorithm* scaler,
    const ScalingParams* scalingParams
) {
  AspectFillResult result = calculateAspectFillSize(image.size(), targetSize);

  Q_ASSERT_X(
      cropOffset <= result.maxCropOffset,
      Q_FUNC_INFO,
      "Crop offset exceeds the maximum value."
  );

  QImage scaledImage = scaler->scale(image, result.size, scalingParams);

  QImage dstImage(targetSize, image.format());
  dstImage.fill(Qt::black);

  QPainter painter(&dstImage);

  QRect rect(
      result.fillReference == AspectFillDimension::Width ? 0 : cropOffset,
      result.fillReference == AspectFillDimension::Height ? 0 : cropOffset,
      targetSize.width(),
      targetSize.height()
  );

  painter.drawImage(QPoint(), scaledImage, rect);
  painter.end();

  return dstImage;
}
