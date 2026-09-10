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

#include "palette.h"

//-----------------------------------------------
//
//

extern Palette testPalette1({0xFFEAE8E3, 0xFFBAB5AB, 0xFF807D74, 0xFF565248, 0xFFC5D2C8, 0xFF83A67F,
                             0xFF5D7555, 0xFF445632, 0xFFE0B6AF, 0xFFC1665A, 0xFF884631, 0xFF663822,
                             0xFFADA7C8, 0xFF887FA3, 0xFF625B81, 0xFF494066, 0xFF9DB8D2, 0xFF7590AE,
                             0xFF4B6983, 0xFF314E6C, 0xFFEFE0CD, 0xFFE0C39E, 0xFFB39169, 0xFF826647,
                             0xFFDF421E, 0xFF990000, 0xFFEED680, 0xFFD1940C, 0xFF46A046, 0xFF267726,
                             0xFFFFFFFF, 0xFF000000});

//
//
//______________________________________________

Palette::Palette(const QString& name) {
  setName(name);
}

Palette::Palette(const RGBColorList& rgbList) {
  setPalette(rgbList);
}

Palette::Palette(const QString& name, const RGBColorList& rgbList) {
  setPalette(name, rgbList);
}

void Palette::addColor(Rgb color) {
  if (m_rgbList.size() > kMaxСolors) {
    return;
  }

  m_rgbList.push_back(color);
  m_labList.push_back(Lab::fromRgb(color));
}

void Palette::setColor(int index, Rgb color) {
  Q_ASSERT_X(index >= 0 && index < m_rgbList.size(), Q_FUNC_INFO, "Index out of bounds.");

  if (index > kMaxСolors) {
    return;
  }

  m_rgbList[index] = color;
  m_labList[index] = Lab::fromRgb(color);
}

void Palette::setPalette(const RGBColorList& rgbList) {
  if (rgbList.size() > kMaxСolors) {
    Q_ASSERT_X(true, Q_FUNC_INFO, "The provided list of colors exceeds the allowed limit");
    return;
  }

  m_rgbList = rgbList;
  updateLists();
}

void Palette::setPalette(const QString& name, const RGBColorList& rgbList) {
  if (rgbList.size() > kMaxСolors) {
    Q_ASSERT_X(true, Q_FUNC_INFO, "The provided list of colors exceeds the allowed limit");
    return;
  }

  setName(name);
  m_rgbList = rgbList;
  updateLists();
}

Rgb Palette::rgb(int index) const {
  Q_ASSERT_X(index >= 0 && index < m_rgbList.size(), Q_FUNC_INFO, "Index out of bounds.");

  return m_rgbList[index];
}

Lab Palette::lab(int index) const {
  Q_ASSERT_X(index >= 0 && index < m_labList.size(), Q_FUNC_INFO, "Index out of bounds.");

  return m_labList[index];
}

void Palette::setName(const QString& name) {
  if (name.size() <= kMaxNameLength) {
    m_name = name;
  } else {
    m_name = name.mid(0, kMaxNameLength);
  }
}

void Palette::updateLists() {
  m_labList.clear();

  for (const auto& color : m_rgbList) {
    m_labList.push_back(Lab::fromRgb(color));
  }
}
