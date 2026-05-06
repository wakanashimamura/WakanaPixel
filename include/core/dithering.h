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

#ifndef DITHERING_H_
#define DITHERING_H_

#include "model/palette.h"
#include "ui/dithering_settings_control.h"

#include <QGroupBox>
#include <QImage>
#include <QPointer>

enum class DitheringAlgorithm { None, FloydSteinberg };

// ----------------------------------------------------------------------------------------------
// IDithering
// ----------------------------------------------------------------------------------------------

class IDithering {
 public:
  [[nodiscard]] virtual QImage apply(const QImage& image, const Palette& palette)  = 0;
  [[nodiscard]] virtual QGroupBox* createSettingsWidget(QWidget* parent = nullptr) = 0;
  [[nodiscard]] virtual DitheringAlgorithm id() const                              = 0;
  [[nodiscard]] virtual QString displayName() const                                = 0;

  virtual ~IDithering() = default;
};

// ----------------------------------------------------------------------------------------------
// NoDithering
// ----------------------------------------------------------------------------------------------

class NoDithering : public IDithering {
 public:
  [[nodiscard]] QImage apply(const QImage& image, const Palette& palette) override;
  [[nodiscard]] QGroupBox* createSettingsWidget(QWidget* parent = nullptr) override;
  [[nodiscard]] DitheringAlgorithm id() const override;
  [[nodiscard]] QString displayName() const override;

 private:
  QPointer<DitheringSettingsControl> m_settingsWidget;
};

// ----------------------------------------------------------------------------------------------
// FloydSteinbergDithering
// ----------------------------------------------------------------------------------------------

class FloydSteinbergDithering : public IDithering {
 public:
  [[nodiscard]] QImage apply(const QImage& image, const Palette& palette) override;
  [[nodiscard]] QGroupBox* createSettingsWidget(QWidget* parent = nullptr) override;
  [[nodiscard]] DitheringAlgorithm id() const override;
  [[nodiscard]] QString displayName() const override;

 private:
  struct DitherColorError {
    int red{};
    int green{};
    int blue{};
  };

  static void diffuseError(DitherColorError& erorr, int weight, const DitherColorError& quantError);

  QPointer<FloydSteinbergSettingsControl> m_settingsWidget;
};

#endif  // !DITHERING_H_
