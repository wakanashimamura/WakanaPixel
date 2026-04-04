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

#ifndef RGB_H_
#define RGB_H_

#include <cstdint>

// #AARRGGBB

union RGB {
  // ----------------------------------------------------------------------------------------------
  // Type aliases
  // ----------------------------------------------------------------------------------------------

  using ValueType   = std::uint32_t;
  using ChannelType = std::uint8_t;

  // ----------------------------------------------------------------------------------------------
  // Enumerations
  // ----------------------------------------------------------------------------------------------

  enum class Channel { kAlpha, kRed, kGreen, kBlue };

  // ----------------------------------------------------------------------------------------------
  // Constants
  // ----------------------------------------------------------------------------------------------

  static constexpr double kMaxChannel = 255.0;

  // ----------------------------------------------------------------------------------------------
  // Data members
  // ----------------------------------------------------------------------------------------------

  ValueType argb{};

  struct {
    ChannelType blue;
    ChannelType green;
    ChannelType red;
    ChannelType alpha;
  };

  // ----------------------------------------------------------------------------------------------
  // Constructors
  // ----------------------------------------------------------------------------------------------

  RGB() = default;

  constexpr RGB(ValueType color) noexcept
      : argb(color) {}

  constexpr RGB(ChannelType red_, ChannelType green_, ChannelType blue_,
                ChannelType alpha_ = 255) noexcept
      : blue(blue_),
        green(green_),
        red(red_),
        alpha(alpha_) {}

  // ----------------------------------------------------------------------------------------------
  // Comparison operators
  // ----------------------------------------------------------------------------------------------

  [[nodiscard]] bool operator==(const RGB& other) const noexcept { return argb == other.argb; }
  [[nodiscard]] bool operator==(ValueType color) const noexcept { return argb == color; }
  [[nodiscard]] bool operator!=(const RGB& other) const noexcept { return argb != other.argb; }
  [[nodiscard]] bool operator!=(ValueType color) const noexcept { return argb != color; }

  // ----------------------------------------------------------------------------------------------
  // Channel extraction
  // ----------------------------------------------------------------------------------------------

  [[nodiscard]]
  static ChannelType color(const RGB color, Channel channel) {
    switch (channel) {
      case Channel::kRed:
        return color.red;
      case Channel::kGreen:
        return color.green;
      case Channel::kBlue:
        return color.blue;
      case Channel::kAlpha:
        return color.alpha;
    }
  }
};

// ----------------------------------------------------------------------------------------------
// Channel extraction
// ----------------------------------------------------------------------------------------------

static_assert(sizeof(RGB) == 4, "RGB must be exactly 4 bytes");

#endif  // !RGB_H_
