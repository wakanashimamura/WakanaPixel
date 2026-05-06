// ================================================================================================
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

#include "core/image_painter.h"

#include "model/settings.h"

#include <QFont>
#include <QPainter>
#include <QPainterPath>
#include <QString>

QImage drawSignature(const QImage& image, const Palette& palette) {
  if (image.isNull()) {
    return image;
  }

  QImage result = image;

  RGB rgb = palette.findLightestColor();

  QFont font("Courier New", 9);
  font.setStyleStrategy(QFont::StyleStrategy(QFont::NoAntialias | QFont::NoSubpixelAntialias));

  QFontMetrics fm(font);

  QString program   = "WakanaPixel";
  QString colorText = QString::number(palette.size()) + " colors by ";
  QString screen    = Settings::currentPlatform().name() + " screen,";

  int maxWidth = result.width() - 5;

  QString finalText;
  if (fm.horizontalAdvance(program) > maxWidth)
    return result;

  finalText = program;

  if (fm.horizontalAdvance(colorText + finalText) <= maxWidth)
    finalText = colorText + finalText;

  if (fm.horizontalAdvance(screen + finalText) <= maxWidth)
    finalText = screen + finalText;

  int textW  = fm.horizontalAdvance(finalText);
  int ascent = fm.ascent();

  // Render text mask: white on black, no AA — avoids color bleeding
  QImage mask(textW + 2, fm.height() + 2, QImage::Format_Grayscale8);
  mask.fill(Qt::black);
  {
    QPainter mp(&mask);
    mp.setRenderHint(QPainter::TextAntialiasing, false);
    mp.setFont(font);
    mp.setPen(Qt::white);
    mp.drawText(0, ascent, finalText);
  }

  int x0 = result.width() - textW - 5;
  int y0 = result.height() - fm.descent();

  QRgb black   = qRgb(0, 0, 0);
  QRgb textRgb = qRgb(rgb.red, rgb.green, rgb.blue);

  // Pass 1: thin 4-direction outline (no diagonals — cleaner at 1px)
  constexpr std::array<std::pair<int, int>, 4> dirs{{{-1, 0}, {1, 0}, {0, -1}, {0, 1}}};
  for (int py = 0; py < mask.height(); py++) {
    const uchar* row = mask.constScanLine(py);
    for (int px = 0; px < mask.width(); px++) {
      if (row[px] < 128)
        continue;
      for (auto [ox, oy] : dirs) {
        int tx = x0 + px + ox;
        int ty = y0 - ascent + py + oy;
        if (tx >= 0 && tx < result.width() && ty >= 0 && ty < result.height())
          result.setPixel(tx, ty, black);
      }
    }
  }

  // Pass 2: draw text pixels on top with exact palette color (no blending)
  for (int py = 0; py < mask.height(); py++) {
    const uchar* row = mask.constScanLine(py);
    for (int px = 0; px < mask.width(); px++) {
      if (row[px] < 128)
        continue;
      int tx = x0 + px;
      int ty = y0 - ascent + py;
      if (tx >= 0 && tx < result.width() && ty >= 0 && ty < result.height())
        result.setPixel(tx, ty, textRgb);
    }
  }

  return result;
}

QImage drawPalette(
    const QImage& image, const Palette& palette, PalettePosition position, int paletteHeight
) {
  if (position == PalettePosition::None || image.isNull()) {
    return image;
  }

  const int penWidth    = 1;
  const int paletteSize = palette.size();
  const int imageWidth  = image.width();

  if (paletteSize * 4 > imageWidth) {
    return image;
  }

  QImage result(imageWidth, image.height() + paletteHeight, image.format());
  result.fill(Qt::black);

  QPainter painter(&result);
  painter.setRenderHint(QPainter::Antialiasing, false);

  const QPoint imageOffset(0, position == PalettePosition::Bottom ? 0 : paletteHeight);
  painter.drawImage(imageOffset, image);

  const int yOffset = (position == PalettePosition::Top) ? 0 : image.height();

  // -------- Let's draw the colors of the palette --------

  painter.setPen(Qt::NoPen);
  const Palette::RGBColorsType& rgbPalette = palette.rgbPalette();

  for (int i = 0; i < paletteSize; ++i) {
    const int xStart = (i * imageWidth) / paletteSize;
    const int xEnd   = ((i + 1) * imageWidth) / paletteSize;
    const int w      = xEnd - xStart;

    painter.setBrush(QColor::fromRgba(rgbPalette[i].argb));
    painter.drawRect(QRect(xStart, yOffset, w, paletteHeight));
  }

  // -------- Let's draw a frame --------

  QPen pen(Qt::black);
  pen.setWidth(penWidth);
  pen.setJoinStyle(Qt::MiterJoin);
  painter.setPen(pen);

  const int halfPen = penWidth / 2;
  const int yTop    = yOffset + halfPen;
  const int yBottom = yOffset + paletteHeight - (penWidth - halfPen);

  // Draw the top and bottom lines
  painter.drawLine(0, yTop, imageWidth - 1, yTop);
  painter.drawLine(0, yBottom, imageWidth - 1, yBottom);

  // Draw left and right lines
  painter.drawLine(halfPen, yTop, halfPen, yBottom);
  painter.drawLine(
      imageWidth - (penWidth - halfPen),
      yTop,
      imageWidth - (penWidth - halfPen),
      yBottom
  );

  // Draw vertical separators between colors
  for (int i = 1; i < paletteSize; ++i) {
    const int x = (i * imageWidth) / paletteSize;
    painter.drawLine(x, yTop, x, yBottom);
  }

  painter.end();
  return result;
}
