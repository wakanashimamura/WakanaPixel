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

#include "ui/resize_mode_control.h"

#include "core/scale.h"

ResizeModeControl::ResizeModeControl(QWidget* parent)
    : QWidget(parent) {
  m_label       = new QLabel("Resize Mode", this);
  m_combo       = new QComboBox(this);
  m_cropControl = new CropControl(this);

  m_combo->addItem("Fit", QVariant::fromValue(ResizeMode::Fit));
  m_combo->addItem("Crop", QVariant::fromValue(ResizeMode::Crop));
  setCurrentResizeMode(ResizeMode::Fit);

  QVBoxLayout* m_vLayout = new QVBoxLayout(this);

  m_vLayout->setSpacing(6);
  m_vLayout->setContentsMargins(0, 0, 0, 0);

  m_vLayout->addWidget(m_label);
  m_vLayout->addWidget(m_combo);
  m_vLayout->addWidget(m_cropControl);

  setLayout(m_vLayout);

  connect(m_cropControl, &CropControl::valueChanged, this, &ResizeModeControl::valueChanged);

  connect(m_combo, &QComboBox::currentIndexChanged, this, [this](int) {
    ResizeMode mode = this->currentResizeMode();
    if (mode == ResizeMode::Crop) {
      showCropControl();
    } else {
      hideCropControl();
    }
    emit resizeModeChanged(mode);
  });
}

ResizeMode ResizeModeControl::currentResizeMode() const {
  return m_combo->currentData().value<ResizeMode>();
}

void ResizeModeControl::setComboEnabled(bool value) {
  m_combo->setEnabled(value);
}

int ResizeModeControl::value() {
  return m_cropControl->value();
}

void ResizeModeControl::setCropMode(CropMode mode) {
  m_cropControl->setMode(mode);
}

void ResizeModeControl::hideCropControl() {
  m_cropControl->hide();
}

void ResizeModeControl::showCropControl() {
  m_cropControl->show();
}

void ResizeModeControl::setMinimum(int value) {
  m_cropControl->setMinimum(value);
}

int ResizeModeControl::minimum() const {
  return m_cropControl->minimum();
}

void ResizeModeControl::setMaximum(int value) {
  m_cropControl->setMaximum(value);
}

int ResizeModeControl::maximum() const {
  return m_cropControl->maximum();
}

void ResizeModeControl::setCurrentResizeMode(ResizeMode mode) {
  m_combo->setCurrentIndex(m_combo->findData(QVariant::fromValue(mode)));
  if (mode == ResizeMode::Crop) {
    showCropControl();
  } else {
    hideCropControl();
  }
}

void ResizeModeControl::setValue(int value) {
  m_cropControl->setValue(value);
}
