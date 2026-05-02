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

#include "core/image_processing.h"

#include "core/dithering.h"
#include "model/builtin_palettes.h"

QImage preprocessImage(
    const QImage& image,
    QSize size,
    RoundMode mode,
    DownScaleMode scaleMode,
    ResizeMode resizeMode,
    int position
) {
  QImage result;

  switch (scaleMode) {
    case DownScaleMode::Original:
    case DownScaleMode::Custom:
    case DownScaleMode::Width:
    case DownScaleMode::Height:
      result = scale(image, size, mode);
      break;

    case DownScaleMode::CustomCanvas:
    case DownScaleMode::Preset:
      if (resizeMode == ResizeMode::Fit) {
        result = fitImage(image, size, mode);
      } else {
        result = cropImage(image, size, position, mode);
      }
      break;

    default:
      break;
  }

  return result;
}

QImage processImage(const QImage& image, int indexBuiltPalette, IDithering& dither) {
  QImage result;

  Palette palette = kBuiltinPalettes[indexBuiltPalette];

  result = dither.apply(image, palette);

  return result;
}
