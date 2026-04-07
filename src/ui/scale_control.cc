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

ScaleControl::ScaleControl(QWidget* parent)
    : QWidget(parent) {
  m_label  = new QLabel(this);
  m_combo  = new QComboBox(this);
  m_width  = new SizeControl(this);
  m_height = new SizeControl(this);

  m_label->setText("Title");

  m_width->setText("width");
  m_height->setText("height");

  QVBoxLayout* layout = new QVBoxLayout(this);
  layout->setSpacing(6);
  layout->setContentsMargins(0, 0, 0, 0);

  layout->addWidget(m_label);
  layout->addWidget(m_combo);
  layout->addWidget(m_width);
  layout->addWidget(m_height);

  connect(m_width, &SizeControl::valueChanged, this, &ScaleControl::widthChanged);
  connect(m_height, &SizeControl::valueChanged, this, &ScaleControl::heightChanged);
  connect(m_combo, &QComboBox::currentIndexChanged, this, &ScaleControl::currentIndexChanged);
  connect(m_combo, &QComboBox::currentTextChanged, this, &ScaleControl::currentTextChanged);
}

void ScaleControl::setWidthMinimum(int value) {
  m_width->setMinimum(value);
}
int ScaleControl::widthMinimum() const {
  return m_width->minimum();
}

void ScaleControl::setHeightMinimum(int value) {
  m_height->setMinimum(value);
}
int ScaleControl::heightMinimum() const {
  return m_height->minimum();
}

void ScaleControl::setWidthMaximum(int value) {
  m_width->setMaximum(value);
}
int ScaleControl::widthMaximum() const {
  return m_width->maximum();
}

void ScaleControl::setHeightMaximum(int value) {
  m_height->setMaximum(value);
}
int ScaleControl::heightmaximum() const {
  return m_height->maximum();
}

void ScaleControl::hideWidth() {
  m_width->hide();
}
void ScaleControl::hideHeight() {
  m_height->hide();
}
void ScaleControl::hideComboBox() {
  m_combo->hide();
}

void ScaleControl::showWidth() {
  m_width->show();
}
void ScaleControl::showHeight() {
  m_height->show();
}
void ScaleControl::showComboBox() {
  m_combo->show();
}

int ScaleControl::widthValue() const {
  return m_width->value();
}

int ScaleControl::heightValue() const {
  return m_height->value();
}

QString ScaleControl::title() const {
  return m_label->text();
}

void ScaleControl::setWidth(int value) {
  m_width->setValue(value);
}
void ScaleControl::setHeight(int value) {
  m_height->setValue(value);
}

void ScaleControl::setWidthRange(int min, int max) {
  m_width->setRange(min, max);
}
void ScaleControl::setHeightRange(int min, int max) {
  m_height->setRange(min, max);
}

void ScaleControl::setCurrentIndex(int index) {
  m_combo->setCurrentIndex(index);
}

void ScaleControl::setTitle(const QString& text) {
  m_label->setText(text);
}
