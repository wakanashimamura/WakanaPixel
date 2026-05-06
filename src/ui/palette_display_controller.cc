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

#include "ui/palette_display_controller.h"

#include "core/image_painter.h"

#include <QVBoxLayout>

PaletteDisplayController::PaletteDisplayController(QWidget* parent)
    : QGroupBox(parent) {
  setTitle("Palette display");

  m_combo = new QComboBox();

  m_combo->addItem("Top", QVariant::fromValue(PalettePosition::Top));
  m_combo->addItem("None", QVariant::fromValue(PalettePosition::None));
  m_combo->addItem("Bottom", QVariant::fromValue(PalettePosition::Bottom));
  setCurrentPalettePosition(PalettePosition::None);

  QVBoxLayout* layout = new QVBoxLayout(this);

  layout->setSpacing(0);
  layout->setContentsMargins(9, 0, 9, 6);

  layout->addWidget(m_combo);

  connect(m_combo, &QComboBox::currentIndexChanged, this, [this]() {
    PalettePosition mode = m_combo->currentData().value<PalettePosition>();
    emit palettePositionChanged(mode);
  });
}

PalettePosition PaletteDisplayController::currentPalettePosition() {
  return m_combo->currentData().value<PalettePosition>();
}

void PaletteDisplayController::setCurrentPalettePosition(PalettePosition mode) {
  m_combo->setCurrentIndex(m_combo->findData(QVariant::fromValue(mode)));
}
