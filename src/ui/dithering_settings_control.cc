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

#include "ui/dithering_settings_control.h"

// ----------------------------------------------------------------------------------------------
// DitheringSettingsControl
// ----------------------------------------------------------------------------------------------

DitheringSettingsControl::DitheringSettingsControl(const QString& title, QWidget* parent)
    : QGroupBox(parent) {
  setTitle(title);

  QVBoxLayout* main = new QVBoxLayout(this);
  main->setContentsMargins(4, 4, 4, 4);

  m_label = new QLabel("Color Comparison Format");
  m_combo = new QComboBox();

  m_combo->addItem("RGB", QVariant::fromValue(Palette::ColorDistMode::RGB));
  m_combo->addItem("WRGB", QVariant::fromValue(Palette::ColorDistMode::WRGB));
  m_combo->addItem("Lab", QVariant::fromValue(Palette::ColorDistMode::Lab));

  main->addWidget(m_label);
  main->addWidget(m_combo);

  m_specificLayout = new QVBoxLayout();
  main->addLayout(m_specificLayout);

  connect(
      m_combo,
      &QComboBox::currentIndexChanged,
      this,
      &DitheringSettingsControl::settingsChanged
  );
}

Palette::ColorDistMode DitheringSettingsControl::colorDistMode() {
  return m_combo->currentData().value<Palette::ColorDistMode>();
}

// ----------------------------------------------------------------------------------------------
// FloydSteinbergSettingsControl
// ----------------------------------------------------------------------------------------------

FloydSteinbergSettingsControl::FloydSteinbergSettingsControl(const QString& title, QWidget* parent)
    : DitheringSettingsControl(title, parent) {
  m_powerLabel  = new QLabel("Dithering strength");
  m_powerSlider = new QSlider(Qt::Horizontal);

  m_powerSlider->setRange(0, 255);
  m_powerSlider->setValue(255);

  specificLayout()->addWidget(m_powerLabel);
  specificLayout()->addWidget(m_powerSlider);

  connect(m_powerSlider, &QSlider::valueChanged, this, &DitheringSettingsControl::settingsChanged);
}

uint8_t FloydSteinbergSettingsControl::strength() {
  return static_cast<uint8_t>(m_powerSlider->value());
}
