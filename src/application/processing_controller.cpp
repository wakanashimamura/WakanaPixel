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

#include "processing/resize.h"
#include "processing/resize_utils.h"

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
  emit requestResize();
}

void ProcessingController::saveImage(const QString& filePath) {
  std::lock_guard<std::mutex> lock(mtx);
  m_imageDocument.save(filePath);
}

void ProcessingController::resizeImage(ResizeParams params) {
  if (m_imageDocument.isNull() || params.targetSize.isEmpty()) {
    return;
  }

  updateResizeControl(params);

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

void ProcessingController::updateResizeControl(const ResizeParams& params) {
  ResizeControlStatus status;
  ResizeParamsLimit limit;
  QSize size = params.targetSize;

  status.axisCrop = CropAxis::None;

  if (params.resizeMode == ResizeMode::Fill) {
    QSize filledSize    = fillRect(m_imageDocument.originalImage().size(), params.targetSize);
    status.axisCrop     = defineCropAxis(filledSize, params.targetSize);
    limit.maxCropOffset = maxCropOffset(status.axisCrop, filledSize, params.targetSize);
  }

  if (params.resizeMode == ResizeMode::Width || params.resizeMode == ResizeMode::Height) {
    if (params.resizeMode == ResizeMode::Width) {
      status.heightEnabled = false;
      size = calculateHeight(m_imageDocument.originalImage().size(), params.targetSize.width());
    } else {
      status.widthEnabled = false;
      size = calculateWidth(m_imageDocument.originalImage().size(), params.targetSize.height());
    }

    QSize maxFitSize = fitRect(
        m_imageDocument.originalImage().size(),
        QSize(k_maxResizeImageSize, k_maxResizeImageSize)
    );

    limit.maxWidth  = maxFitSize.width();
    limit.maxHeight = maxFitSize.height();
  }

  emit updateResizeControlStatus(status);
  emit updateResizeParamsLimit(limit);
  emit updateResizeControlValue(size);
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
