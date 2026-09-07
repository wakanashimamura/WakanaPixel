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

#include "xyz.h"

#include "rgb.h"

const std::array<double, 256> Xyz::linearSrgb = []() {
  // Linearize the sRGB Data
  // First, scale the sRGB data to the [0, 1] range.
  // For 8-bit data, this means dividing each value by 255.
  // The same calculation is applied to all three channels (R, G, and B),
  // generically represented as V.
  //
  //     | V / 12.92                 | if V <= 0.04045
  // V = |                           |
  //     | ((V + 0.055) / 1.055)^2.4 | otherwise
  //
  // To improve performance, create a lookup table containing precomputed
  // values for the entire 0–255 range, avoiding recalculation at runtime.

  std::array<double, 256> arr{};

  for (int i = 0; i < arr.size(); ++i) {
    double V = i / 255.0;

    if (V <= 0.04045) {
      arr[i] = V / 12.92;
    } else {
      arr[i] = std::pow((V + 0.055) / 1.055, 2.4);
    }
  }

  return arr;
}();

Xyz::Xyz(double x, double y, double z)
    : m_x(x),
      m_y(y),
      m_z(z) {}

Xyz Xyz::fromRgb(Rgb color) {
  // sRGB' to XYZ - apply transformation matrix
  // A standardized 3x3 matrix describes how to convert from sRGB' data to CIE-XYZ data.

  // |X|   | 0.4124564  0.3575761  0.1804375 | |sR|
  // |Y| = | 0.2126729  0.7151522  0.0721750 | |sG|
  // |Z|   | 0.0193339  0.1191920  0.9503041 | |sB|

  Xyz xyz;
  DoubleSRgb rgb(linearSrgb[color.red()], linearSrgb[color.green()], linearSrgb[color.blue()]);

  xyz.m_x = rgb.red * 0.4124564 + rgb.green * 0.3575761 + rgb.blue * 0.1804375;
  xyz.m_y = rgb.red * 0.2126729 + rgb.green * 0.7151522 + rgb.blue * 0.0721750;
  xyz.m_z = rgb.red * 0.0193339 + rgb.green * 0.1191920 + rgb.blue * 0.9503041;

  return xyz;
}

double Xyz::x() const {
  return m_x;
}

double Xyz::y() const {
  return m_y;
}

double Xyz::z() const {
  return m_z;
}

void Xyz::setX(double x) {
  m_x = x;
}

void Xyz::setY(double y) {
  m_y = y;
}

void Xyz::setZ(double z) {
  m_z = z;
}
