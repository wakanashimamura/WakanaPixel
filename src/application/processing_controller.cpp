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

#include "processing_controller.h"

#include "processing/resize_geometry.h"

#include <thread>

ProcessingController::ProcessingController(QObject* parent)
    : QObject(parent),
      m_scaler(new NearestNeighborScaler) {}

void ProcessingController::openImage(const QString& filePath) {
  {
    std::lock_guard<std::mutex> lock(mtx);

    if (!m_imageDocument.load(filePath)) {
      return;
    }
  }

  emit imageLoaded(true);
  emit updateResizeControlValue(calculateAspectFitSize(
      m_imageDocument.originalImage().size(),
      {k_maxResizeImageSize, k_maxResizeImageSize}
  ));
  emit requestResize();
}

void ProcessingController::saveImage(const QString& filePath) {
  m_imageDocument.save(filePath);
}

void ProcessingController::resizeImage(ResizeParams params) {
  if (m_imageDocument.isNull() || params.size.isEmpty()) {
    return;
  }

  AspectFillResult fillResult =
      calculateAspectFillSize(m_imageDocument.originalImage().size(), params.size);

  ResizeControlStatus status;
  ResizeParamsLimit limit;

  status.axisCrop      = fillResult.fillReference;
  status.widthEnabled  = params.resizeMode == ResizeMode::Height ? false : true;
  status.heightEnabled = params.resizeMode == ResizeMode::Width ? false : true;
  status.cropVisible   = params.resizeMode == ResizeMode::Fill ? true : false;

  QSize resolvedSize  = params.size;
  limit.maxCropOffset = fillResult.maxCropOffset;

  if (params.resizeMode == ResizeMode::Width || params.resizeMode == ResizeMode::Height) {
    QSize maxFitSize = calculateAspectFitSize(
        m_imageDocument.originalImage().size(),
        {k_maxResizeImageSize, k_maxResizeImageSize}
    );
    limit.maxWidth  = maxFitSize.width();
    limit.maxHeight = maxFitSize.height();
  }

  if (params.resizeMode == ResizeMode::Width) {
    resolvedSize = calculateByWidth(m_imageDocument.originalImage().size(), params.size.width());
  } else if (params.resizeMode == ResizeMode::Height) {
    resolvedSize = calculateByHeight(m_imageDocument.originalImage().size(), params.size.height());
  }

  emit updateResizeControlStatus(status);
  emit updateResizeParamsLimit(limit);
  emit updateResizeControlValue(resolvedSize);

  if (m_isStartResize && !isResizeRequired) {
    isResizeRequired = true;
  }

  if (m_isStartResize) {
    return;
  }

  m_isStartResize = true;

  std::thread th(&ProcessingController::startResize, this, params);
  th.detach();
}

void ProcessingController::startResize(ResizeParams params) {
  std::lock_guard<std::mutex> lock(mtx);

  QImage image = resize(m_imageDocument.originalImage(), *m_scaler, params);
  m_imageDocument.setScaledImage(image);
  emit imageReadyDisplay(m_imageDocument.scaledImage());

  m_isStartResize = false;
  if (isResizeRequired) {
    isResizeRequired = false;
    emit requestResize();
  }
}
