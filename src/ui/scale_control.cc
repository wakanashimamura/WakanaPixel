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

#include "ui/scale_control.h"

#include <QVBoxLayout>

// ----------------------------------------------------------------------------------------------
// Constructors
// ----------------------------------------------------------------------------------------------

ScaleControl::ScaleControl(QWidget* parent)
    : QGroupBox(parent) {
  m_combo         = new QComboBox(this);
  m_width         = new SizeControl(this);
  m_height        = new SizeControl(this);
  m_roundLabel    = new QLabel(this);
  m_roundCombo    = new QComboBox(this);
  m_resizeControl = new ResizeModeControl(this);

  m_width->setText("Width");
  m_height->setText("Height");

  m_roundLabel->setText("Rounding");
  m_roundCombo->addItem("Floor", QVariant::fromValue(RoundMode::Floor));
  m_roundCombo->addItem("Round", QVariant::fromValue(RoundMode::Round));
  m_roundCombo->addItem("Ceil", QVariant::fromValue(RoundMode::Ceil));
  setCurrentRoundMode(RoundMode::Round);

  QVBoxLayout* layout = new QVBoxLayout(this);

  layout->addWidget(m_combo);
  layout->addWidget(m_width);
  layout->addWidget(m_height);
  layout->addWidget(m_roundLabel);
  layout->addWidget(m_roundCombo);
  layout->addWidget(m_resizeControl);

  // m_width / m_height

  connect(m_width, &SizeControl::valueChanged, this, [this](int value) {
    emit widthChanged(value);
    emit settingsChanged();
  });

  connect(m_height, &SizeControl::valueChanged, this, [this](int value) {
    emit heightChanged(value);
    emit settingsChanged();
  });

  // m_combo

  connect(m_combo, &QComboBox::currentIndexChanged, this, [this](int index) {
    emit currentIndexChanged(index);
    emit settingsChanged();
  });
  connect(m_combo, &QComboBox::currentTextChanged, this, &ScaleControl::currentTextChanged);

  // m_roundCombo

  connect(m_roundCombo, &QComboBox::currentIndexChanged, this, [this]() {
    RoundMode mode = m_roundCombo->currentData().value<RoundMode>();
    emit roundModeChanged(mode);
    emit settingsChanged();
  });

  // m_resizeControl

  connect(m_resizeControl, &ResizeModeControl::resizeModeChanged, this, [this](ResizeMode mode) {
    emit resizeModeChanged(mode);
    emit settingsChanged();
  });

  connect(m_resizeControl, &ResizeModeControl::valueChanged, this, [this](int value) {
    emit resizeCropValueChanged(value);
    emit settingsChanged();
  });
}

// ----------------------------------------------------------------------------------------------
// ComboBox
// ----------------------------------------------------------------------------------------------

void ScaleControl::addItem(const QString& text, const QVariant& userData) {
  m_combo->addItem(text, userData);
}

QVariant ScaleControl::currentData(int role) const {
  return m_combo->currentData();
}

int ScaleControl::currentIndex() const {
  return m_combo->currentIndex();
}

QString ScaleControl::currentText() const {
  return m_combo->currentText();
}

void ScaleControl::hideComboBox() {
  m_combo->hide();
}
void ScaleControl::showComboBox() {
  m_combo->show();
}

// ----------------------------------------------------------------------------------------------
// Width
// ----------------------------------------------------------------------------------------------

void ScaleControl::setWidthMinimum(int value) {
  m_width->setMinimum(value);
}
int ScaleControl::widthMinimum() const {
  return m_width->minimum();
}

void ScaleControl::setWidthMaximum(int value) {
  m_width->setMaximum(value);
}
int ScaleControl::widthMaximum() const {
  return m_width->maximum();
}

QSize ScaleControl::scaleRange() {
  return QSize(widthMaximum(), heightmaximum());
}

int ScaleControl::widthValue() const {
  return m_width->value();
}

QSize ScaleControl::scaleSize() const {
  return QSize(widthValue(), heightValue());
}

