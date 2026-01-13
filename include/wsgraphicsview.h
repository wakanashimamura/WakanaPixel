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

#ifndef WSGRAPHICSVIEW_H
#define WSGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QWheelEvent>
#include <QGraphicsScene>

class WSGraphicsView : public QGraphicsView 
{
  Q_OBJECT

public:
  explicit WSGraphicsView(QWidget* parent = nullptr);
  ~WSGraphicsView();

  void loadImage(const QImage& image);
  void FitImageToView();
  
protected:
  void wheelEvent(QWheelEvent* event) override;

private:
  QGraphicsScene *m_scene;
  double m_scaleFactor;
};

#endif // WSGRAPHICSVIEW_H