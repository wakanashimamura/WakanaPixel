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
    : QGroupBox("Size", this),
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

void ImageSizeSelector::setWidthVisible(bool visible) {
  m_width->setVisible(visible);
  updateVisibility();
}

bool ImageSizeSelector::isWidthVisible() const {
  return m_width->isVisible();
}

void ImageSizeSelector::setHeightVisible(bool visible) {
  m_height->setVisible(visible);
  updateVisibility();
}

bool ImageSizeSelector::isHeightVisible() const {
  return m_height->isVisible();
}

void ImageSizeSelector::setWidthEnabled(bool enabled) {
  m_width->setEnabled(enabled);
  updateEnabled();
}

bool ImageSizeSelector::isWidthEnabled() const {
  return m_width->isEnabled();
}

void ImageSizeSelector::setHeightEnabled(bool enabled) {
  m_height->setEnabled(enabled);
  updateEnabled();
}

bool ImageSizeSelector::isHeightEnabled() const {
  return m_height->isEnabled();
}

void ImageSizeSelector::setValue(QSize value) {
  m_width->setValue(value.width());
}

void ImageSizeSelector::setWidthRange(int minimum, int maximum) {
  m_width->setRange(minimum, maximum);
}

void ImageSizeSelector::setHeightRange(int minimum, int maximum) {
  m_height->setRange(minimum, maximum);
}

void ImageSizeSelector::updateVisibility() {
  setVisible(m_width->isVisible() || m_height->isVisible());
}

void ImageSizeSelector::updateEnabled() {
  setEnabled(m_width->isEnabled() || m_height->isEnabled());
}
