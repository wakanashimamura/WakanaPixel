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
// XYZ to Lab
// http://www.brucelindbloom.com/index.html?Eqn_XYZ_to_Lab.html
// https://en.wikipedia.org/wiki/CIELAB_color_space#From_CIE_XYZ_to_CIELAB
// https://rgbatohex.com/tools/xyz-to-lab

#pragma once

class Rgb;
class Xyz;

class Lab {
 public:
  Lab() = default;
  Lab(double l, double a, double b);

  static Lab fromRgb(Rgb color);
  static Lab fromXyz(Xyz color);

  double l() const;
  double a() const;
  double b() const;

  void setL(double l);
  void setA(double a);
  void setB(double b);

 private:
  double m_l;
  double m_a;
  double m_b;
};
