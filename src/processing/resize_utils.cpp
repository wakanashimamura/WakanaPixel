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

#include "resize_utils.h"

#include <algorithm>
#include <cmath>
#include <limits>

QSize resizeRect(const QSize& sourceSize, const QSize& targetSize, ResizeMode mode) {
  if (sourceSize.isEmpty() || targetSize.isEmpty())
    return {};

  switch (mode) {
    case ResizeMode::Original:
      return fitWithoutUpscaling(sourceSize, targetSize);

    case ResizeMode::Exact:
      return targetSize;

    case ResizeMode::Fit:
      return fitRect(sourceSize, targetSize);

    case ResizeMode::Fill:
      return fillRect(sourceSize, targetSize);

    case ResizeMode::Width:
      return calculateHeight(sourceSize, targetSize.width());

    case ResizeMode::Height:
      return calculateWidth(sourceSize, targetSize.height());
  }
  return {};
}

QSize fitRect(const QSize& sourceSize, const QSize& targetSize) {
  if (sourceSize.isEmpty() || targetSize.isEmpty())
    return {};

  double factorW = static_cast<double>(targetSize.width()) / sourceSize.width();
  double factorH = static_cast<double>(targetSize.height()) / sourceSize.height();

  double factor = std::min(factorW, factorH);

  QSize size;
  size.setWidth(std::round(sourceSize.width() * factor));
  size.setHeight(std::round(sourceSize.height() * factor));

  return size;
}

QSize fitWithoutUpscaling(const QSize& sourceSize, const QSize& targetSize) {
  if (sourceSize.isEmpty() || targetSize.isEmpty())
    return {};

  double factorW = static_cast<double>(targetSize.width()) / sourceSize.width();
  double factorH = static_cast<double>(targetSize.height()) / sourceSize.height();

  double factor = std::min({1.0, factorW, factorH});

  QSize size;
  size.setWidth(std::round(sourceSize.width() * factor));
  size.setHeight(std::round(sourceSize.height() * factor));

  return size;
}

QSize fillRect(const QSize& sourceSize, const QSize& targetSize) {
  if (sourceSize.isEmpty() || targetSize.isEmpty())
    return {};

  double factorW = static_cast<double>(targetSize.width()) / sourceSize.width();
  double factorH = static_cast<double>(targetSize.height()) / sourceSize.height();

  double factor = std::max(factorW, factorH);

  QSize size;
  size.setWidth(std::round(sourceSize.width() * factor));
  size.setHeight(std::round(sourceSize.height() * factor));

  return size;
}

QSize calculateHeight(const QSize& sourceSize, int width) {
  return fitRect(sourceSize, QSize(width, std::numeric_limits<int>::max()));
}

QSize calculateWidth(const QSize& sourceSize, int height) {
  return fitRect(sourceSize, QSize(std::numeric_limits<int>::max(), height));
}

CropAxis defineCropAxis(const QSize& filledSize, const QSize& targetSize) {
  Q_ASSERT_X(
      filledSize.width() == targetSize.width() || filledSize.height() == targetSize.height(),
      Q_FUNC_INFO,
      "Invalid crop sizes: at least one dimension of filledSize must match targetSize."
  );

  if (filledSize.isEmpty() || targetSize.isEmpty()) {
    return CropAxis::None;
  }

  if (filledSize == targetSize) {
    return CropAxis::None;
  }

  if (filledSize.width() == targetSize.width() && filledSize.height() > targetSize.height()) {
    return CropAxis::Vertical;
  }

  if (filledSize.width() > targetSize.width() && filledSize.height() == targetSize.height()) {
    return CropAxis::Horizontal;
  }

  return CropAxis::None;
}

int maxCropOffset(CropAxis axis, const QSize& filledSize, const QSize& targetSize) {
  Q_ASSERT_X(
      filledSize.width() == targetSize.width() || filledSize.height() == targetSize.height(),
      Q_FUNC_INFO,
      "Invalid crop sizes: at least one dimension of filledSize must match targetSize."
  );

  switch (axis) {
    case CropAxis::Horizontal:
      return filledSize.width() - targetSize.width();

    case CropAxis::Vertical:
      return filledSize.height() - targetSize.height();

    case CropAxis::None:
      return 0;

    default:
      break;
  }
  return 0;
}
