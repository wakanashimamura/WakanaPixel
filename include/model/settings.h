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

#ifndef SETTINGS_H_
#define SETTINGS_H_

#include <QSize>
#include <QString>

#include <array>

enum class DownScaleMode { Original, Custom, CustomCanvas, Width, Height, Preset };

enum class PlatformId { Amiga = 0 };

struct DownScaleData {
  DownScaleData() = default;
  DownScaleData(QString text_, DownScaleMode mode_, QSize size_)
      : text(text_),
        mode(mode_),
        size(size_) {}

  QString text;
  DownScaleMode mode;
  QSize size;
};

class Platform {
 public:
  Platform(QString name, QSize screenSize, std::vector<DownScaleData> downScaleData)
      : m_name(name),
        m_screenSize(screenSize),
        m_downScaleData(downScaleData) {}

  QString name() const { return m_name; }
  QSize screenSize() const { return m_screenSize; }
  const std::vector<DownScaleData>& downScaleData() const { return m_downScaleData; }

 private:
  QString m_name;
  QSize m_screenSize;
  std::vector<DownScaleData> m_downScaleData;
};

class Settings {
 public:
  static const std::array<Platform, 1> k_platforms;
  static const std::array<DownScaleData, 5> k_downScaleDefData;

  static const Platform& currentPlatform();
  static void setCurrentPlatform(PlatformId id);

 private:
  static inline PlatformId m_currentPlatform = PlatformId::Amiga;
};

#endif  // !SETTINGS_H_
