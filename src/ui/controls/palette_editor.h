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

#include "palette_canvas.h"

#include <QGroupBox>

// PaletteEditor is a wrapper around PaletteCanvas that adds a border around it.
class PaletteEditor : public QGroupBox {
  Q_OBJECT

 public:
  explicit PaletteEditor(QWidget* parent = nullptr);

  [[nodiscard]] const Palette& palette() const;

 public slots:
  void setPalette(const Palette& palette);

 signals:
  void paletteChanged(const Palette& palette);

 private:
  PaletteCanvas* m_paletteCanvas;
};
