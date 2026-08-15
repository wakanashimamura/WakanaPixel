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

#include "image_size_selector.h"

#include "slider_spin_box.h"

#include <QVBoxLayout>

ImageSizeSelector::ImageSizeSelector(QWidget* parent)
    : QGroupBox("Size", parent),
      m_width(new SliderSpinBox("Width", this)),
      m_height(new SliderSpinBox("Height", this)) {
  QVBoxLayout* layout = new QVBoxLayout(this);

  layout->addWidget(m_width);
  layout->addWidget(m_height);

  connect(m_width, &SliderSpinBox::valueChanged, this, [this] { emit valueChanged(value()); });
  connect(m_height, &SliderSpinBox::valueChanged, this, [this] { emit valueChanged(value()); });
}

QSize ImageSizeSelector::value() const {
  return QSize(m_width->value(), m_height->value());
}

void ImageSizeSelector::setWidthEnabled(bool enabled) {
  m_widthEnabled = enabled;
  m_width->setEnabled(enabled);
  updateEnabled();
}

bool ImageSizeSelector::isWidthEnabled() const {
  return m_widthEnabled;
}

void ImageSizeSelector::setHeightEnabled(bool enabled) {
  m_heightEnabled = enabled;
  m_height->setEnabled(enabled);
  updateEnabled();
}

bool ImageSizeSelector::isHeightEnabled() const {
  return m_heightEnabled;
}

void ImageSizeSelector::setValue(QSize value) {
  const QSignalBlocker blockWidth(m_width);
  const QSignalBlocker blockHeight(m_height);


  m_width->setValue(value.width()); 
  m_height->setValue(value.height());

  emit valueChanged(value);
}

void ImageSizeSelector::setWidthRange(int minimum, int maximum) {
  m_width->setRange(minimum, maximum);
}

void ImageSizeSelector::setHeightRange(int minimum, int maximum) {
  m_height->setRange(minimum, maximum);
}

void ImageSizeSelector::updateEnabled() {
  setEnabled(m_widthEnabled || m_heightEnabled);
}
