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

#include "image_document.h"

bool ImageDocument::load(const QString& filePath) {
  QImage image;
  if (filePath.isEmpty() || !image.load(filePath)) {
    return false;
  }

  m_originalImage = image.convertToFormat(QImage::Format_RGB32);

  return true;
}

bool ImageDocument::save(const QString& filePath) const {
  return !filePath.isEmpty() && m_originalImage.save(filePath);
}

bool ImageDocument::isNull() const noexcept {
  return m_originalImage.isNull();
}

const QImage& ImageDocument::originalImage() const noexcept {
  return m_originalImage;
}
