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
// https://www.baeldung.com/cs/compute-similarity-of-colours

#ifndef COLOR_DISTANCE_H_
#define COLOR_DISTANCE_H_

#include "color/lab.h"
#include "color/rgb.h"

[[nodiscard]] inline double calcColorDist(const RGB& colorA, const RGB colorW) {
  double R = colorA.red - colorW.red;
  double G = colorA.green - colorW.green;
  double B = colorA.blue - colorW.blue;

  return R * R + G * G + B * B;
}

[[nodiscard]] inline double calcWtdColorDist(const RGB& colorA, const RGB colorW) {
  double R = colorA.red - colorW.red;
  double G = colorA.green - colorW.green;
  double B = colorA.blue - colorW.blue;

  return 0.3 * (R * R) + 0.59 * (G * G) + 0.11 * (B * B);
}

[[nodiscard]] inline double calcColorDist(const Lab& colorA, const Lab& colorW) {
  double L = colorA.L - colorW.L;
  double a = colorA.a - colorW.a;
  double b = colorA.b - colorW.b;

  return L * L + a * a + b * b;
}

#endif  // !COLOR_DISTANCE_H_
