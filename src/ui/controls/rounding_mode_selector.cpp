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

#include "rounding_mode_selector.h"

#include <QButtonGroup>
#include <QHBoxLayout>
#include <QRadioButton>

RoundingModeSelector::RoundingModeSelector(QWidget* parent)
    : QGroupBox("Rounding", parent),
      m_buttonGroup(new QButtonGroup(this)) {
  QHBoxLayout* layout = new QHBoxLayout(this);

  QRadioButton* floorButton = new QRadioButton("Floor", this);
  QRadioButton* roundButton = new QRadioButton("Round", this);
  QRadioButton* ceilButton  = new QRadioButton("Ceil", this);

  layout->addWidget(floorButton);
  layout->addWidget(roundButton);
  layout->addWidget(ceilButton);

  m_buttonGroup->addButton(floorButton, static_cast<int>(RoundingMode::Floor));
  m_buttonGroup->addButton(roundButton, static_cast<int>(RoundingMode::Round));
  m_buttonGroup->addButton(ceilButton, static_cast<int>(RoundingMode::Ceil));

  connect(m_buttonGroup, &QButtonGroup::idClicked, this, [this](int id) {
    setMode(static_cast<RoundingMode>(id));
  });

  setMode(m_mode);
}

RoundingMode RoundingModeSelector::mode() const {
  return m_mode;
}

void RoundingModeSelector::setMode(RoundingMode mode) {
  if (m_mode == mode) {
    return;
  }
  m_mode = mode;

  m_buttonGroup->button(static_cast<int>(m_mode))->setChecked(true);

  emit modeChanged(m_mode);
}
