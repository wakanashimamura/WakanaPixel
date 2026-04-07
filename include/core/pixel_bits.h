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

#ifndef PIXEL_BITS_H_
#define PIXEL_BITS_H_

#include "color/rgb.h"

#include <QImage>

#include <type_traits>

enum class AccessMode { ReadWrite, ReadOnly };

template <AccessMode Mode>
class PixelBits {
 public:
  // ----------------------------------------------------------------------------------------------
  // Type aliases
  // ----------------------------------------------------------------------------------------------

  static constexpr bool kIsReadOnly = (Mode == AccessMode::ReadOnly);

  using BytePtr  = std::conditional_t<kIsReadOnly, const uchar*, uchar*>;
  using PixelPtr = std::conditional_t<kIsReadOnly, const RGB*, RGB*>;
  using ImageRef = std::conditional_t<kIsReadOnly, const QImage&, QImage&>;
  using ImagePtr = std::conditional_t<kIsReadOnly, const QImage*, QImage*>;

  // ----------------------------------------------------------------------------------------------
  // Constructors
  // ----------------------------------------------------------------------------------------------

  PixelBits() = default;

  explicit PixelBits(ImageRef image) { setImage(image); }

  template <AccessMode OtherMode,
            typename = std::enable_if_t<kIsReadOnly && OtherMode == AccessMode::ReadWrite>>
  PixelBits(const PixelBits<OtherMode>& other)
      : m_image(other.m_image),
        m_bits(other.m_bits),
        m_bytesPerLine(other.m_bytesPerLine),
        m_width(other.m_width),
        m_height(other.m_height) {}

  // ----------------------------------------------------------------------------------------------
  // Operators
  // ----------------------------------------------------------------------------------------------

  explicit operator bool() const { return isValid(); }

  [[nodiscard]] PixelPtr operator[](size_t index) {
    Q_ASSERT_X(isValid(), "BasePixelBits::operator[]", "Null pointer access detected.");
    return reinterpret_cast<PixelPtr>(m_bits + m_bytesPerLine * index);
  }

  [[nodiscard]] const RGB* operator[](size_t index) const {
    Q_ASSERT_X(isValid(), "BasePixelBits::operator[]", "Null pointer access detected.");
    return reinterpret_cast<PixelPtr>(m_bits + m_bytesPerLine * index);
  }

  // ----------------------------------------------------------------------------------------------
  // Initialization
  // ----------------------------------------------------------------------------------------------

  void setImage(ImageRef image) {
    if (image.isNull()) {
      return;
    }

    Q_ASSERT_X(image.format() == QImage::Format_RGB32 || image.format() == QImage::Format_ARGB32,
               "BasePixelBits::setImage",
               "Unsupported pixel format - pixel access will be incorrect");

    m_image        = &image;
    m_bits         = image.bits();
    m_bytesPerLine = image.bytesPerLine();
    m_width        = image.width();
    m_height       = image.height();
  }

  void reset() {
    m_image        = nullptr;
    m_bits         = nullptr;
    m_bytesPerLine = 0;
    m_width        = 0;
    m_height       = 0;
  }

  // ----------------------------------------------------------------------------------------------
  // Getters
  // ----------------------------------------------------------------------------------------------

  [[nodiscard]] bool isValid() const { return m_bits != nullptr; }

  [[nodiscard]] int width() const { return m_width; }
  [[nodiscard]] int height() const { return m_height; }

  [[nodiscard]] BytePtr bits() const { return m_bits; }
  [[nodiscard]] int bytesPerLine() const { return m_bytesPerLine; }

  [[nodiscard]] ImageRef image() { return *m_image; }
  [[nodiscard]] const QImage* image() const { return m_image; }

 private:
  template <bool>
  friend class BasePixelBits;

  ImagePtr m_image           = nullptr;
  BytePtr m_bits             = nullptr;
  std::size_t m_bytesPerLine = 0;
  int m_width                = 0;
  int m_height               = 0;
};

// ----------------------------------------------------------------------------------------------
// Type aliases
// ----------------------------------------------------------------------------------------------

using MutablePixelBits  = PixelBits<AccessMode::ReadWrite>;
using ReadOnlyPixelBits = PixelBits<AccessMode::ReadOnly>;

#endif  // !PIXEL_BITS_H_
