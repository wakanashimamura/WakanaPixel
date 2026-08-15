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

#include "algorithms/scale/scaling_algorithm.h"

#include <QImage>

enum class ResizeMode { Original, Exact, Fit, Fill, Width, Height };

struct ResizeParams {
  QSize size;
  ResizeMode resizeMode;
  RoundingMode roundingMode;
  int cropOffset = 0;
};

QImage resize(const QImage& image, const ScalingAlgorithm& scaler, ResizeParams params);

QImage resizeToFitWithPadding(
    const QImage& image, QSize size, const ScalingAlgorithm& scaler, const RoundingMode roundingMode
);

QImage resizeToFit(
    const QImage& image, QSize size, const ScalingAlgorithm& scaler, const RoundingMode roundingMode
);

QImage resizeToFill(
    const QImage& image,
    QSize size,
    int cropOffset,
    const ScalingAlgorithm& scaler,
    const RoundingMode roundingMode
);

QImage resizeByWidth(
    const QImage& image, int width, const ScalingAlgorithm& scaler, const RoundingMode roundingMode
);

QImage resizeByHeight(
    const QImage& image, int height, const ScalingAlgorithm& scaler, const RoundingMode roundingMode
);
