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

#include "ui/quantization_control.h"

#include "core/algorithm_factory.h"
#include "model/builtin_palettes.h"

QuantizationControl::QuantizationControl(QWidget* parent)
    : QGroupBox(parent) {
  m_palettesLabel = new QLabel("Palette");
  m_palettesCombo = new QComboBox;

  m_ditheringLabel         = new QLabel("Dithering");
  m_ditheringComboBox      = new QComboBox;
  m_ditheringSettingsPanel = new SettingsPanelController;

  for (int i = 0; i < kBuiltinPalettes.size(); ++i) {
    m_palettesCombo->addItem(kBuiltinPalettes[i].name(), i);
  }

  layout = new QVBoxLayout(this);

  layout->addWidget(m_palettesLabel);
  layout->addWidget(m_palettesCombo);

  layout->addWidget(m_ditheringLabel);
  layout->addWidget(m_ditheringComboBox);
  layout->addWidget(m_ditheringSettingsPanel);

  connect(
      m_palettesCombo,
      &QComboBox::currentIndexChanged,
      this,
      &QuantizationControl::settingsChanged
  );

  connect(m_ditheringComboBox, &QComboBox::currentIndexChanged, this, [this](int index) {
    setDitheringIndex(index);
    emit settingsChanged();
  });
}

int QuantizationControl::currentPaletteIndex() const {
  return m_palettesCombo->currentData().toInt();
}

void QuantizationControl::addDithering(
    const QString& text, QWidget* widget, DitheringAlgorithm id
) {
  m_ditheringComboBox->addItem(text, QVariant::fromValue(id));
  m_ditheringSettingsPanel->addWidget(widget);
}

DitheringAlgorithm QuantizationControl::currentDitheringId() const {
  return m_ditheringComboBox->currentData().value<DitheringAlgorithm>();
}

int QuantizationControl::currentDitheringIndex() const {
  return m_ditheringComboBox->currentIndex();
}

void QuantizationControl::setDitheringIndex(int index) {
  m_ditheringComboBox->setCurrentIndex(index);
  m_ditheringSettingsPanel->setCurrentIndex(index);
}
