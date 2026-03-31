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

#include "core/pixel_bits.h"

#include <vector>

namespace {

int round(double value, RoundMode mode) {
  switch (mode) {
    case RoundMode::kFloor:
      return static_cast<int>(std::floor(value));
    case RoundMode::kRound:
      return static_cast<int>(std::round(value));
    case RoundMode::kCeil:
      return static_cast<int>(std::ceil(value));
    default:
      return value;
  }
}

QImage nearestNeighborScale(const QImage& srcImage, int dstWidth, int dstHeight, RoundMode mode) {
  // Return empty image if input is invali
  if (srcImage.isNull()) {
    return srcImage;
  }
  if (dstWidth <= 0 || dstHeight <= 0) {
    return QImage();
  }

  QImage dstImage(dstWidth, dstHeight, srcImage.format());

  PixelBits dstBits(dstImage);
  ConstPixelBits srcBits(srcImage);

  int srcWidth  = srcBits.width();
  int srcHeight = srcBits.height();

  // Calculate the scaling factor determine how much larger or smaller the output image will be
  double scaleY = static_cast<double>(srcHeight) / dstHeight;
  double scaleX = static_cast<double>(srcWidth) / dstWidth;

  // Precompute X-coordinates to avoid repeated calculations, improving performance.
  std::vector<int> srcPixelsX;
  srcPixelsX.reserve(dstWidth);
  for (int x = 0; x < dstWidth; ++x) {
    // Map X coordinates to source pixels
    srcPixelsX.push_back(std::clamp(round(x * scaleX, mode), 0, srcWidth - 1));
  }

  for (int y = 0; y < dstHeight; ++y) {
    // Map Y coordinates to source pixels
    int srcPixelY = std::clamp(round(y * scaleY, mode), 0, srcHeight - 1);

    for (int x = 0; x < dstWidth; ++x) {
      dstBits[y][x] = srcBits[srcPixelY][srcPixelsX[x]];
    }
  }
  return dstImage;
}

}  // namespace

QImage downscale(const QImage& srcImage, int dstWidth, int dstHeight, RoundMode mode) {
  return nearestNeighborScale(srcImage, dstWidth, dstHeight, mode);
}

QImage upscale(const QImage& srcImage, int dstWidth, int dstHeight, RoundMode mode) {
  return nearestNeighborScale(srcImage, dstWidth, dstHeight, mode);
}

QImage upscale(const QImage& srcImage, int factor, RoundMode mode) {
  if (factor <= 0) {
    return srcImage;
  }

  return nearestNeighborScale(srcImage, srcImage.width() * factor, srcImage.height() * factor,
                              mode);
}
