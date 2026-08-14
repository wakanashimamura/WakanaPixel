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

#include "common/wmath.h"

#include <QGroupBox>

class QButtonGroup;
class QRadioButton;

class RoundingModeSelector : public QGroupBox {
  Q_OBJECT

 public:
  explicit RoundingModeSelector(QWidget* parent = nullptr);

  [[nodiscard]] RoundingMode mode() const;

 public slots:
  void setMode(RoundingMode mode);

 signals:
  void modeChanged(RoundingMode mode);

 private:
  RoundingMode m_mode = RoundingMode::Round;
  QButtonGroup* m_buttonGroup;
};
