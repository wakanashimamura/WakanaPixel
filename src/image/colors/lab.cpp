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

#include "lab.h"

#include "rgb.h"
#include "xyz.h"

#include <algorithm>

Lab::Lab(double l, double a, double b) {
  setL(l);
  setA(a);
  setB(b);
}

Lab Lab::fromRgb(Rgb color) {
  return fromXyz(Xyz::fromRgb(color));
}

Lab Lab::fromXyz(Xyz color) {
  // Step 1: Normalize XYZ values with D65 illuminant
  // Values ​​taken from https://en.wikipedia.org/wiki/CIELAB_color_space#From_CIE_XYZ_to_CIELAB
  // 
  // Xr = X / 0.950489
  // Yr = Y / 1.000000
  // Zr = Z / 1.088840
  //
  // Step 2: Apply nonlinear transformation
  // The same calculation is applied to all three channels (Xr, Yr, and Zr),
  // generically represented as t.
  //
  //        | t^(1/3)            | if t > E
  // f(t) = |                    |
  //        | (K * t + 16) / 116 | otherwise
  //
  // E = 216/24389 = 0.008856
  // K = 24389/27  = 903.3
  //
  // Step 3: Calculate LAB values
  //
  // l = 116 * f(Y) - 16
  // a = 500 * (f(X) - f(Y))
  // b = 200 * (f(Y) - f(Z))

  auto f = [](double t) {
    if (t > 216.0 / 24389.0) {
      return std::cbrt(t);
    } else {
      return (24389.0 / 27.0 * t + 16.0) / 116.0;
    }
  };

  double fX = f(color.x() / 0.950489);
  double fY = f(color.y() / 1.000000);
  double fZ = f(color.z() / 1.088840);

  Lab lab;

  lab.m_l = 116.0 * fY - 16;
  lab.m_a = 500.0 * (fX - fY);
  lab.m_b = 200.0 * (fY - fZ);

  return lab;
}

double Lab::l() const {
  return m_l;
}

double Lab::a() const {
  return m_a;
}

double Lab::b() const {
  return m_b;
}

void Lab::setL(double l) {
  m_l = std::clamp(l, 0.0, 100.0);
}

void Lab::setA(double a) {
  m_a = std::clamp(a, -128.0, 127.0);
}

void Lab::setB(double b) {
  m_b = std::clamp(b, -128.0, 127.0);
}
