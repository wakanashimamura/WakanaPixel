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

#ifndef PALETTE_DISPLAY_CONTROLLER_H_
#define PALETTE_DISPLAY_CONTROLLER_H_

#include <QComboBox>
#include <QGroupBox>

enum class PalettePosition;

class PaletteDisplayController : public QGroupBox {
  Q_OBJECT
 public:
  explicit PaletteDisplayController(QWidget* parent = nullptr);

  PalettePosition currentPalettePosition();

 public slots:
  void setCurrentPalettePosition(PalettePosition mode);

 signals:
  void palettePositionChanged(PalettePosition position);

 private:
  QComboBox* m_combo;
};

#endif  // !PALETTE_DISPLAY_CONTROLLER_H_
