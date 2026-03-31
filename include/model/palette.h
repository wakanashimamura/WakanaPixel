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

#ifndef PALETTE_H_
#define PALETTE_H_

#include "color/lab.h"
#include "color/rgb.h"

#include <string>
#include <vector>

class Palette {
 public:
  // ----------------------------------------------------------------------------------------------
  // Enumerations
  // ----------------------------------------------------------------------------------------------

  enum class ColorDistMode { kRGB, kWeightedRGB, kLab };

  // ----------------------------------------------------------------------------------------------
  // Type aliases
  // ----------------------------------------------------------------------------------------------

  using RGBColorsType = std::vector<RGB>;
  using LabColorsType = std::vector<Lab>;

  // ----------------------------------------------------------------------------------------------
  // Constructors
  // ----------------------------------------------------------------------------------------------

  explicit Palette(const std::string& name = {});
  explicit Palette(const RGBColorsType& colors, bool labEnabled = true);
  explicit Palette(const std::string& name, const RGBColorsType& colors, bool labEnabled = true);

  // ----------------------------------------------------------------------------------------------
  // Operators
  // ----------------------------------------------------------------------------------------------

  explicit operator bool() const { return !m_colors.empty(); }

  // ------------------------------------------------------------------------------------------------
  // Search
  // ------------------------------------------------------------------------------------------------

  [[nodiscard]] RGB findNearestColor(RGB pixel, ColorDistMode mode) const;
  [[nodiscard]] RGB findNearestRGB(RGB pixel) const;
  [[nodiscard]] RGB findNearestWeightedRgb(RGB pixel) const;
  [[nodiscard]] RGB findNearestLab(RGB pixel) const;

  // ----------------------------------------------------------------------------------------------
  // Lab cache
  // ----------------------------------------------------------------------------------------------

  void enableLab();
  void disableLab();

  // ----------------------------------------------------------------------------------------------
  // Modification
  // ----------------------------------------------------------------------------------------------

  void addColor(RGB color);
  void setColor(size_t index, RGB color);

  void setPalette(const RGBColorsType& colors);
  void setPalette(const RGBColorsType& colors, bool labEnabled);
  void setPaletteWithName(const std::string& name, const RGBColorsType& colors, bool labEnabled);

  // ----------------------------------------------------------------------------------------------
  // Getters
  // ----------------------------------------------------------------------------------------------

  [[nodiscard]] const std::string& name() const { return m_name; }
  [[nodiscard]] const RGBColorsType& rgbPalette() const { return m_colors; }
  [[nodiscard]] const LabColorsType& labPalette() const { return m_labCache; }

  [[nodiscard]] RGB rgb(size_t index) const;
  [[nodiscard]] Lab lab(size_t index) const;

  [[nodiscard]] bool empty() const { return m_colors.empty(); }
  [[nodiscard]] bool labEnabled() const { return m_labEnabled; }
  [[nodiscard]] size_t size() const { return m_colors.size(); }

 private:
  std::string m_name;
  RGBColorsType m_colors;
  LabColorsType m_labCache;
  bool m_labEnabled = false;
};

#endif  // !PALETTE_H_