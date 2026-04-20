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

#ifndef RESIZE_MODE_CONTROL_H_
#define RESIZE_MODE_CONTROL_H_

#include "ui/crop_control.h"

#include <QComboBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>

enum class ResizeMode;
enum class CropMode;

class ResizeModeControl : public QWidget {
  Q_OBJECT
 public:
  // ----------------------------------------------------------------------------------------------
  // Constructors
  // ----------------------------------------------------------------------------------------------

  ResizeModeControl(QWidget* parent = nullptr);

  // ----------------------------------------------------------------------------------------------
  // ComboBox
  // ----------------------------------------------------------------------------------------------

  ResizeMode currentResizeMode() const;
  void setComboEnabled(bool value);

  // ----------------------------------------------------------------------------------------------
  // CropControl
  // ----------------------------------------------------------------------------------------------

  int value();
  void setCropMode(CropMode mode);

  void hideCropControl();
  void showCropControl();

  void setMinimum(int value);
  int minimum() const;

  void setMaximum(int value);
  int maximum() const;

 public slots:

  void setCurrentResizeMode(ResizeMode mode);
  void setValue(int value);

 signals:

  void resizeModeChanged(ResizeMode mode);
  void valueChanged(int value);

 private:
  QLabel* m_label;
  QComboBox* m_combo;
  CropControl* m_cropControl;

  QVBoxLayout* m_vLayout;
};

#endif  // !RESIZE_MODE_CONTROL_H_
