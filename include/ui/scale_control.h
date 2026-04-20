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

#include "core/utils.h"
#include "ui/size_control.h"

#include <QComboBox>
#include <QLabel>
#include <QVariant>
#include <QWidget>

class ScaleControl : public QWidget {
  Q_OBJECT

 public:
  // ----------------------------------------------------------------------------------------------
  // Constructors
  // ----------------------------------------------------------------------------------------------

  explicit ScaleControl(QWidget* parent = nullptr);

  // ----------------------------------------------------------------------------------------------
  // Title
  // ----------------------------------------------------------------------------------------------

  QString title() const;

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

 public slots:

  // ----------------------------------------------------------------------------------------------
  // Title
  // ----------------------------------------------------------------------------------------------

  void setTitle(const QString& text);

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

 signals:

  void scaleSettingsChanged();

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

 private:
  QLabel* m_label;
  QComboBox* m_combo;
  SizeControl* m_width;
  SizeControl* m_height;
  QLabel* m_roundLabel;
  QComboBox* m_roundCombo;
};

#endif  // !SCALE_CONTROL_WIDGE_H_
