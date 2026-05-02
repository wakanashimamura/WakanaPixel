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

#include "ui/size_control.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

SizeControl::SizeControl(QWidget* parent)
    : QWidget(parent) {
  m_slider  = new QSlider(Qt::Horizontal, this);
  m_spinBox = new QSpinBox(this);
  m_label   = new QLabel("Size", this);

  setRange(0, 100);
  setRange(0, 100);

  // Layout Top
  QHBoxLayout* m_hLayout = new QHBoxLayout();
  m_hLayout->addWidget(m_label);
  m_hLayout->addWidget(m_spinBox);

  m_hLayout->setSpacing(0);
  m_hLayout->setContentsMargins(0, 0, 0, 0);

  // Layout Main
  QVBoxLayout* m_vLayout = new QVBoxLayout(this);
  m_vLayout->addLayout(m_hLayout);
  m_vLayout->addWidget(m_slider);

  m_vLayout->setSpacing(6);
  m_vLayout->setContentsMargins(0, 0, 0, 0);

  setLayout(m_vLayout);

  connect(m_slider, &QSlider::valueChanged, m_spinBox, &QSpinBox::setValue);
  connect(m_spinBox, &QSpinBox::valueChanged, m_slider, &QSlider::setValue);

  connect(m_slider, &QSlider::valueChanged, this, &SizeControl::valueChanged);
}

void SizeControl::setMinimum(int value) {
  m_slider->setMinimum(value);
  m_spinBox->setMinimum(value);
}

int SizeControl::minimum() const {
  return m_slider->minimum();
}

void SizeControl::setMaximum(int value) {
  m_slider->setMaximum(value);
  m_spinBox->setMaximum(value);
}

int SizeControl::maximum() const {
  return m_slider->maximum();
}

int SizeControl::value() const {
  return m_slider->value();
}

QString SizeControl::text() const {
  return m_label->text();
}

void SizeControl::setValue(int value) {
  m_slider->setValue(value);
}

void SizeControl::setRange(int min, int max) {
  m_slider->setRange(min, max);
  m_spinBox->setRange(min, max);
}

void SizeControl::setText(const QString& text) {
  m_label->setText(text);
}
