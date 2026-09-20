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

#include "image/palette.h"

#include <QMargins>
#include <QRect>
#include <QWidget>

class PaletteCanvas : public QWidget {
  Q_OBJECT

 public:
  explicit PaletteCanvas(QWidget* parent = nullptr);

  [[nodiscard]] const Palette& palette() const { return m_palette; }

  QSize minimumSizeHint() const override;

  // Tell the layout system that height depends on width.
  bool hasHeightForWidth() const override { return true; }
  int heightForWidth(int width) const override;

 public slots:
  void setPalette(const Palette& palette);

 signals:
  void paletteChanged(const Palette& palette);

 protected:
  void paintEvent(QPaintEvent* event) override;
  void mousePressEvent(QMouseEvent* event) override;
  void resizeEvent(QResizeEvent* event) override;

 private:
  struct CellPosition {
    int x0;
    int x1;
    int y0;
  };

  // Returns the number of columns that fit within the specified width.
  int columnsForWidth(int width) const;

  CellPosition cellPositionAtIndex(int index) const;
  QRect cellRectAtIndex(int index);
  int indexAtposition(QMouseEvent* event);
  int validateIndex(int index, QPoint pos);

  static constexpr int k_MinCellWidth = 35;
  static constexpr int k_CellHeight   = 25;

  int m_spacing{};
  QMargins m_margins;

  int m_maxColumns{};
  int m_availableWidth{};

  Palette m_palette;
};
