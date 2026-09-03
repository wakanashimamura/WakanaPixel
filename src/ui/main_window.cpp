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

#include "main_window.h"

#include "application/processing_controller.h"
#include "image_view.h"
#include "resize_control.h"
#include "ui_main_window.h"

#include <QFileDialog>
#include <QStandardPaths>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      m_ui(new Ui::MainWindow) {
  m_ui->setupUi(this);

  m_ui->buttonSaveImage->setEnabled(false);
  m_ui->resizeControl->setEnabled(false);

  connect(m_ui->buttonOpenImage, &QPushButton::clicked, this, &MainWindow::selectImageToOpen);
  connect(m_ui->buttonSaveImage, &QPushButton::clicked, this, &MainWindow::selectImageSavePath);
}

MainWindow::~MainWindow() {
  delete m_ui;
}

void MainWindow::setController(ProcessingController* controller) {
  m_controller = controller;

  connect(m_controller, &ProcessingController::imageLoaded, this, [this](bool isLoaded) {
    m_controller->imageProcessing(m_ui->resizeControl->value());
    m_ui->buttonSaveImage->setEnabled(isLoaded);
    m_ui->resizeControl->setEnabled(isLoaded);
  });

  connect(
      m_controller,
      &ProcessingController::imageReadyDisplay,
      m_ui->imageView,
      &ImageView::setImage
  );

  connect(
      m_controller,
      &ProcessingController::updateResizeControlValue,
      m_ui->resizeControl,
      [this](QSize size) { m_ui->resizeControl->setSize(size); }
  );

  connect(
      m_controller,
      &ProcessingController::updateResizeControlStatus,
      m_ui->resizeControl,
      &ResizeControl::setStatus
  );
  connect(
      m_controller,
      &ProcessingController::updateResizeParamsLimit,
      m_ui->resizeControl,
      &ResizeControl::setLimit
  );

  connect(
      m_ui->resizeControl,
      &ResizeControl::valueChanged,
      m_controller,
      &ProcessingController::imageProcessing
  );
}

void MainWindow::selectImageToOpen() {
  if (!m_controller) {
    return;
  }

  QString filePath = QFileDialog::getOpenFileName(
      this,
      "Open image",
      QStandardPaths::writableLocation(QStandardPaths::PicturesLocation),
      "Images (*.png *.jpg *.jpeg *.jpe *.jfif);;"
      "JPEG (*.jpg *.jpeg *.jpe *.jfif);;"
      "PNG (*.png)"
  );

  m_controller->openImage(filePath);
}

void MainWindow::selectImageSavePath() {
  if (!m_controller) {
    return;
  }

  QString filePath = QFileDialog::getSaveFileName(
      this,
      "Save image",
      QStandardPaths::writableLocation(QStandardPaths::PicturesLocation),
      "Images (*.png *.jpg *.jpeg *.jpe *.jfif);;"
      "JPEG (*.jpg *.jpeg *.jpe *.jfif);;"
      "PNG (*.png)"
  );

  m_controller->saveImage(filePath);
}
