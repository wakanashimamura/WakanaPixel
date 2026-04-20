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

#ifndef CROP_CONTROL_H_
#define CROP_CONTROL_H_

#include <QHBoxLayout>
#include <QLabel>
#include <QSlider>
#include <QVBoxLayout>
#include <QWidget>

enum class CropMode;

class CropControl : public QWidget {
  Q_OBJECT

 public:
  explicit CropControl(QWidget* parent = nullptr);

  void setTopSpacing(int spacing);
  void setMainSpacing(int spacing);

  void setTopMargins(int left, int top, int right, int bottom);
  void setMainMargins(int left, int top, int right, int bottom);

  void setMinimum(int value);
  int minimum() const;

  void setMaximum(int value);
  int maximum() const;

  int value() const;

  void setMode(CropMode mode);
 public slots:
  void setValue(int value);
  void setRange(int min, int max);

 signals:
  void valueChanged(int value);

 private:
  QSlider* m_slider;
  QLabel* m_labelLeft;
  QLabel* m_labelRight;

  QHBoxLayout* m_hLayout;
  QVBoxLayout* m_vLayout;
};

#endif  // !CROP_CONTROL_H_
