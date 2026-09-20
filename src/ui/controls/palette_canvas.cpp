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

#include "palette_canvas.h"

#include <QColorDialog>
#include <QPainter>
#include <QResizeEvent>

PaletteCanvas::PaletteCanvas(QWidget* parent)
    : QWidget(parent),
      m_spacing(4),
      m_margins(0, 0, 0, 0) {}

QSize PaletteCanvas::minimumSizeHint() const {
  int minWidth = m_margins.left() + k_MinCellWidth + m_margins.right();

  int minheight = 0;
  if (m_palette.empty()) {
    minheight = m_margins.top() + k_CellHeight + m_margins.bottom();
  }

  return QSize(minWidth, 0);
}

int PaletteCanvas::heightForWidth(int width) const {
  if (m_palette.empty()) {
    return m_margins.top() + k_CellHeight + m_margins.bottom();
  }

  int row = std::ceil(static_cast<double>(m_palette.size()) / columnsForWidth(width));
  return m_margins.top() + (k_CellHeight * row) + (m_spacing * (row - 1)) + m_margins.bottom();
}

void PaletteCanvas::setPalette(const Palette& palette) {
  m_palette = palette;
  updateGeometry();
}

void PaletteCanvas::paintEvent(QPaintEvent* event) {
  if (m_palette.empty()) {
    return;
  }

  QPainter painter(this);

  for (int i = 0; i < m_palette.size(); ++i) {
    painter.fillRect(cellRectAtIndex(i), QColor(m_palette.rgb(i).color()));
  }
}

void PaletteCanvas::mousePressEvent(QMouseEvent* event) {
  if (event->button() == Qt::LeftButton && !m_palette.empty()) {
    int index = indexAtposition(event);

    if (index < 0) {
      return;
    }

    QColor initialColor = m_palette.color(index);
    QColor selectedColor;

    QColorDialog dialog(initialColor);

    if (dialog.exec() == QDialog::Accepted) {
      selectedColor = dialog.selectedColor();
      m_palette.setColor(index, selectedColor.rgb());
      update();
      emit paletteChanged(m_palette);
    }
  }
}

void PaletteCanvas::resizeEvent(QResizeEvent* event) {
  if (m_palette.empty()) {
    return;
  }

  m_maxColumns = columnsForWidth(event->size().width());

  int widthWithoutMargins = event->size().width() - m_margins.left() - m_margins.right();
  m_availableWidth        = widthWithoutMargins - m_spacing * (m_maxColumns - 1);
}

int PaletteCanvas::columnsForWidth(int width) const {
  int widthWithoutMargins = width - m_margins.left() - m_margins.right();

  // Calculate the maximum number of columns that can fit within the given width.
  // If the number of columns exceeds the number of colors in the palette,
  // use the palette size so that the cells can expand to fill the available width.

  int columns = std::min(widthWithoutMargins / (k_MinCellWidth + m_spacing), m_palette.size());

  // At least one column.
  return std::max(1, columns);
}

PaletteCanvas::CellPosition PaletteCanvas::cellPositionAtIndex(int index) const {
  int row = index / m_maxColumns;
  int col = index % m_maxColumns;

  CellPosition pos;

  // Divide the available width evenly between columns.
  // Integer division also distributes the remaining pixels between cells.
  pos.x0 = m_margins.left() + col * m_spacing + (col * m_availableWidth) / m_maxColumns;
  pos.x1 = m_margins.left() + col * m_spacing + ((col + 1) * m_availableWidth) / m_maxColumns;

  pos.y0 = m_margins.top() + row * (k_CellHeight + m_spacing);

  return pos;
}

QRect PaletteCanvas::cellRectAtIndex(int index) {
  CellPosition pos = cellPositionAtIndex(index);
  return QRect(pos.x0, pos.y0, pos.x1 - pos.x0, k_CellHeight);
}

int PaletteCanvas::indexAtposition(QMouseEvent* event) {
  QPoint pos = event->pos();
  if (pos.x() < m_margins.left() || pos.x() > (width() - 1) - m_margins.right()) {
    return -1;
  }

  if (pos.y() < m_margins.top() || pos.y() > (height() - 1) - m_margins.bottom()) {
    return -1;
  }

  int x = pos.x() - m_margins.left();
  int y = pos.y() - m_margins.top();

  int row = y / (k_CellHeight + m_spacing);

  int cellWidthAndSpace = m_availableWidth / m_maxColumns + m_spacing;

  int col = x / cellWidthAndSpace;

  // Since the remaining pixels are distributed between the cells,
  // their widths may differ by a few pixels. Therefore, the calculated
  // index is only approximate, so validateIndex() checks the current
  // and neighboring cells to determine the exact cell under the cursor.
  int inexactIndex = row * m_maxColumns + col;

  return validateIndex(inexactIndex, pos);
}

int PaletteCanvas::validateIndex(int index, QPoint pos) {
  if (index < m_palette.size()) {
    CellPosition cellPos = cellPositionAtIndex(index);

    if (pos.x() >= cellPos.x0 && pos.x() < cellPos.x1) {
      return index;
    }
  }

  const int previousIndex = index - 1;
  if (previousIndex >= 0 && previousIndex < m_palette.size() - 1) {
    CellPosition cellPos = cellPositionAtIndex(previousIndex);

    if (pos.x() >= cellPos.x0 && pos.x() < cellPos.x1) {
      return previousIndex;
    }
  }

  const int nextIndex = index + 1;
  if (nextIndex < m_palette.size()) {
    CellPosition cellPos = cellPositionAtIndex(nextIndex);

    if (pos.x() >= cellPos.x0 && pos.x() < cellPos.x1) {
      return nextIndex;
    }
  }

  return -1;
}