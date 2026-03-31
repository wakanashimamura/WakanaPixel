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

#include "model/palette.h"

#include "color/color_distance.h"

#include <QtGlobal>

#include <limits>

// ----------------------------------------------------------------------------------------------
// Constructors
// ----------------------------------------------------------------------------------------------

Palette::Palette(const std::string& name)
    : m_name(name) {}

Palette::Palette(const RGBColorsType& colors, bool labEnabled) {
  setPalette(colors, labEnabled);
}

Palette::Palette(const std::string& name, const RGBColorsType& colors, bool labEnabled) {
  setPaletteWithName(name, colors, labEnabled);
}

// ------------------------------------------------------------------------------------------------
// Search
// ------------------------------------------------------------------------------------------------

RGB Palette::findNearestColor(RGB pixel, ColorDistMode mode) const {
  switch (mode) {
    case Palette::ColorDistMode::kRGB:
      return findNearestRGB(pixel);

    case Palette::ColorDistMode::kWeightedRGB:
      return findNearestWeightedRgb(pixel);

    case Palette::ColorDistMode::kLab:
      return findNearestLab(pixel);
  }

  return findNearestRGB(pixel);
}

RGB Palette::findNearestRGB(RGB pixel) const {
  Q_ASSERT_X(!empty(), "Palette::nearestColorRgb", "Palette is empty");

  double bestDist = std::numeric_limits<double>::max();
  RGB color;

  for (size_t i = 0; i < m_colors.size(); ++i) {
    const double dist = calcColorDist(m_colors[i], pixel);

    if (dist < bestDist) {
      bestDist = dist;
      color    = m_colors[i];
    }
  }
  return color;
}

RGB Palette::findNearestWeightedRgb(RGB pixel) const {
  Q_ASSERT_X(!empty(), "Palette::nearestColorWtdRGB", "Palette is empty");

  double bestDist = std::numeric_limits<double>::max();
  RGB color;

  for (size_t i = 0; i < m_colors.size(); ++i) {
    const double dist = calcWtdColorDist(m_colors[i], pixel);

    if (dist < bestDist) {
      bestDist = dist;
      color    = m_colors[i];
    }
  }
  return color;
}

RGB Palette::findNearestLab(RGB pixel) const {
  Q_ASSERT_X(!empty(), "Palette::nearestColorLab", "Palette is empty");
  Q_ASSERT_X(m_labEnabled, "Palette::nearestColorLab", "Lab cache is disabled");

  const Lab pixelLab(pixel);
  double bestDist = std::numeric_limits<double>::max();
  RGB color;

  for (size_t i = 0; i < m_labCache.size(); ++i) {
    const double dist = calcColorDist(m_labCache[i], pixelLab);

    if (dist < bestDist) {
      bestDist = dist;
      color    = m_colors[i];
    }
  }
  return color;
}

// ------------------------------------------------------------------------------------------------
// Lab cache
// ------------------------------------------------------------------------------------------------

void Palette::enableLab() {
  Q_ASSERT_X(!empty(), "Palette::enableLab", "Empty palette");
  m_labCache.clear();
  m_labCache.reserve(m_colors.size());
  for (const auto& rgb : m_colors) {
    m_labCache.emplace_back(rgb);
  }
  m_labEnabled = true;
}

void Palette::disableLab() {
  m_labCache.clear();
  m_labCache.shrink_to_fit();
  m_labEnabled = false;
}

// ------------------------------------------------------------------------------------------------
// Modification
// ------------------------------------------------------------------------------------------------

void Palette::addColor(RGB color) {
  m_colors.push_back(color);
  if (m_labEnabled) {
    m_labCache.emplace_back(color);
  }
}

void Palette::setColor(size_t index, RGB color) {
  Q_ASSERT_X(index < size(), "Palette::setColor", "Index out of range");

  m_colors[index] = color;
  if (m_labEnabled) {
    m_labCache[index].fromRGB(color);
  }
}

void Palette::setPalette(const RGBColorsType& colors) {
  Q_ASSERT_X(!colors.empty(), "Palette::setPalette", "Empty palette");
  m_colors = colors;

  if (m_labEnabled) {
    enableLab();
  } else {
    disableLab();
  }
}

void Palette::setPalette(const RGBColorsType& colors, bool labEnabled) {
  Q_ASSERT_X(!colors.empty(), "Palette::setPalette", "Empty palette");
  m_colors = colors;

  if (labEnabled) {
    enableLab();
  } else {
    disableLab();
  }
}

void Palette::setPaletteWithName(const std::string& name, const RGBColorsType& colors,
                                 bool labEnabled) {
  m_name = name;
  setPalette(colors, labEnabled);
}

// ------------------------------------------------------------------------------------------------
// Getters
// ------------------------------------------------------------------------------------------------

RGB Palette::rgb(size_t index) const {
  Q_ASSERT_X(index < size(), "Palette::rgb", "Index out of range");
  return m_colors[index];
}

Lab Palette::lab(size_t index) const {
  Q_ASSERT_X(m_labEnabled, "Palette::lab", "Lab cache is disabled");
  Q_ASSERT_X(index < size(), "Palette::lab", "Index out of range");
  return m_labCache[index];
}
