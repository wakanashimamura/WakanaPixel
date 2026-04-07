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

#ifndef SCALE_CONTROL_WIDGE_H_
#define SCALE_CONTROL_WIDGE_H_

#include "ui/size_control.h"

#include <QComboBox>
#include <QLabel>
#include <QWidget>

class ScaleControl : public QWidget {
  Q_OBJECT

 public:
  explicit ScaleControl(QWidget* parent = nullptr);

  void setWidthMinimum(int value);
  int widthMinimum() const;

  void setHeightMinimum(int value);
  int heightMinimum() const;

  void setWidthMaximum(int value);
  int widthMaximum() const;

  void setHeightMaximum(int value);
  int heightmaximum() const;

  void hideWidth();
  void hideHeight();
  void hideComboBox();

  void showWidth();
  void showHeight();
  void showComboBox();

  int widthValue() const;
  int heightValue() const;

  QString title() const;

 public slots:
  void setWidth(int value);
  void setHeight(int value);

  void setWidthRange(int min, int max);
  void setHeightRange(int min, int max);

  void setCurrentIndex(int index);

  void setTitle(const QString& text);

 signals:
  void widthChanged(int value);
  void heightChanged(int value);

  void currentIndexChanged(int index);
  void currentTextChanged(const QString& text);

 private:
  QLabel* m_label;
  QComboBox* m_combo;
  SizeControl* m_width;
  SizeControl* m_height;
};

#endif  // !SCALE_CONTROL_WIDGE_H_
