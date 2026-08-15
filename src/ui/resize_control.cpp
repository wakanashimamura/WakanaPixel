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

#include "resize_control.h"

#include "controls/crop_position_selector.h"
#include "controls/image_size_selector.h"
#include "controls/resize_mode_selector.h"
#include "controls/rounding_mode_selector.h"
#include "processing/resize.h"

#include <QVBoxLayout>

ResizeControl::ResizeControl(QWidget* parent)
    : QGroupBox("Resize", parent),
      m_mode(new ResizeModeSelector(this)),
      m_size(new ImageSizeSelector(this)),
      m_crop(new CropPositionSelector(this)),
      m_rounding(new RoundingModeSelector(this)) {
  QVBoxLayout* layout = new QVBoxLayout(this);

  layout->addWidget(m_mode);
  layout->addWidget(m_size);
  layout->addWidget(m_crop);
  layout->addWidget(m_rounding);

  setStatus(ResizeControlStatus());
  setLimit(ResizeParamsLimit());

  connect(m_mode, &ResizeModeSelector::modeChanged, this, [this]() {
    emit ResizeControl::valueChanged(value());
  });
  connect(m_size, &ImageSizeSelector::valueChanged, this, [this]() {
    emit ResizeControl::valueChanged(value());
  });
  connect(m_crop, &CropPositionSelector::valueChanged, this, [this]() {
    emit ResizeControl::valueChanged(value());
  });
  connect(m_rounding, &RoundingModeSelector::modeChanged, this, [this]() {
    emit ResizeControl::valueChanged(value());
  });
}

ResizeParams ResizeControl::value() {
  ResizeParams params;

  params.size         = m_size->value();
  params.resizeMode   = m_mode->mode();
  params.roundingMode = m_rounding->mode();
  params.cropOffset   = m_crop->value();

  return params;
}

void ResizeControl::setSize(QSize size) {
  const QSignalBlocker blockSize(m_size);
  m_size->setValue(size);
}

void ResizeControl::setStatus(ResizeControlStatus status) {
  m_size->setWidthEnabled(status.widthEnabled);
  m_size->setHeightEnabled(status.heightEnabled);

  m_crop->setVisible(status.cropVisible);
  m_crop->setAxis(status.axisCrop);
}

void ResizeControl::setLimit(ResizeParamsLimit limit) {
  m_size->setWidthRange(limit.minWidth, limit.maxWidth);
  m_size->setHeightRange(limit.minHeight, limit.maxHeight);

  m_crop->setMaximum(limit.maxCropOffset);
}
