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

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "model/image.h"
#include "model/settings.h"
#include "ui/palette_display_controller.h"
#include "ui/quantization_control.h"
#include "ui/scale_control.h"

#include <QMainWindow>
#include <QStackedWidget>

class AlgorithmFactory;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

 private slots:
  void onOpen();
  void onSaveAs();
  void onFitToView();
  void onZoomIn();
  void onZoomOut();

  void onPlatformChanged();

  void onDownScaleControlChanged();
  void onProcess();

 private:
  void updateDonwScale();
  void preprocess();

  Ui::MainWindow* m_ui;
  AlgorithmFactory& m_algorithmFactory;
  Image m_image;

  ScaleControl* m_downScaleControl;
  QuantizationControl* m_quantizationControl;
  PaletteDisplayController* m_paletteDisplayController;
};

#endif  // !MAIN_WINDOW_H
