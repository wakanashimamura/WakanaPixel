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

  connect(m_mode, &ResizeModeSelector::modeChanged, this, [this]() {
    updatePreset();

    switch (m_mode->mode()) {
      case ResizeMode::Width:
        m_size->setWidthEnabled(true);
        m_size->setHeightEnabled(false);
        break;

      case ResizeMode::Height:
        m_size->setWidthEnabled(false);
        m_size->setHeightEnabled(true);
        break;

      default:
        m_size->setWidthEnabled(true);
        m_size->setHeightEnabled(true);
        break;
    }

    emit ResizeControl::valueChanged(value());
  });
  connect(m_size, &ImageSizeSelector::valueChanged, this, [this]() {
    updatePreset();
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

  params.targetSize   = m_size->value();
  params.resizeMode   = m_mode->mode();
  params.roundingMode = m_rounding->mode();
  params.cropOffset   = m_crop->value();

  return params;
}


void ResizeControl::setResizeState(ResizeState state) {
  m_size->setValue(state.size);

  m_size->setWidthRange(state.minWidth, state.maxWidth);
  m_size->setHeightRange(state.minHeight, state.maxHeight);

  m_crop->setMaximum(state.maxCropOffset);
  m_crop->setAxis(state.cropAxis);
}

void ResizeControl::updatePreset() {
  QSize presetValue = m_size->presetValue();

  if (presetValue.isEmpty()) {
    return;
  }

  const QSignalBlocker blocker(m_size);

  if (presetValue.width() <= m_size->maximumWidth() &&
      presetValue.height() <= m_size->maximumHeight()) {
    m_size->setValue(presetValue);
  } else {
    m_size->setModeCustomPreset();
  }
}
