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

#include "nearest_neighbor_scaler.h"

#include "image/pixel_bits.h"

#include <QtAssert>

QImage NearestNeighborScaler::scale(const QImage& image, QSize size, ScalingParams* params) {
  Q_ASSERT_X(!image.isNull(), Q_FUNC_INFO, "Image that was sent is empty..");

  if (size.isEmpty()) {
    return QImage();
  }

  const NearestNeighborParams* specificParams = dynamic_cast<const NearestNeighborParams*>(params);

  Q_ASSERT_X(
      specificParams != nullptr,
      Q_FUNC_INFO,
      "Invalid scaling parameters type. Expected NearestNeighborParams."
  );

  QImage result(size, image.format());

  ReadOnlyPixelBits imageBits(image);
  MutablePixelBits resultBits(result);

  double scaleY = static_cast<double>(imageBits.height()) / size.height();
  double scaleX = static_cast<double>(imageBits.width()) / size.width();

  // Precompute X-coordinates to avoid repeated calculations.
  std::vector<int> pixelsX;
  pixelsX.reserve(size.width());
  for (int x = 0; x < size.width(); ++x) {
    // Map X coordinates to source pixels
    pixelsX.push_back(
        std::clamp(round(x * scaleX, specificParams->roundingMode), 0, imageBits.width() - 1)
    );
  }

  for (int y = 0; y < size.height(); ++y) {
    // Map Y coordinates to source pixels
    int pixelY =
        std::clamp(round(y * scaleY, specificParams->roundingMode), 0, imageBits.height() - 1);

    for (int x = 0; x < size.width(); ++x) {
      resultBits[y][x] = imageBits[pixelY][pixelsX[x]];
    }
  }
  return result;
}

ScalingAlgorithmType NearestNeighborScaler::type() const {
  return ScalingAlgorithmType::NearestNeighbor;
}

QString NearestNeighborScaler::name() const {
  return QString("Nearest Neighbor");
}
