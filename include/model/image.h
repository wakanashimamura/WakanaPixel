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

#ifndef IMAGE_H_
#define IMAGE_H_

#include <QImage>
#include <QSize>
#include <QString>

class Image {
 public:
  explicit Image() = default;
  explicit Image(const QString& path) { open(path); }

  explicit operator bool() const { return isLoaded(); }

  bool open(const QString& path);
  bool save(const QString& path) const;

  [[nodiscard]] const QImage& original() const { return m_original; }
  [[nodiscard]] const QImage& preprocess() const { return m_preprocess; }
  [[nodiscard]] const QImage& processed() const { return m_processed; }
  [[nodiscard]] const QString& filePath() const { return m_filePath; }
  [[nodiscard]] bool isLoaded() const { return m_isLoaded; }

  [[nodiscard]] QSize originalSize() const { return m_original.size(); }
  [[nodiscard]] QSize preprocessSize() const { return m_preprocess.size(); }
  [[nodiscard]] QSize processedSize() const { return m_processed.size(); }

  bool setPreprocess(const QImage& image);
  bool setProcessed(const QImage& image);
  void resetProcessed() { m_processed = m_original; }

 private:
  QImage m_original;
  QImage m_preprocess;
  QImage m_processed;
  QString m_filePath;
  bool m_isLoaded = false;
};

#endif  // !IMAGE_H_
