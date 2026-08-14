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

#include "resize_mode_selector.h"

#include <QComboBox>
#include <QVBoxLayout>

ResizeModeSelector::ResizeModeSelector(QWidget* parent)
    : QGroupBox("Mode", parent),
      m_comboBox(new QComboBox(this)) {
  QVBoxLayout* layout = new QVBoxLayout(this);
  layout->addWidget(m_comboBox);

  // clang-format off
  m_comboBox->addItem("Original",   QVariant::fromValue(ResizeMode::Original));
  m_comboBox->addItem("Exact Size", QVariant::fromValue(ResizeMode::Exact));
  m_comboBox->addItem("Fit",        QVariant::fromValue(ResizeMode::Fit));
  m_comboBox->addItem("Fill",       QVariant::fromValue(ResizeMode::Fill));
  m_comboBox->addItem("Width",      QVariant::fromValue(ResizeMode::Width));
  m_comboBox->addItem("Height",     QVariant::fromValue(ResizeMode::Height));
  // clang-format on

  connect(m_comboBox, &QComboBox::currentIndexChanged, this, [this] { emit modeChanged(mode()); });
}

ResizeMode ResizeModeSelector::mode() const {
  return m_comboBox->currentData().value<ResizeMode>();
}

void ResizeModeSelector::setMode(ResizeMode mode) {
  m_comboBox->setCurrentIndex(m_comboBox->findData(QVariant::fromValue(mode)));
}
