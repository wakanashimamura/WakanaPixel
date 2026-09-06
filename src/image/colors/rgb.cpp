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

#include "rgb.h"

#include <QtAssert>

Rgb::Rgb(std::uint32_t color)
    : m_color(color) {}

Rgb::Rgb(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) {
  setAlpha(alpha);
  setRed(red);
  setGreen(green);
  setBlue(blue);
}

bool Rgb::operator=(uint32_t color) {
  return m_color = color;
}

bool Rgb::operator!=(Rgb color) const {
  return m_color != color.m_color;
}

bool Rgb::operator==(Rgb color) const {
  return m_color == color.m_color;
}

uint8_t Rgb::color(Channel channel) const {
  switch (channel) {
    case Rgb::Alpha:
      return alpha();

    case Rgb::Red:
      return red();

    case Rgb::Green:
      return green();

    case Rgb::Blue:
      return blue();

    default:
      Q_ASSERT_X(false, Q_FUNC_INFO, "Unexpected channel value");
      break;
  }
  return 0;
}

// clang-format off
std::uint32_t Rgb::color() const        { return m_color;  }
void Rgb::setColor(std::uint32_t color) { m_color = color; }

std::uint8_t Rgb::alpha() const { return m_color >> AlphaShift & static_cast<std::uint32_t>(0xff); }
std::uint8_t Rgb::red()   const { return m_color >> RedShift   & static_cast<std::uint32_t>(0xff); }
std::uint8_t Rgb::green() const { return m_color >> GreenShift & static_cast<std::uint32_t>(0xff); }
std::uint8_t Rgb::blue()  const { return m_color >> BlueShift  & static_cast<std::uint32_t>(0xff); }

void Rgb::setAlpha(std::uint8_t alpha) { m_color = (m_color & ~(static_cast<std::uint32_t>(0xff) << AlphaShift)) | (static_cast<std::uint32_t>(alpha) << AlphaShift); }
void Rgb::setRed(std::uint8_t alpha)   { m_color = (m_color & ~(static_cast<std::uint32_t>(0xff) << RedShift))   | (static_cast<std::uint32_t>(alpha) << RedShift);   }
void Rgb::setGreen(std::uint8_t alpha) { m_color = (m_color & ~(static_cast<std::uint32_t>(0xff) << GreenShift)) | (static_cast<std::uint32_t>(alpha) << GreenShift); }
void Rgb::setBlue(std::uint8_t alpha)  { m_color = (m_color & ~(static_cast<std::uint32_t>(0xff) << BlueShift))  | (static_cast<std::uint32_t>(alpha) << BlueShift);  }
// clang-format on
