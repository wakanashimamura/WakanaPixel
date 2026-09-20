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

extern Palette testPalette2(
    {0xFF000000, 0xFF800000, 0xFF008000, 0xFF808000, 0xFF000080, 0xFF800080, 0xFF008080, 0xFFC0C0C0,
     0xFFC0DCC0, 0xFFA6CAF0, 0xFF2A3FAA, 0xFF2A3FFF, 0xFF2A5F00, 0xFF2A5F55, 0xFF2A5FAA, 0xFF2A5FFF,
     0xFF2A7F00, 0xFF2A7F55, 0xFF2A7FAA, 0xFF2A7FFF, 0xFF2A9F00, 0xFF2A9F55, 0xFF2A9FAA, 0xFF2A9FFF,
     0xFF2ABF00, 0xFF2ABF55, 0xFF2ABFAA, 0xFF2ABFFF, 0xFF2ADF00, 0xFF2ADF55, 0xFF2ADFAA, 0xFF2ADFFF,
     0xFF2AFF00, 0xFF2AFF55, 0xFF2AFFAA, 0xFF2AFFFF, 0xFF550000, 0xFF550055, 0xFF5500AA, 0xFF5500FF,
     0xFF551F00, 0xFF551F55, 0xFF551FAA, 0xFF551FFF, 0xFF553F00, 0xFF553F55, 0xFF553FAA, 0xFF553FFF,
     0xFF555F00, 0xFF555F55, 0xFF555FAA, 0xFF555FFF, 0xFF557F00, 0xFF557F55, 0xFF557FAA, 0xFF557FFF,
     0xFF559F00, 0xFF559F55, 0xFF559FAA, 0xFF559FFF, 0xFF55BF00, 0xFF55BF55, 0xFF55BFAA, 0xFF55BFFF,
     0xFF55DF00, 0xFF55DF55, 0xFF55DFAA, 0xFF55DFFF, 0xFF55FF00, 0xFF55FF55, 0xFF55FFAA, 0xFF55FFFF,
     0xFF7F0000, 0xFF7F0055, 0xFF7F00AA, 0xFF7F00FF, 0xFF7F1F00, 0xFF7F1F55, 0xFF7F1FAA, 0xFF7F1FFF,
     0xFF7F3F00, 0xFF7F3F55, 0xFF7F3FAA, 0xFF7F3FFF, 0xFF7F5F00, 0xFF7F5F55, 0xFF7F5FAA, 0xFF7F5FFF,
     0xFF7F7F00, 0xFF7F7F55, 0xFF7F7FAA, 0xFF7F7FFF, 0xFF7F9F00, 0xFF7F9F55, 0xFF7F9FAA, 0xFF7F9FFF,
     0xFF7FBF00, 0xFF7FBF55, 0xFF7FBFAA, 0xFF7FBFFF, 0xFF7FDF00, 0xFF7FDF55, 0xFF7FDFAA, 0xFF7FDFFF,
     0xFF7FFF00, 0xFF7FFF55, 0xFF7FFFAA, 0xFF7FFFFF, 0xFFAA0000, 0xFFAA0055, 0xFFAA00AA, 0xFFAA00FF,
     0xFFAA1F00, 0xFFAA1F55, 0xFFAA1FAA, 0xFFAA1FFF, 0xFFAA3F00, 0xFFAA3F55, 0xFFAA3FAA, 0xFFAA3FFF,
     0xFFAA5F00, 0xFFAA5F55, 0xFFAA5FAA, 0xFFAA5FFF, 0xFFAA7F00, 0xFFAA7F55, 0xFFAA7FAA, 0xFFAA7FFF,
     0xFFAA9F00, 0xFFAA9F55, 0xFFAA9FAA, 0xFFAA9FFF, 0xFFAABF00, 0xFFAABF55, 0xFFAABFAA, 0xFFAABFFF,
     0xFFAADF00, 0xFFAADF55, 0xFFAADFAA, 0xFFAADFFF, 0xFFAAFF00, 0xFFAAFF55, 0xFFAAFFAA, 0xFFAAFFFF,
     0xFFD40000, 0xFFD40055, 0xFFD400AA, 0xFFD400FF, 0xFFD41F00, 0xFFD41F55, 0xFFD41FAA, 0xFFD41FFF,
     0xFFD43F00, 0xFFD43F55, 0xFFD43FAA, 0xFFD43FFF, 0xFFD45F00, 0xFFD45F55, 0xFFD45FAA, 0xFFD45FFF,
     0xFFD47F00, 0xFFD47F55, 0xFFD47FAA, 0xFFD47FFF, 0xFFD49F00, 0xFFD49F55, 0xFFD49FAA, 0xFFD49FFF,
     0xFFD4BF00, 0xFFD4BF55, 0xFFD4BFAA, 0xFFD4BFFF, 0xFFD4DF00, 0xFFD4DF55, 0xFFD4DFAA, 0xFFD4DFFF,
     0xFFD4FF00, 0xFFD4FF55, 0xFFD4FFAA, 0xFFD4FFFF, 0xFFFF0055, 0xFFFF00AA, 0xFFFF1F00, 0xFFFF1F55,
     0xFFFF1FAA, 0xFFFF1FFF, 0xFFFF3F00, 0xFFFF3F55, 0xFFFF3FAA, 0xFFFF3FFF, 0xFFFF5F00, 0xFFFF5F55,
     0xFFFF5FAA, 0xFFFF5FFF, 0xFFFF7F00, 0xFFFF7F55, 0xFFFF7FAA, 0xFFFF7FFF, 0xFFFF9F00, 0xFFFF9F55,
     0xFFFF9FAA, 0xFFFF9FFF, 0xFFFFBF00, 0xFFFFBF55, 0xFFFFBFAA, 0xFFFFBFFF, 0xFFFFDF00, 0xFFFFDF55,
     0xFFFFDFAA, 0xFFFFDFFF, 0xFFFFFF55, 0xFFFFFFAA, 0xFFCCCCFF, 0xFFFFCCFF, 0xFF33FFFF, 0xFF66FFFF,
     0xFF99FFFF, 0xFFCCFFFF, 0xFF007F00, 0xFF007F55, 0xFF007FAA, 0xFF007FFF, 0xFF009F00, 0xFF009F55,
     0xFF009FAA, 0xFF009FFF, 0xFF00BF00, 0xFF00BF55, 0xFF00BFAA, 0xFF00BFFF, 0xFF00DF00, 0xFF00DF55,
     0xFF00DFAA, 0xFF00DFFF, 0xFF00FF55, 0xFF00FFAA, 0xFF2A0000, 0xFF2A0055, 0xFF2A00AA, 0xFF2A00FF,
     0xFF2A1F00, 0xFF2A1F55, 0xFF2A1FAA, 0xFF2A1FFF, 0xFF2A3F00, 0xFF2A3F55, 0xFFFFFBF0, 0xFFA0A0A4,
     0xFF808080, 0xFFFF0000, 0xFF00FF00, 0xFFFFFF00, 0xFF0000FF, 0xFFFF00FF, 0xFF00FFFF, 0xFFFFFFFF}
);

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

void Palette::addColor(std::uint32_t color) {
  addColor(Rgb(color));
}

void Palette::setColor(int index, Rgb color) {
  Q_ASSERT_X(index >= 0 && index < m_rgbList.size(), Q_FUNC_INFO, "Index out of bounds.");

  if (index > kMaxСolors) {
    return;
  }

  m_rgbList[index] = color;
  m_labList[index] = Lab::fromRgb(color);
}

void Palette::setColor(int index, std::uint32_t color) {
  setColor(index, Rgb(color));
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

std::uint32_t Palette::color(int index) const {
  Q_ASSERT_X(index >= 0 && index < m_rgbList.size(), Q_FUNC_INFO, "Index out of bounds.");

  return m_rgbList[index].color();
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
