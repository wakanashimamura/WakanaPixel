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

#include "resize_types.h"

#include <QSize>

QSize resizeRect(const QSize& sourceSize, const QSize& targetSize, ResizeMode mode);

QSize fitRect(const QSize& sourceSize, const QSize& targetSize);

QSize fitWithoutUpscaling(const QSize& sourceSize, const QSize& targetSize);

QSize fillRect(const QSize& sourceSize, const QSize& targetSize);

QSize calculateHeight(const QSize& sourceSize, int width);

QSize calculateWidth(const QSize& sourceSize, int height);

CropAxis defineCropAxis(const QSize& filledSize, const QSize& targetSize);

int maxCropOffset(CropAxis axis, const QSize& filledSize, const QSize& targetSize);
