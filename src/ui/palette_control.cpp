#include "palette_control.h"
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

#include <QPainter>
#include <QRectF>

#include <image/palette.h>

PaletteControl::PaletteControl(QWidget* parent)
    : QGroupBox("Colors", parent) {
  setFixedSize(300, 200);
}

void PaletteControl::paintEvent(QPaintEvent* event) {
  QGroupBox::paintEvent(event);

  QRectF rectangle0 = contentsRect();
  QRectF rectangle(rectangle0.x() + 10, rectangle0.y() + 10, 15, 15);

  QPainter painter(this);



  for (int i = 0; i < testPalette1.size(); ++i) {
    Rgb rgb = testPalette1.rgb(i);

    painter.fillRect(rectangle, QColor(rgb.red(), rgb.green(), rgb.blue()));
     rectangle.translate(15 + 10, 0);

     if (rectangle.x() >= rectangle0.width() - 10) {
       rectangle.moveLeft(rectangle0.x() + 10);
       rectangle.translate(0, 15 + 10);
     }
  }
}