void ScaleControl::hideWidth() {
  m_width->hide();
}
void ScaleControl::showWidth() {
  m_width->show();
}

// ----------------------------------------------------------------------------------------------
// Height
// ----------------------------------------------------------------------------------------------

void ScaleControl::setHeightMinimum(int value) {
  m_height->setMinimum(value);
}
int ScaleControl::heightMinimum() const {
  return m_height->minimum();
}

void ScaleControl::setHeightMaximum(int value) {
  m_height->setMaximum(value);
}
int ScaleControl::heightmaximum() const {
  return m_height->maximum();
}

int ScaleControl::heightValue() const {
  return m_height->value();
}

void ScaleControl::hideHeight() {
  m_height->hide();
}
void ScaleControl::showHeight() {
  m_height->show();
}

// ----------------------------------------------------------------------------------------------
// Round mode
// ----------------------------------------------------------------------------------------------

RoundMode ScaleControl::currentRoundMode() const {
  return m_roundCombo->currentData().value<RoundMode>();
}

void ScaleControl::hideRoundMode() {
  m_roundLabel->hide();
  m_roundCombo->hide();
}

void ScaleControl::showRoundMode() {
  m_roundLabel->show();
  m_roundCombo->show();
}

// ----------------------------------------------------------------------------------------------
// Resize mode
// ----------------------------------------------------------------------------------------------

ResizeMode ScaleControl::currentResizeMode() const {
  return m_resizeControl->currentResizeMode();
}

int ScaleControl::resizeCropValue() {
  return m_resizeControl->value();
}

void ScaleControl::setResizeCropMode(CropMode mode) {
  m_resizeControl->setCropMode(mode);
}

void ScaleControl::setResizeControlDisabled(bool value) {
  m_resizeControl->setResizeDisabled(value);
}

void ScaleControl::hideCropControl() {
  m_resizeControl->hideCropControl();
}

void ScaleControl::showCropControl() {
  m_resizeControl->showCropControl();
}

void ScaleControl::setResizeMinimum(int value) {
  m_resizeControl->setMinimum(value);
}

int ScaleControl::resizeMinimum() const {
  return m_resizeControl->minimum();
}

void ScaleControl::setResizeMaximum(int value) {
  m_resizeControl->setMaximum(value);
}

int ScaleControl::resizeMaximum() const {
  return m_resizeControl->maximum();
}

// ----------------------------------------------------------------------------------------------
// Slots ComboBox
// ----------------------------------------------------------------------------------------------

void ScaleControl::clear() {
  m_combo->clear();
}

void ScaleControl::setCurrentIndex(int index) {
  m_combo->setCurrentIndex(index);
}

// ----------------------------------------------------------------------------------------------
// Slots Width / Height
// ----------------------------------------------------------------------------------------------

void ScaleControl::setWidth(int value) {
  m_width->setValue(value);
}

void ScaleControl::setWidthRange(int min, int max) {
  m_width->setRange(min, max);
}

void ScaleControl::setWidthEnabled(bool value) {
  m_width->setEnabled(value);
}

void ScaleControl::setHeight(int value) {
  m_height->setValue(value);
}

void ScaleControl::setHeightRange(int min, int max) {
  m_height->setRange(min, max);
}

void ScaleControl::setHeightEnabled(bool value) {
  m_height->setEnabled(value);
}

void ScaleControl::setScaleSize(QSize size) {
  setWidth(size.width());
  setHeight(size.height());
}

void ScaleControl::setScaleRange(QSize size) {
  setWidthMaximum(size.width());
  setHeightMaximum(size.height());
}

void ScaleControl::setCurrentRoundMode(RoundMode mode) {
  m_roundCombo->setCurrentIndex(m_roundCombo->findData(QVariant::fromValue(mode)));
}

// ----------------------------------------------------------------------------------------------
// Resize mode
// ----------------------------------------------------------------------------------------------

void ScaleControl::setCurrentResizeMode(ResizeMode mode) {
  m_resizeControl->setCurrentResizeMode(mode);
}

void ScaleControl::setResizeCropValue(int value) {
  m_resizeControl->setValue(value);
}
