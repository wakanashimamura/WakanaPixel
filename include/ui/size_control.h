// ================================================================================================
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

#ifndef SIZE_CONTROL_H_
#define SIZE_CONTROL_H_

#include <QLabel>
#include <QSlider>
#include <QSpinBox>
#include <QString>
#include <QWidget>

class SizeControl : public QWidget {
  Q_OBJECT

 public:
  explicit SizeControl(QWidget* parent = nullptr);

  void setMinimum(int value);
  int minimum() const;

  void setMaximum(int value);
  int maximum() const;

  int value() const;
  QString text() const;

 public slots:
  void setValue(int value);
  void setRange(int min, int max);

  void setText(const QString& text);

 signals:
  void valueChanged(int value);

 private:
  QSlider* m_slider;
  QSpinBox* m_spinBox;
  QLabel* m_label;
};

#endif  // !SIZE_CONTROL_H_
