// WakanaPixel - Converts photos into pixelated images
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

#include "wsgraphicsview.h"

WSGraphicsView::WSGraphicsView(QWidget* parent)
  : QGraphicsView (parent), m_scene (new QGraphicsScene (this)), m_scaleFactor (1.10)
{
  setScene (m_scene);

  // enable dragging
  setDragMode (QGraphicsView::ScrollHandDrag);

  // remove scroll bars 
  setHorizontalScrollBarPolicy (Qt::ScrollBarAlwaysOff);
  setVerticalScrollBarPolicy (Qt::ScrollBarAlwaysOff);
}

WSGraphicsView::~WSGraphicsView()
{
  delete m_scene;
}

void WSGraphicsView::loadImage (const QImage& image) {
  QPixmap pixmap = QPixmap::fromImage(image);

  m_scene->clear ();
  m_scene->addPixmap (pixmap);
  m_scene->setSceneRect (pixmap.rect());
  FitImageToView();
}

void WSGraphicsView::FitImageToView()
{
  if (!scene() || scene()->items().isEmpty()) return;

  // reset view
  resetTransform();

  fitInView(scene()->sceneRect(), Qt::KeepAspectRatio);
}

void WSGraphicsView::wheelEvent (QWheelEvent* event) {
  ViewportAnchor oldAnchor = transformationAnchor ();

  setTransformationAnchor (QGraphicsView::AnchorUnderMouse);

  if (event->angleDelta().y() > 0) {
    // Zoom in
    scale(m_scaleFactor, m_scaleFactor);
  } else {
    // Zoom out
    scale(1.0 / m_scaleFactor, 1.0 / m_scaleFactor);
  }

  setTransformationAnchor (oldAnchor);
} 