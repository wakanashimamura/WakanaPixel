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

#include "core/scale.h"
#include "model/settings.h"

#include <QImage>
#include <QSize>

class IDithering;
enum class PalettePosition;

[[nodiscard]] QImage preprocessImage(
    const QImage& image,
    QSize size,
    RoundMode mode,
    DownScaleMode scaleMode,
    ResizeMode resizeMode,
    int position
);

[[nodiscard]] QImage processImage(
    const QImage& image, int indexBuiltPalette, IDithering& dither, PalettePosition position
);
