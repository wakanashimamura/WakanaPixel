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

#include "model/settings.h"

// clang-format off

const std::array<Platform, 1> Settings::k_platforms = {
  Platform (
    "Amiga",
    QSize{320, 256},
    {
      {"320x256", DownScaleMode::Preset, QSize(320, 256)},
      {"320x240", DownScaleMode::Preset, QSize(320, 240)},
      {"320x200", DownScaleMode::Preset, QSize(320, 200)},
      {"256x256", DownScaleMode::Preset, QSize(256, 256)},
      {"240x240", DownScaleMode::Preset, QSize(240, 240)},
      {"200x200", DownScaleMode::Preset, QSize(200, 200)},
      {"160x160", DownScaleMode::Preset, QSize(160, 160)},
      {"128x128", DownScaleMode::Preset, QSize(128, 128)}
    }
  )
};

const std::array<DownScaleData, 5>  Settings::k_downScaleDefData {
  DownScaleData("Original",      DownScaleMode::Original,     QSize()),
  DownScaleData("Custom",        DownScaleMode::Custom,       QSize()),
  DownScaleData("Custom Canvas", DownScaleMode::CustomCanvas, QSize()),
  DownScaleData("Width",         DownScaleMode::Width,        QSize()),
  DownScaleData("Height",        DownScaleMode::Height,       QSize())
};

// clang-format on

const Platform& Settings::currentPlatform() {
  return k_platforms[static_cast<int>(m_currentPlatform)];
}

void Settings::setCurrentPlatform(PlatformId id) {
  m_currentPlatform = id;
}
