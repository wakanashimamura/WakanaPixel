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
// Formula how to convert between sRGB and CIE-XYZ
// https://www.image-engineering.de/en/resources/tech-notes/convert-between-srgb-and-ciexyz/

#pragma once

#include <array>
#include <cmath>

class Rgb;

class Xyz {
 public:
  Xyz() = default;
  Xyz(double x, double y, double z);

  static Xyz fromRgb(Rgb color);

  double x() const;
  double y() const;
  double z() const;

  void setX(double x);
  void setY(double y);
  void setZ(double z);

 private:
  struct DoubleSRgb {
    DoubleSRgb() = default;

    DoubleSRgb(double red_, double green_, double blue_)
        : red(red_),
          green(green_),
          blue(blue_) {}

    double red{};
    double green{};
    double blue{};
  };

  static const std::array<double, 256> linearSrgb;

  double m_x{};
  double m_y{};
  double m_z{};
};
