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

#include "image_view.h"

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QImage>
#include <QWheelEvent>

ImageView::ImageView(QWidget* parent)
    : QGraphicsView(parent),
      m_scene(new QGraphicsScene(this)),
      m_imageItem(new QGraphicsPixmapItem()) {
  // Link the scene to the view
  setScene(m_scene);

  // Add item to the scene
  m_scene->addItem(m_imageItem);

  // Allow dragging with the mouse
  setDragMode(QGraphicsView::ScrollHandDrag);

  // Disable scrollbars
  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  // Scaling relative to cursor
  setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

  // Better image update
  setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);

  setRenderHint(QPainter::Antialiasing, false);
  setRenderHint(QPainter::SmoothPixmapTransform, false);
}

void ImageView::fitImage() {
  if (!m_imageItem->pixmap().isNull()) {
    resetTransform();
    QGraphicsView::fitInView(m_imageItem, Qt::KeepAspectRatio);
  }
}

void ImageView::zoomIn() {
  if (m_imageItem->pixmap().isNull()) {
    return;
  }
  const double nextScale = transform().m11() * k_zoomFactor;

  if (nextScale < k_maximumScale) {
    QGraphicsView::scale(k_zoomFactor, k_zoomFactor);
  }
}

void ImageView::zoomOut() {
  if (m_imageItem->pixmap().isNull()) {
    return;
  }
  const double nextScale = transform().m11() * (1.0 / k_zoomFactor);

  if (nextScale > k_minimumScale) {
    QGraphicsView::scale(1.0 / k_zoomFactor, 1.0 / k_zoomFactor);
  }
}

void ImageView::setImage(const QImage& image) {
  m_imageItem->setPixmap(QPixmap::fromImage(image));
  m_scene->setSceneRect(m_imageItem->pixmap().rect());
}

void ImageView::wheelEvent(QWheelEvent* event) {
  if (event->angleDelta().y() > 0) {
    zoomIn();
  } else {
    zoomOut();
  }
}