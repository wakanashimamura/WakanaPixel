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

#include "preset_resize_dimensions.h"

#include <QComboBox>
#include <QVBoxLayout>

PresetResizeDimensions::PresetResizeDimensions(QWidget* parent)
    : QWidget(parent),
      m_comboBox(new QComboBox(this)) {
  QVBoxLayout* layout = new QVBoxLayout(this);
  layout->addWidget(m_comboBox);
  layout->setSpacing(0);
  layout->setContentsMargins(0, 0, 0, 0);

  m_comboBox->addItem("Custom", QVariant::fromValue(QSize()));

  // clang-format off
  m_comboBox->addItem("160x144", QVariant::fromValue(QSize(160,144)));
  m_comboBox->addItem("160x200", QVariant::fromValue(QSize(160,200)));
  m_comboBox->addItem("200x200", QVariant::fromValue(QSize(200,200)));
  m_comboBox->addItem("256x256", QVariant::fromValue(QSize(256,256)));
  m_comboBox->addItem("256x192", QVariant::fromValue(QSize(256,192)));
  m_comboBox->addItem("320x200", QVariant::fromValue(QSize(320,200)));
  m_comboBox->addItem("320x256", QVariant::fromValue(QSize(320,256)));
  m_comboBox->addItem("640×400", QVariant::fromValue(QSize(640,400)));
  m_comboBox->addItem("640×480", QVariant::fromValue(QSize(640,480)));
  // clang-format on
  m_comboBox->setCurrentIndex(7);

  connect(m_comboBox, &QComboBox::currentIndexChanged, this, [this]() {
    emit valueChanged(value());
  });
}

QSize PresetResizeDimensions::value() const {
  return m_comboBox->currentData().value<QSize>();
}

void PresetResizeDimensions::setCustom() {
  m_comboBox->setCurrentIndex(0);
}
