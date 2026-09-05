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

#pragma once

#include "common/wmath.h"

#include <QSize>

enum class ResizeMode {
  Original,
  Exact,
  Fit,
  Fill,
  Width,
  Height
};

enum class CropAxis {
  Horizontal,
  Vertical,
  None
};

struct ResizeParams {
  QSize targetSize;
  ResizeMode resizeMode     = ResizeMode::Original;
  RoundingMode roundingMode = RoundingMode::Round;
  int cropOffset            = 0;

  bool operator==(const ResizeParams& other) const {
    return targetSize == other.targetSize && resizeMode == other.resizeMode &&
           roundingMode == other.roundingMode && cropOffset == other.cropOffset;
  }

  bool operator!=(const ResizeParams& other) const {
    return targetSize != other.targetSize || resizeMode != other.resizeMode ||
           roundingMode != other.roundingMode || cropOffset != other.cropOffset;
  }
};