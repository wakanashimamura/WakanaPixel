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

#ifndef DITHERING_SETTINGS_CONTROL_H_
#define DITHERING_SETTINGS_CONTROL_H_

#include "model/palette.h"

#include <QComboBox>
#include <QGroupBox>
#include <QLabel>
#include <QSlider>
#include <QVBoxLayout>

// ----------------------------------------------------------------------------------------------
// DitheringSettingsControl
// ----------------------------------------------------------------------------------------------

class DitheringSettingsControl : public QGroupBox {
  Q_OBJECT
 public:
  explicit DitheringSettingsControl(const QString& title, QWidget* parent = nullptr);

  Palette::ColorDistMode colorDistMode();

 signals:
  void settingsChanged();

 protected:
  QVBoxLayout* specificLayout() const { return m_specificLayout; }

 private:
  QLabel* m_label;
  QComboBox* m_combo;

  QVBoxLayout* m_specificLayout;
};

// ----------------------------------------------------------------------------------------------
// FloydSteinbergSettingsControl
// ----------------------------------------------------------------------------------------------

class FloydSteinbergSettingsControl : public DitheringSettingsControl {
  Q_OBJECT
 public:
  explicit FloydSteinbergSettingsControl(const QString& title, QWidget* parent = nullptr);

  uint8_t strength();

 private:
  QLabel* m_powerLabel;
  QSlider* m_powerSlider;
};

#endif  // ! DITHERING_SETTINGS_CONTROL_H_
