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

#include <cstdint>

//format 0xAARRGGBB

class Rgb {
 public:
  enum Channel {
    Alpha,
    Red,
    Green,
    Blue
  };

  enum Shifts {
    BlueShift  = 0,
    GreenShift = 8,
    RedShift   = 16,
    AlphaShift = 24
  };

  Rgb() = default;
  Rgb(std::uint32_t color);
  Rgb(std::uint8_t red, std::uint8_t green, std::uint8_t blue, std::uint8_t alpha = 255);

  Rgb& operator=(uint32_t color);

  bool operator!=(const Rgb& other) const;
  bool operator==(const Rgb& other) const;

  std::uint8_t color(Channel channel) const;

  std::uint32_t color() const;
  void setColor(std::uint32_t color);

  std::uint8_t alpha() const;
  std::uint8_t red() const;
  std::uint8_t green() const;
  std::uint8_t blue() const;

  void setAlpha(std::uint8_t alpha);
  void setRed(std::uint8_t red);
  void setGreen(std::uint8_t green);
  void setBlue(std::uint8_t blue);

 private:
  std::uint32_t m_color{};
};

static_assert(sizeof(Rgb) == 4, "RGB must be exactly 4 bytes");