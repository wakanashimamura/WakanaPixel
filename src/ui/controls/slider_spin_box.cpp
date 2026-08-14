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

#include "slider_spin_box.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QSlider>
#include <QSpinBox>
#include <QString>
#include <QVBoxLayout>
 #include <QSignalBlocker>

SliderSpinBox::SliderSpinBox(QString label, QWidget* parent)
    : QWidget(parent),
      m_title(new QLabel(label, this)),
      m_spinBox(new QSpinBox()),
      m_slider(new QSlider(Qt::Horizontal, this)) {
  // Header layout
  QHBoxLayout* header = new QHBoxLayout();
  header->addWidget(m_title);
  header->addWidget(m_spinBox);

  // Layout
  QVBoxLayout* layout = new QVBoxLayout(this);
  layout->addLayout(header);
  layout->addWidget(m_slider);

  connect(m_slider, &QSlider::valueChanged, m_spinBox, &QSpinBox::setValue);
  connect(m_spinBox, &QSpinBox::valueChanged, m_slider, &QSlider::setValue);
  connect(m_slider, &QSlider::valueChanged, this, &SliderSpinBox::valueChanged);
}

int SliderSpinBox::value() const {
  return m_slider->value();
}

void SliderSpinBox::setValue(int value) {
  const QSignalBlocker blockSpin(m_spinBox);
  const QSignalBlocker blockSlider(m_slider);
  m_spinBox->setValue(value);
  m_slider->setValue(value);

  emit valueChanged(value);
}

void SliderSpinBox::setRange(int minimum, int maximum) {
  m_spinBox->setRange(minimum, maximum);
  m_slider->setRange(minimum, maximum);
}
