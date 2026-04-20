// ================================================================================================
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

#ifndef UTILS_H_
#define UTILS_H_

#include <QSize>

#include <cmath>
#include <cstdint>

enum class RoundMode { Floor, Round, Ceil };

[[nodiscard]] inline int round(double value, RoundMode mode) {
  switch (mode) {
    case RoundMode::Floor:
      return static_cast<int>(std::floor(value));
    case RoundMode::Round:
      return static_cast<int>(std::round(value));
    case RoundMode::Ceil:
      return static_cast<int>(std::ceil(value));
    default:
      return value;
  }
}

[[nodiscard]] inline uint8_t clampByte(int value) {
  if (value > 255) {
    return 255;
  } else if (value < 0) {
    return 0;
  }

  return value;
}

[[nodiscard]] inline int square(int value) {
  return value * value;
}

[[nodiscard]] inline double square(double value) {
  return value * value;
}

[[nodiscard]] inline int cube(int value) {
  return value * value * value;
}

[[nodiscard]] inline double cube(double value) {
  return value * value * value;
}

[[nodiscard]] inline bool isOutOfBounds(QSize imageSize, QSize boundsSize) {
  return imageSize.width() > boundsSize.width() || imageSize.height() > boundsSize.height();
}

[[nodiscard]] inline bool isPortrait(QSize imageSize) {
  return imageSize.height() >= imageSize.width();
}

#endif  // !UTILS_H_
