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
// https://kaizoudou.com/from-rgb-to-lab-color-space/

#ifndef LAB_H_
#define LAB_H_

#include "color/rgb.h"

#include <array>
#include <cmath>

class Lab {
 public:
  // ----------------------------------------------------------------------------------------------
  // Data members
  // ----------------------------------------------------------------------------------------------

  double L{};
  double a{};
  double b{};

  // ----------------------------------------------------------------------------------------------
  // Constructors
  // ----------------------------------------------------------------------------------------------

  Lab() = default;
  Lab(double L, double a, double b)
      : L(L),
        a(a),
        b(b) {}
  explicit Lab(RGB rgb) { fromRGB(rgb); }

  // ----------------------------------------------------------------------------------------------
  // ----------------------------------------------------------------------------------------------

  void fromRGB(RGB rgb) {
    const auto& lut = linearLut();

    double r = lut[rgb.red];
    double g = lut[rgb.green];
    double b = lut[rgb.blue];

    double X = r * 0.4124564 + g * 0.3575761 + b * 0.1804375;
    double Y = r * 0.2126729 + g * 0.7151522 + b * 0.0721750;
    double Z = r * 0.0193339 + g * 0.1191920 + b * 0.9503041;

    double fx = labF(X / 0.95047);
    double fy = labF(Y / 1.00000);
    double fz = labF(Z / 1.08883);

    this->L = 116.0 * fy - 16.0;
    this->a = 500.0 * (fx - fy);
    this->b = 200.0 * (fy - fz);
  }

 private:
  [[nodiscard]] static const std::array<double, 256>& linearLut() {
    static const std::array<double, 256> lut = [] {
      std::array<double, 256> arr{};
      for (int i = 0; i < 256; ++i) {
        double c = i / RGB::kMaxChannel;
        arr[i]   = (c <= 0.04045) ? c / 12.92 : std::pow((c + 0.055) / 1.055, 2.4);
      }
      return arr;
    }();
    return lut;
  }

  [[nodiscard]] static inline double labF(double t) {
    return (t > 0.008856) ? std::cbrt(t) : (7.787 * t + 16.0 / 116.0);
  }
};

#endif  // !LAB_H_