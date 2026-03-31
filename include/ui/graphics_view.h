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

#ifndef GRAPHICS_VIEW_H_
#define GRAPHICS_VIEW_H_

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QWheelEvent>

class GraphicsView : public QGraphicsView {
  Q_OBJECT

 public:
  explicit GraphicsView(QWidget* parent = nullptr);

  bool setImage(const QImage& image);
  void fitToView();
  void zoomIn();
  void zoomOut();

 protected:
  void wheelEvent(QWheelEvent* event) override;

 private:
  QGraphicsScene* m_scene;
  QGraphicsPixmapItem* m_image;

  static constexpr double k_scaleFactor = 1.10;
  static constexpr double k_minScale    = 0.05;  // 5%
  static constexpr double k_maxScale    = 50.0;  // 5000%
};

#endif  // GRAPHICS_VIEW_H_