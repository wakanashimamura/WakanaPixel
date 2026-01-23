// ================================================================================================
//
// WakanaPixel - This software for creating digital art converts picture into pixel art.
// What is pixel art - https://en.wikipedia.org/wiki/Pixel_art.
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

#include "wsimageprocessing.h"

QImage ws::nearestNeighborScale(QImage srcImage, int dstWidth, int dstHeight,
                                double (*roundFunc)(double)) {
  // Return empty image if input is invalid, use default rounding if needed
  if (srcImage.isNull()) {
    return srcImage;
  }
  if (dstWidth <= 0 || dstHeight <= 0) {
    return QImage();
  }
  if (!roundFunc) {
    roundFunc = &std::round;
  }

  // Convert to ARGB32 if necessary to simplify per-pixel operations.
  if (srcImage.format() != QImage::Format_ARGB32 && srcImage.format() != QImage::Format_RGB32) {
    srcImage = srcImage.convertToFormat(QImage::Format_ARGB32);
  }

  QImage dstImage(dstWidth, dstHeight, srcImage.format());

  const uchar *srcBits = srcImage.constBits();
  uchar *dstBits = dstImage.bits();

  int srcBytesPerLine = srcImage.bytesPerLine();
  int dstBytesPerLine = dstImage.bytesPerLine();
  int srcWidth = srcImage.width();
  int srcHeight = srcImage.height();

  // Calculate the scaling factor determine how much larger or smaller the output image will be
  double scaleY = static_cast<double>(srcHeight) / dstHeight;
  double scaleX = static_cast<double>(srcWidth) / dstWidth;

  // Precompute X-coordinates to avoid repeated calculations, improving performance.
  std::vector<int> srcPixelsX(dstWidth);
  for (int x = 0; x < dstWidth; ++x) {
    // Map X coordinates to source pixels
    srcPixelsX[x] = std::clamp(static_cast<int>(roundFunc(x * scaleX)), 0, srcWidth - 1);
  }

  for (int y = 0; y < dstHeight; ++y) {
    // Map Y coordinates to source pixels
    int sourcePixelY = std::clamp(static_cast<int>(roundFunc(y * scaleY)), 0, srcHeight - 1);

    // Conversion to 32-bit format for easier work with pixels.
    const uint32_t *srcRow32 =
        reinterpret_cast<const uint32_t *>(srcBits + (sourcePixelY * srcBytesPerLine));
    uint32_t *dstRow32 = reinterpret_cast<uint32_t *>(dstBits + (y * dstBytesPerLine));

    for (int x = 0; x < dstWidth; ++x) {
      // Copy color from nearest source pixel.
      dstRow32[x] = srcRow32[srcPixelsX[x]];
    }
  }
  return dstImage;
}

// For readability: calls nearestNeighborScale
QImage ws::downscale(QImage srcImage, int dstWidth, int dstHeight, double (*roundFunc)(double)) {
  return nearestNeighborScale(srcImage, dstWidth, dstHeight, roundFunc);
}
QImage ws::upscale(QImage srcImage, int dstWidth, int dstHeight, double (*roundFunc)(double)) {
  return nearestNeighborScale(srcImage, dstWidth, dstHeight, roundFunc);
}
