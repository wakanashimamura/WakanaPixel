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

#include "crop_position_selector.h"

#include <QHBoxLayout>
#include <QPushButton>
#include <QSignalBlocker>
#include <QSlider>
#include <QSpinBox>
#include <QVBoxLayout>

CropPositionSelector::CropPositionSelector(QWidget* parent)
    : QGroupBox("Crop", parent),
      m_leftButton(new QPushButton("Left", this)),
      m_centerButton(new QPushButton("Center", this)),
      m_rightButton(new QPushButton("Right", this)),
      m_slider(new QSlider(Qt::Horizontal, this)),
      m_spinBox(new QSpinBox(this)) {
  m_leftButton->sizePolicy().setHorizontalPolicy(QSizePolicy::Maximum);
  m_centerButton->sizePolicy().setHorizontalPolicy(QSizePolicy::Maximum);
  m_rightButton->sizePolicy().setHorizontalPolicy(QSizePolicy::Maximum);
  m_slider->sizePolicy().setHorizontalPolicy(QSizePolicy::Maximum);
  m_spinBox->sizePolicy().setHorizontalPolicy(QSizePolicy::Maximum);

  QVBoxLayout* layout = new QVBoxLayout(this);

  m_spinBox->setFixedWidth(100);

  QHBoxLayout* btnLayout = new QHBoxLayout;
  btnLayout->addWidget(m_leftButton);
  btnLayout->addWidget(m_centerButton);
  btnLayout->addWidget(m_rightButton);

  QHBoxLayout* selectorLayout = new QHBoxLayout;
  selectorLayout->addWidget(m_slider);
  selectorLayout->addWidget(m_spinBox);

  layout->addLayout(btnLayout);
  layout->addLayout(selectorLayout);

  connect(m_slider, &QSlider::valueChanged, m_spinBox, &QSpinBox::setValue);
  connect(m_spinBox, &QSpinBox::valueChanged, m_slider, &QSlider::setValue);
  connect(m_slider, &QSlider::valueChanged, this, &CropPositionSelector::valueChanged);

  connect(m_leftButton, &QPushButton::clicked, this, [this]() {
    m_slider->setValue(m_slider->minimum());
  });

  connect(m_centerButton, &QPushButton::clicked, this, [this]() {
    m_slider->setValue(std::round(m_slider->maximum() / 2.0));
  });

  connect(m_rightButton, &QPushButton::clicked, this, [this]() {
    m_slider->setValue(m_slider->maximum());
  });
}

int CropPositionSelector::value() const {
  return m_slider->value();
}

void CropPositionSelector::setAxis(AspectFillDimension axis) {
  switch (axis) {
    case AspectFillDimension::Width:
      m_leftButton->setText("Top");
      m_rightButton->setText("Bottom");
      break;

    case AspectFillDimension::Height:
      m_leftButton->setText("Left");
      m_rightButton->setText("Right");
      break;
  }
}

void CropPositionSelector::setValue(int value) {
  const QSignalBlocker blockSlider(m_slider);
  const QSignalBlocker blockSpin(m_spinBox);

  m_slider->setValue(value);
  m_spinBox->setValue(value);

  emit valueChanged(value);
}

void CropPositionSelector::setMaximum(int maximum) {
  m_slider->setMaximum(maximum);
  m_spinBox->setMaximum(maximum);
}