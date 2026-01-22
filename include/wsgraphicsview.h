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

#ifndef WSGRAPHICSVIEW_H
#define WSGRAPHICSVIEW_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QWheelEvent>

class WSGraphicsView : public QGraphicsView {
  Q_OBJECT

 public:
  explicit WSGraphicsView(QWidget *parent = nullptr);

  bool setImage(const QImage &image);
  void fitToView();

 protected:
  void wheelEvent(QWheelEvent *event) override;

 private:
  QGraphicsScene *m_scene;
  QGraphicsPixmapItem *m_image;

  const double k_scaleFactor = 1.10;
};

#endif  // WSGRAPHICSVIEW_H