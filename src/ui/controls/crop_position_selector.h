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

#include "processing/resize_geometry.h"

#include <QGroupBox>

class QPushButton;
class QSlider;
class QSpinBox;

class CropPositionSelector : public QGroupBox {
  Q_OBJECT

 public:
  explicit CropPositionSelector(QWidget* parent = nullptr);

  [[nodiscard]] int value() const;

  void updateDirectionLabels(AspectFillDimension axis);

 public slots:
  void setValue(int value);
  void setMaximum(int maximum);
  void setConfiguration(int maximum, AspectFillDimension axis);

 signals:
  void valueChanged(int value);

 private:
  QPushButton* m_leftButton;
  QPushButton* m_centerButton;
  QPushButton* m_rightButton;

  QSlider* m_slider;
  QSpinBox* m_spinBox;
};
