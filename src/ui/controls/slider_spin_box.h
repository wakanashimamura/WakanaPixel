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

#pragma once

#include <QWidget>

class QLabel;
class QSlider;
class QSpinBox;

class SliderSpinBox : public QWidget {
  Q_OBJECT

 public:
  explicit SliderSpinBox(QString label, QWidget* parent = nullptr);

  [[nodiscard]] int value() const;

  int maximum() const;

 public slots:
  void setValue(int value);
  void setRange(int minimum, int maximum);

 signals:
  void valueChanged(int value);

 private:
  QLabel* m_title;
  QSpinBox* m_spinBox;
  QSlider* m_slider;
};
