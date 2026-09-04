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

#include <QGroupBox>
#include <QSize>

class PresetResizeDimensions;
class SliderSpinBox;

class ImageSizeSelector : public QGroupBox {
  Q_OBJECT

 public:
  explicit ImageSizeSelector(QWidget* parent = nullptr);

  [[nodiscard]] QSize value() const;

  int maximumWidth() const;
  int maximumHeight() const;

  void setWidthEnabled(bool enabled);
  bool isWidthEnabled() const;

  void setHeightEnabled(bool enabled);
  bool isHeightEnabled() const;

  [[nodiscard]] QSize presetValue();
  void setModeCustomPreset();

 public slots:
  void setValue(QSize value);

  void setWidthRange(int minimum, int maximum);
  void setHeightRange(int minimum, int maximum);

 signals:
  void valueChanged(QSize value);

 private:
  void updateEnabled();
  void valueChanged_();

  bool m_widthEnabled  = true;
  bool m_heightEnabled = true;

  PresetResizeDimensions* m_preset;

  SliderSpinBox* m_width;
  SliderSpinBox* m_height;
};
