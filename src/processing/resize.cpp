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

QImage resize(const QImage& image, const ScalingAlgorithm& scaler, ResizeParams params) {
  if (image.isNull() || params.size.isEmpty()) {
    return {};
  }

  switch (params.resizeMode) {
    case ResizeMode::Original:
      if (image.size().width() > params.size.width() &&
          image.size().height() > params.size.height()) {
        return resizeToFit(image, params.size, scaler, params.roundingMode);
      }
      return image;
    case ResizeMode::Exact:
      return scaler.scale(image, params.size, params.roundingMode);

    case ResizeMode::Fit:
      return resizeToFitWithPadding(image, params.size, scaler, params.roundingMode);

    case ResizeMode::Fill:
      return resizeToFill(image, params.size, params.cropOffset, scaler, params.roundingMode);

    case ResizeMode::Width:
      return resizeByWidth(image, params.size.width(), scaler, params.roundingMode);

    case ResizeMode::Height:
      return resizeByHeight(image, params.size.height(), scaler, params.roundingMode);
  }

  return {};
}

QImage resizeToFitWithPadding(
    const QImage& image, QSize size, const ScalingAlgorithm& scaler, const RoundingMode roundingMode
) {
  QSize newSize      = calculateAspectFitSize(image.size(), size);
  QImage scaledImage = scaler.scale(image, newSize, roundingMode);

  QImage dstImage(size, image.format());
  dstImage.fill(Qt::black);
  QPainter painter(&dstImage);

  QPoint point((size.width() - newSize.width()) / 2, (size.height() - newSize.height()) / 2);

  painter.drawImage(point, scaledImage);
  painter.end();

  return dstImage;
}

QImage resizeToFit(
    const QImage& image, QSize size, const ScalingAlgorithm& scaler, const RoundingMode roundingMode
) {
  QSize newSize = calculateAspectFitSize(image.size(), size);
  return scaler.scale(image, newSize, roundingMode);
}

QImage resizeToFill(
    const QImage& image,
    QSize size,
    int cropOffset,
    const ScalingAlgorithm& scaler,
    const RoundingMode roundingMode
) {
  AspectFillResult result     = calculateAspectFillSize(image.size(), size);
  const int boundedCropOffset = std::clamp(cropOffset, 0, result.maxCropOffset);
  QImage scaledImage          = scaler.scale(image, result.size, roundingMode);

  QImage dstImage(size, image.format());
  dstImage.fill(Qt::black);

  QPainter painter(&dstImage);

  QRect rect(
      result.fillReference == AspectFillDimension::Width ? 0 : boundedCropOffset,
      result.fillReference == AspectFillDimension::Height ? 0 : boundedCropOffset,
      size.width(),
      size.height()
  );

  painter.drawImage(QPoint(), scaledImage, rect);
  painter.end();

  return dstImage;
}

QImage resizeByWidth(
    const QImage& image, int width, const ScalingAlgorithm& scaler, const RoundingMode roundingMode
) {
  QSize newSize = calculateByWidth(image.size(), width);
  return scaler.scale(image, newSize, roundingMode);
}

QImage resizeByHeight(
    const QImage& image, int height, const ScalingAlgorithm& scaler, const RoundingMode roundingMode
) {
  QSize newSize = calculateByHeight(image.size(), height);
  return scaler.scale(image, newSize, roundingMode);
}