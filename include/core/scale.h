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

#ifndef NEAREST_NEIGHBOR_SCALE_H_
#define NEAREST_NEIGHBOR_SCALE_H_

#include "core/utils.h"

#include <QImage>
#include <QSize>

struct DownScaleData;

enum class ResizeMode { Fit, Crop };
enum class CropMode { Horizontal, Vertical };

struct DownScaleConfig {
  QSize targetSize;
  QSize range;
  bool widthEnabled{};
  bool heightEnabled{};
  bool ResizeModeDisabled{};
};

struct CropGeometry {
  QSize size;
  int maxPosition;
  CropMode mode;
};

QSize calcScaledSize(const QSize& imageSize, const QSize& screenSize);

QSize calcWidthFromHeight(const QSize& imageSize, int height);
QSize calcHeightFromWidth(const QSize& imageSize, int width);

QImage scale(const QImage& image, QSize size, RoundMode mode = RoundMode::Round);

QImage upScale(const QImage& image, int factor);

DownScaleConfig buildDownScaleConfig(
    DownScaleData& data, const QSize& imageSize, const QSize& screenSize, const QSize& currentScale
);

CropGeometry computeCropGeometry(QSize imageSize, QSize screenSize);

QImage fitImage(const QImage& image, QSize screenSize, RoundMode mode = RoundMode::Round);

QImage cropImage(
    const QImage& image, QSize screenSize, int position, RoundMode mode = RoundMode::Round
);

#endif  // !NEAREST_NEIGHBOR_SCALE_H_
