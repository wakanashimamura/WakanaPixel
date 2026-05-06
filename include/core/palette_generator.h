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

#ifndef PALETTE_GENERATOR_H_
#define PALETTE_GENERATOR_H_

#include "color/rgb.h"
#include "model/palette.h"

#include <QGroupBox>
#include <QImage>
#include <QString>

#include <vector>

enum class PaletteGenerator { MedianCut, None };

class IPaletteGenerator {
 public:
  [[nodiscard]] virtual Palette apply(const QImage& image, int colorCount)         = 0;
  [[nodiscard]] virtual QGroupBox* createSettingsWidget(QWidget* parent = nullptr) = 0;
  [[nodiscard]] virtual PaletteGenerator id() const                                = 0;
  [[nodiscard]] virtual QString displayName() const                                = 0;

  virtual ~IPaletteGenerator() = default;
};

#endif  // !PALETTE_GENERATOR_H_
