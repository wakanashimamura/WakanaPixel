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

#ifndef MEDIAN_CUT_H_
#define MEDIAN_CUT_H_

#include "core/palette_generator.h"

class MedianCut final : public IPaletteGenerator {
 public:
  [[nodiscard]] Palette apply(const QImage& image, int colorCount) override;
  [[nodiscard]] QGroupBox* createSettingsWidget(QWidget* parent = nullptr) override;
  [[nodiscard]] PaletteGenerator id() const override;
  [[nodiscard]] QString displayName() const override;
};

#endif  // !MEDIAN_CUT_H_
