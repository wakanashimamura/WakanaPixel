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

#include "ui/crop_control.h"

#include "core/scale.h"

CropControl::CropControl(QWidget* parent)
    : QWidget(parent) {
  m_slider     = new QSlider(Qt::Horizontal, this);
  m_labelLeft  = new QLabel(this);
  m_labelRight = new QLabel(this);

  m_hLayout = new QHBoxLayout();
  m_vLayout = new QVBoxLayout();

  setRange(0, 0);
  setMode(CropMode::Vertical);

  // Layout Top
  m_hLayout = new QHBoxLayout();
  m_hLayout->addWidget(m_labelLeft);
  m_hLayout->addStretch();
  m_hLayout->addWidget(m_labelRight);

  setTopSpacing(0);
  setTopMargins(0, 0, 0, 0);

  // Layout Main
  m_vLayout = new QVBoxLayout(this);
  m_vLayout->addLayout(m_hLayout);
  m_vLayout->addWidget(m_slider);

  setMainSpacing(6);
  setMainMargins(0, 0, 0, 0);

  setLayout(m_vLayout);

  connect(m_slider, &QSlider::valueChanged, this, &CropControl::valueChanged);
}

void CropControl::setTopSpacing(int spacing) {
  m_hLayout->setSpacing(spacing);
}
void CropControl::setMainSpacing(int spacing) {
  m_vLayout->setSpacing(spacing);
}

void CropControl::setTopMargins(int left, int top, int right, int bottom) {
  m_hLayout->setContentsMargins(left, top, right, bottom);
}

void CropControl::setMainMargins(int left, int top, int right, int bottom) {
  m_vLayout->setContentsMargins(left, top, right, bottom);
}

void CropControl::setMinimum(int value) {
  m_slider->setMinimum(value);
}

int CropControl::minimum() const {
  return m_slider->minimum();
}

void CropControl::setMaximum(int value) {
  m_slider->setMaximum(value);
}

int CropControl::maximum() const {
  return m_slider->maximum();
}

int CropControl::value() const {
  return m_slider->value();
}

void CropControl::setMode(CropMode mode) {
  if (mode == CropMode::Horizontal) {
    m_labelLeft->setText("Left");
    m_labelRight->setText("Right");
  } else {
    m_labelLeft->setText("top");
    m_labelRight->setText("bottom");
  }
}

void CropControl::setValue(int value) {
  m_slider->setValue(value);
}

void CropControl::setRange(int min, int max) {
  m_slider->setRange(min, max);
}
