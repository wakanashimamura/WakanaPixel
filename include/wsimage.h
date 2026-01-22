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

#ifndef WSIMAGE_H
#define WSIMAGE_H

#include <QImage>
#include <QString>

class WSImage {
 public:
  bool load(const QString &filePath) {
    if (filePath.isEmpty()) {
      return false;
    }

    if (!m_orginal.load(filePath)) {
      return false;
    }

    m_edited = m_orginal;
    return true;
  }

  bool save(const QString &filePath) const {
    if (filePath.isEmpty()) {
      return false;
    }

    if (!m_edited.save(filePath)) {
      return false;
    }

    return true;
  }
  void setEdited(const QImage &image) { m_edited = image; }

  QImage original() const { return m_orginal; }
  QImage edited() const { return m_edited; }

 private:
  QImage m_orginal;
  QImage m_edited;
};

#endif  // !WSIMAGE_H