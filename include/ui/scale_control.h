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

#ifndef SCALE_CONTROL_H_
#define SCALE_CONTROL_H_

#include "core/utils.h"
#include "ui/resize_mode_control.h"
#include "ui/size_control.h"

#include <QComboBox>
#include <QGroupBox>
#include <QLabel>
#include <QVariant>

class ScaleControl : public QGroupBox {
  Q_OBJECT

 public:
  // ----------------------------------------------------------------------------------------------
  // Constructors
  // ----------------------------------------------------------------------------------------------

  explicit ScaleControl(QWidget* parent = nullptr);

  // ----------------------------------------------------------------------------------------------
  // ComboBox
  // ----------------------------------------------------------------------------------------------

  void addItem(const QString& text, const QVariant& userData = QVariant());
  QVariant currentData(int role = Qt::UserRole) const;

  int currentIndex() const;
  QString currentText() const;

  void hideComboBox();
  void showComboBox();

  // ----------------------------------------------------------------------------------------------
  // Width
  // ----------------------------------------------------------------------------------------------

  void setWidthMinimum(int value);
  int widthMinimum() const;

  void setWidthMaximum(int value);
  int widthMaximum() const;
  QSize scaleRange();

  int widthValue() const;
  QSize scaleSize() const;

  void hideWidth();
  void showWidth();

  // ----------------------------------------------------------------------------------------------
  // Height
  // ----------------------------------------------------------------------------------------------

  void setHeightMinimum(int value);
  int heightMinimum() const;

  void setHeightMaximum(int value);
  int heightmaximum() const;

  int heightValue() const;

  void hideHeight();
  void showHeight();

  // ----------------------------------------------------------------------------------------------
  // Round mode
  // ----------------------------------------------------------------------------------------------

  RoundMode currentRoundMode() const;

  void hideRoundMode();
  void showRoundMode();

  // ----------------------------------------------------------------------------------------------
  // Resize mode
  // ----------------------------------------------------------------------------------------------

  ResizeMode currentResizeMode() const;
  int resizeCropValue();

  void setResizeCropMode(CropMode mode);

  void setResizeControlDisabled(bool value);
  void hideCropControl();
  void showCropControl();

  void setResizeMinimum(int value);
  int resizeMinimum() const;

  void setResizeMaximum(int value);
  int resizeMaximum() const;

 public slots:

  // ----------------------------------------------------------------------------------------------
  // ComboBox
  // ----------------------------------------------------------------------------------------------

  void clear();
  void setCurrentIndex(int index);

  // ----------------------------------------------------------------------------------------------
  // Width / Height
  // ----------------------------------------------------------------------------------------------

  void setWidth(int value);
  void setWidthRange(int min, int max);
  void setWidthEnabled(bool value);

  void setHeight(int value);
  void setHeightRange(int min, int max);
  void setHeightEnabled(bool value);

  void setScaleSize(QSize size);
  void setScaleRange(QSize size);

  // ----------------------------------------------------------------------------------------------
  // Round mode
  // ----------------------------------------------------------------------------------------------

  void setCurrentRoundMode(RoundMode mode);

  // ----------------------------------------------------------------------------------------------
  // Resize mode
  // ----------------------------------------------------------------------------------------------

  void setCurrentResizeMode(ResizeMode mode);
  void setResizeCropValue(int value);

 signals:

  void settingsChanged();

  // ----------------------------------------------------------------------------------------------
  // ComboBox
  // ----------------------------------------------------------------------------------------------

  void currentIndexChanged(int index);
  void currentTextChanged(const QString& text);

  // ----------------------------------------------------------------------------------------------
  // Width / Height
  // ----------------------------------------------------------------------------------------------

  void widthChanged(int value);
  void heightChanged(int value);

  // ----------------------------------------------------------------------------------------------
  // Round mode
  // ----------------------------------------------------------------------------------------------

  void roundModeChanged(RoundMode mode);

  // ----------------------------------------------------------------------------------------------
  // Resize mode
  // ----------------------------------------------------------------------------------------------

  void resizeModeChanged(ResizeMode mode);
  void resizeCropValueChanged(int value);

 private:
  QComboBox* m_combo                 = nullptr;
  SizeControl* m_width               = nullptr;
  SizeControl* m_height              = nullptr;
  QLabel* m_roundLabel               = nullptr;
  QComboBox* m_roundCombo            = nullptr;
  ResizeModeControl* m_resizeControl = nullptr;
};

#endif  // !SCALE_CONTROL_H_
