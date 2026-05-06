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

#include "ui/main_window.h"

#include "core/algorithm_factory.h"
#include "core/image_processing.h"
#include "core/median_cut.h"
#include "core/scale.h"
#include "ui_main_window.h"

#include <QFileDialog>
#include <QImage>
#include <QString>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      m_ui(new Ui::MainWindow),
      m_algorithmFactory(AlgorithmFactory::create()) {
  m_ui->setupUi(this);

  // -------- Menu Bar --------

  // clang-format off
  connect(m_ui->actionOpen,      &QAction::triggered, this, &MainWindow::onOpen);
  connect(m_ui->actionSaveAs,    &QAction::triggered, this, &MainWindow::onSaveAs);
  connect(m_ui->actionFitToView, &QAction::triggered, this, &MainWindow::onFitToView);
  connect(m_ui->actionZoomIn,    &QAction::triggered, this, &MainWindow::onZoomIn);
  connect(m_ui->actionZoomOut,   &QAction::triggered, this, &MainWindow::onZoomOut);
  // clang-format on

  // -------- -------- --------

  QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(m_ui->scrollContents->layout());

  // -------- Down Scale --------

  m_downScaleControl = new ScaleControl(m_ui->scrollContents);

  layout->insertWidget(layout->indexOf(m_ui->verticalSpacer), m_downScaleControl);
  m_downScaleControl->setTitle("DOWN SCALE");

  connect(
      m_downScaleControl,
      &ScaleControl::settingsChanged,
      this,
      &MainWindow::onDownScaleControlChanged
  );

  connect(m_downScaleControl, &ScaleControl::settingsChanged, this, &MainWindow::preprocess);

  // -------- QuantizationControl --------

  m_quantizationControl = new QuantizationControl(m_ui->scrollContents);
  layout->insertWidget(layout->indexOf(m_downScaleControl) + 1, m_quantizationControl);

  std::vector<DitheringAlgorithm> ditheringIds = m_algorithmFactory.availableDitheringAlgorithms();

  for (DitheringAlgorithm id : ditheringIds) {
    IDithering& dithering = m_algorithmFactory.dithering(id);

    QWidget* w = dithering.createSettingsWidget();
    m_quantizationControl->addDithering(dithering.displayName(), w, dithering.id());
  }
  m_quantizationControl->setDitheringIndex(0);

  // -------- -------- --------

  m_paletteDisplayController = new PaletteDisplayController(this);

  layout->insertWidget(layout->indexOf(m_quantizationControl) + 1, m_paletteDisplayController);

  // -------- -------- --------

  connect(m_ui->btnPixelate, &QPushButton::clicked, this, &MainWindow::onProcess);

  onPlatformChanged();
}

MainWindow::~MainWindow() {
  delete m_ui;
}

void MainWindow::onOpen() {
  QString path = QFileDialog::getOpenFileName(
      this,
      "Save image as",
      "",
      "All Picture Files (*.png *.jpg *.jpeg *.jpe *.jfif);;JPEG "
      "(*.jpg *.jpeg *.jpe *.jfif);; PNG(*.png);"
  );

  m_image.open(path);

  onDownScaleControlChanged();
  m_ui->graphicsView->fitToView();
}

void MainWindow::onSaveAs() {
  QString path = QFileDialog::getSaveFileName(
      this,
      "Save image as",
      "",
      "All Picture Files (*.png *.jpg *.jpeg *.jpe *.jfif);;JPEG "
      "(*.jpg *.jpeg *.jpe *.jfif);; PNG(*.png)"
  );

  m_image.save(path);
}

void MainWindow::onFitToView() {
  m_ui->graphicsView->fitToView();
}

void MainWindow::onZoomIn() {
  m_ui->graphicsView->zoomIn();
}

void MainWindow::onZoomOut() {
  m_ui->graphicsView->zoomOut();
}

void MainWindow::onPlatformChanged() {
  const Platform& platform = Settings::currentPlatform();

  m_downScaleControl->setWidthRange(8, platform.screenSize().width());
  m_downScaleControl->setHeightRange(8, platform.screenSize().height());
  m_downScaleControl->clear();

  auto addItems = [this](const auto& container) {
    for (const DownScaleData& i : container) {
      m_downScaleControl->addItem(i.text, QVariant::fromValue(i));
    }
  };

  addItems(Settings::k_downScaleDefData);
  addItems(platform.downScaleData());
}

void MainWindow::onDownScaleControlChanged() {
  if (!m_image) {
    return;
  }

  updateDonwScale();
  preprocess();
}

void MainWindow::onProcess() {
  if (!m_image) {
    return;
  }

  m_image.setProcessed(processImage(
      m_image.preprocess(),
      m_algorithmFactory.generator(PaletteGenerator::MedianCut),
      m_quantizationControl->currentPaletteIndex(),
      m_algorithmFactory.dithering(m_quantizationControl->currentDitheringId()),
      m_paletteDisplayController->currentPalettePosition()
  ));

  m_ui->graphicsView->setImage(m_image.processed());
}

void MainWindow::preprocess() {
  DownScaleData data = m_downScaleControl->currentData().value<DownScaleData>();
  m_image.setPreprocess(preprocessImage(
      m_image.original(),
      m_downScaleControl->scaleSize(),
      m_downScaleControl->currentRoundMode(),
      data.mode,
      m_downScaleControl->currentResizeMode(),
      m_downScaleControl->resizeCropValue()
  ));

  m_ui->graphicsView->setImage(m_image.preprocess());
}

void MainWindow::updateDonwScale() {
  DownScaleData data = m_downScaleControl->currentData().value<DownScaleData>();

  DownScaleConfig config = buildDownScaleConfig(
      data,
      m_image.originalSize(),
      Settings::currentPlatform().screenSize(),
      m_downScaleControl->scaleSize()
  );

  CropGeometry geometry =
      computeCropGeometry(m_image.originalSize(), m_downScaleControl->scaleSize());

  m_downScaleControl->setResizeMaximum(geometry.maxPosition);
  m_downScaleControl->setResizeCropMode(geometry.mode);

  m_downScaleControl->setScaleRange(config.range);
  m_downScaleControl->setWidthEnabled(config.widthEnabled);
  m_downScaleControl->setHeightEnabled(config.heightEnabled);
  m_downScaleControl->setScaleSize(config.targetSize);
  m_downScaleControl->setResizeControlDisabled(config.resizeModeDisabled);
}
