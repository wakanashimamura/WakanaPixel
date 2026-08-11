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

#include "resize_geometry.h"

#include <limits>

QSize calculateAspectFitSize(const QSize& sourceSize, const QSize& bounds) {
  if (sourceSize.isEmpty() || bounds.isEmpty())
    return {};

  double factorW = static_cast<double>(bounds.width()) / sourceSize.width();
  double factorH = static_cast<double>(bounds.height()) / sourceSize.height();

  double factor = std::min(factorW, factorH);

  QSize size;
  size.setWidth(std::round(sourceSize.width() * factor));
  size.setHeight(std::round(sourceSize.height() * factor));

  return size;
}

AspectFillResult calculateAspectFillSize(const QSize& sourceSize, const QSize& bounds) {
  if (sourceSize.isEmpty() || bounds.isEmpty())
    return {};

  double srcRatio = double(sourceSize.width()) / sourceSize.height();
  double tgtRatio = double(bounds.width()) / bounds.height();

  AspectFillResult result;

  if (srcRatio > tgtRatio) {
    result.size          = calculateWidthByHeight(sourceSize, bounds.height());
    result.fillReference = AspectFillDimension::Height;
    result.maxCropOffset = result.size.width() - bounds.width();
  } else {
    result.fillReference = AspectFillDimension::Width;
    result.size          = calculateHeightByWidth(sourceSize, bounds.width());
    result.maxCropOffset = result.size.height() - bounds.height();
  }

  return result;
}

QSize calculateWidthByHeight(const QSize& sourceSize, int height) {
  return calculateAspectFitSize(sourceSize, QSize(std::numeric_limits<int>::max(), height));
}

QSize calculateHeightByWidth(const QSize& sourceSize, int width) {
  return calculateAspectFitSize(sourceSize, QSize(width, std::numeric_limits<int>::max()));
}
