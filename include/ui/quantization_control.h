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

#ifndef QUANTIZATION_CONTROL_H_
#define QUANTIZATION_CONTROL_H_

#include "ui/settings_panel_controller.h"

#include <QComboBox>
#include <QGroupBox>
#include <QLabel>
#include <QStackedWidget>
#include <QVariant>
#include <QVBoxLayout>

enum class DitheringAlgorithm;

class QuantizationControl : public QGroupBox {
  Q_OBJECT
 public:
  explicit QuantizationControl(QWidget* parent = nullptr);

  int currentPaletteIndex() const;

  void addDithering(const QString& text, QWidget* widget, DitheringAlgorithm id);
  DitheringAlgorithm currentDitheringId() const;
  int currentDitheringIndex() const;

 public slots:

  void setDitheringIndex(int index);

 signals:

  void settingsChanged();

 private:
  QVBoxLayout* layout;
  QLabel* m_palettesLabel;
  QComboBox* m_palettesCombo;

  QLabel* m_ditheringLabel;
  QComboBox* m_ditheringComboBox;
  SettingsPanelController* m_ditheringSettingsPanel;
};

#endif  // !QUANTIZATION_CONTROL_H_
