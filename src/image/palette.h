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

#include "colors/lab.h"
#include "colors/rgb.h"

#include <QString>

#include <vector>

class Palette {
 public:
  using RGBColorList = std::vector<Rgb>;
  using LabColorList = std::vector<Lab>;

  static constexpr int kMaxNameLength = 30;
  static constexpr int kMaxСolors     = 256;

  explicit Palette(const QString& name = {});
  explicit Palette(const RGBColorList& rgbList);
  explicit Palette(const QString& name, const RGBColorList& rgbList);

  explicit operator bool() const { return !m_rgbList.empty(); }

  void addColor(Rgb color);
  void setColor(int index, Rgb color);

  void setPalette(const RGBColorList& rgbList);
  void setPalette(const QString& name, const RGBColorList& rgbList);

  [[nodiscard]] const RGBColorList& rgbList() const { return m_rgbList; }
  [[nodiscard]] const LabColorList& labList() const { return m_labList; }

  [[nodiscard]] Rgb rgb(int index) const;
  [[nodiscard]] Lab lab(int index) const;

  [[nodiscard]] const QString& name() const { return m_name; }
  void setName(const QString& name);

  [[nodiscard]] bool empty() const { return m_rgbList.empty(); }
  [[nodiscard]] int size() const { return m_rgbList.size(); }

 private:
  void updateLists();

  QString m_name;

  RGBColorList m_rgbList;
  LabColorList m_labList;
};

//-----------------------------------------------
//
//

extern Palette testPalette1;

//
//
//______________________________________________
