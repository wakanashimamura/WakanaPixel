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

#include "core/dithering.h"

#include "core/pixel_bits.h"
#include "core/utils.h"

#include <vector>

// ----------------------------------------------------------------------------------------------
// NoDithering
// ----------------------------------------------------------------------------------------------

QImage NoDithering::apply(const QImage& image, const Palette& palette) {
  if (image.isNull()) {
    return image;
  }

  Q_ASSERT_X(
      image.format() == QImage::Format_RGB32 || image.format() == QImage::Format_ARGB32,
      "NearestColorDither::apply",
      "Unsupported pixel format - pixel access will be incorrect"
  );

  Q_ASSERT_X(
      palette.size() > 1,
      "NearestColorDither::apply",
      "Palette must contain at least 2 colors"
  );

  Q_ASSERT_X(m_settingsWidget, "NoDithering::apply", "Settings widget must be created before use");

  QImage result(image.size(), image.format());

  MutablePixelBits resultBits(result);
  ReadOnlyPixelBits imageBits(image);

  Palette::ColorDistMode distMode = m_settingsWidget->colorDistMode();

  for (int y = 0; y < resultBits.height(); ++y) {
    for (int x = 0; x < resultBits.width(); ++x) {
      resultBits[y][x] = palette.findNearestColor(imageBits[y][x], distMode);
    }
  }

  return result;
}

QGroupBox* NoDithering::createSettingsWidget(QWidget* parent) {
  DitheringSettingsControl* widget = new DitheringSettingsControl(displayName());

  m_settingsWidget = widget;
  return widget;
}

DitheringAlgorithm NoDithering::id() const {
  return DitheringAlgorithm::None;
}

QString NoDithering::displayName() const {
  return QString("NoDithering");
}

// ----------------------------------------------------------------------------------------------
// FloydSteinbergDithering
// ----------------------------------------------------------------------------------------------

// wikipedia Floyd–Steinberg dithering
// https://en.wikipedia.org/wiki/Floyd%E2%80%93Steinberg_dithering

// The implementation approach for this algorithm is borrowed from:
// https://github.com/turborium/Dither3/blob/main/Dither.pas

QImage FloydSteinbergDithering::apply(const QImage& image, const Palette& palette) {
  if (image.isNull()) {
    return image;
  }

  Q_ASSERT_X(
      image.format() == QImage::Format_RGB32 || image.format() == QImage::Format_ARGB32,
      "NearestColorDither::apply",
      "Unsupported pixel format - pixel access will be incorrect"
  );

  Q_ASSERT_X(
      palette.size() > 1,
      "NearestColorDither::apply",
      "Palette must contain at least 2 colors"
  );

  Q_ASSERT_X(
      m_settingsWidget,
      "FloydSteinbergDithering::apply",
      "Settings widget must be created before use"
  );

  QImage result(image.size(), image.format());

  MutablePixelBits resultBits(result);
  ReadOnlyPixelBits imageBits(image);

  DitherColorError error;
  std::vector<DitherColorError> currLineError(image.width() + 2);
  std::vector<DitherColorError> nextLineError(image.width() + 2);

  double normalizedStrength       = static_cast<double>(m_settingsWidget->strength()) / 255;
  Palette::ColorDistMode distMode = m_settingsWidget->colorDistMode();

  for (int y = 0; y < resultBits.height(); ++y) {
    for (int x = 0; x < resultBits.width(); ++x) {
      RGB pixel = imageBits[y][x];

      // clang-format off
      pixel.alpha  = 255;
      pixel.red   = clampByte(pixel.red   + (currLineError[x + 1].red   / 16) * normalizedStrength);
      pixel.green = clampByte(pixel.green + (currLineError[x + 1].green / 16) * normalizedStrength);
      pixel.blue  = clampByte(pixel.blue  + (currLineError[x + 1].blue  / 16) * normalizedStrength);
      
      RGB newPixel = palette.findNearestColor(pixel, distMode);

      resultBits[y][x] = newPixel;

      error.red   = pixel.red   - newPixel.red;
      error.green = pixel.green - newPixel.green;
      error.blue  = pixel.blue  - newPixel.blue;

      // [         |    *     | 7/17[2] ]
      // [ 3/16[0] |  5/16[1] | 1/16[2] ]
      
      // 0
      diffuseError(currLineError[x + 2], 7, error);

      // 1
      diffuseError(nextLineError[x + 0], 3, error);
      // 2
      diffuseError(nextLineError[x + 1], 5, error);
      // 3
      diffuseError(nextLineError[x + 2], 1, error);

      // clang-format on
    }
    for (int i = 0; i < currLineError.size(); ++i) {
      currLineError[i] = nextLineError[i];
      nextLineError[i] = DitherColorError();
    }
  }

  return result;
}

QGroupBox* FloydSteinbergDithering::createSettingsWidget(QWidget* parent) {
  FloydSteinbergSettingsControl* widget = new FloydSteinbergSettingsControl(displayName(), parent);

  m_settingsWidget = widget;
  return widget;
}

DitheringAlgorithm FloydSteinbergDithering::id() const {
  return DitheringAlgorithm::FloydSteinberg;
}

QString FloydSteinbergDithering::displayName() const {
  return QString("Floyd Steinberg");
}

void FloydSteinbergDithering::diffuseError(
    DitherColorError& erorr, int weight, const DitherColorError& quantError
) {
  erorr.red += weight * quantError.red;
  erorr.green += weight * quantError.green;
  erorr.blue += weight * quantError.blue;
}
