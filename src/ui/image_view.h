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

#include <QGraphicsView>

class QGraphicsPixmapItem;
class QGraphicsScene;

class ImageView final : public QGraphicsView {
  Q_OBJECT

 public:
  explicit ImageView(QWidget* parent = nullptr);

  void fitImage();
  void zoomIn();
  void zoomOut();

 public slots:
  void setImage(const QImage& image);

 protected:
  void wheelEvent(QWheelEvent* event) override;

 private:
  QGraphicsScene* m_scene;
  QGraphicsPixmapItem* m_imageItem;

  static constexpr double k_zoomFactor   = 1.10;
  static constexpr double k_minimumScale = 0.05;  // 5%
  static constexpr double k_maximumScale = 50.0;  // 5000%
};