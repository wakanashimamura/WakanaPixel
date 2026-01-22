// ================================================================================================
//
// WakanaPixel - This software for creating digital art converts picture into pixel art.
// What is pixel art - https://en.wikipedia.org/wiki/Pixel_art.
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

#include "wsgraphicsview.h"

WSGraphicsView::WSGraphicsView(QWidget *parent)
    : QGraphicsView(parent), m_scene(new QGraphicsScene(this)), m_image(new QGraphicsPixmapItem()) {
  // Link the scene to the view
  setScene(m_scene);

  // Add item to the scene
  m_scene->addItem(m_image);

  // Allow dragging with the mouse
  setDragMode(QGraphicsView::ScrollHandDrag);

  // Disable scrollbars
  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  // Scaling relative to cursor
  setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

  // Better image update
  setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
}

bool WSGraphicsView::setImage(const QImage &image) {
  if (image.isNull()) {
    return false;
  }

  m_image->setPixmap(QPixmap::fromImage(image));
  m_image->setPos(0, 0);
  m_scene->setSceneRect(m_image->pixmap().rect());

  return true;
}

void WSGraphicsView::fitToView() {
  if (!m_image->pixmap().isNull()) {
    resetTransform();
    QGraphicsView::fitInView(m_image, Qt::KeepAspectRatio);
  }
}

void WSGraphicsView::wheelEvent(QWheelEvent *event) {
  if (m_image->pixmap().isNull()) {
    return;
  }

  if (event->angleDelta().y() > 0) {
    // Zoom in
    scale(k_scaleFactor, k_scaleFactor);
  } else {
    // Zoom out
    scale(1.0 / k_scaleFactor, 1.0 / k_scaleFactor);
  }
}