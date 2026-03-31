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

#include "model/image.h"

bool Image::open(const QString& path) {
  if (path.isEmpty()) {
    return false;
  }

  if (!m_original.load(path)) {
    return false;
  }

  if (m_original.format() != QImage::Format_ARGB32 && m_original.format() != QImage::Format_RGB32) {
    m_original = m_original.convertToFormat(QImage::Format_RGB32);
  }

  m_filePath  = path;
  m_processed = m_original;
  m_isLoaded  = true;

  return true;
}

bool Image::save(const QString& path) const {
  if (path.isEmpty()) {
    return false;
  }

  if (!m_processed.save(path)) {
    return false;
  }

  return true;
}

bool Image::setProcessed(const QImage& image) {
  if (image.isNull()) {
    return false;
  }
  m_processed = image;

  return true;
}