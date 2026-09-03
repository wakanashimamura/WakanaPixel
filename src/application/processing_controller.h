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

#include "algorithms/scale/nearest_neighbor_scaler.h"
#include "control_types/resize_control_type.h"
#include "image/image_document.h"
#include "processing/resize_types.h"

#include <QObject>

#include <mutex>

class ProcessingController final : public QObject {
  Q_OBJECT

 public:
  explicit ProcessingController(QObject* parent = nullptr);

 public slots:
  void openImage(const QString& filePath);
  void saveImage(const QString& filePath);

  void imageProcessing(ResizeParams settings);

 signals:
  void imageLoaded(bool isLoaded);

  void imageReadyDisplay(const QImage& image);

  void updateResizeControlValue(QSize size);
  void updateResizeControlStatus(ResizeControlStatus status);
  void updateResizeParamsLimit(ResizeParamsLimit status);

 private:
  void startResize();

  void updateResizeControl(const ResizeParams& params);

 private:
  std::mutex m_mtxProcessing;
  std::mutex m_mtxParams;

  ImageDocument m_imageDocument;
  ScalingAlgorithm* m_scaler;

  ResizeParams m_lastParams;
  bool m_isProcessing = false;
};