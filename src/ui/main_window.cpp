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
#include "ui_main_window.h"

#include <QFileDialog>
#include <QStandardPaths>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      m_ui(new Ui::MainWindow) {
  m_ui->setupUi(this);

  connect(m_ui->buttonOpenImage, &QPushButton::clicked, this, &MainWindow::selectImageToOpen);
  connect(m_ui->buttonSaveImage, &QPushButton::clicked, this, &MainWindow::selectImageSavePath);
}

MainWindow::~MainWindow() {
  delete m_ui;
}

void MainWindow::setController(ProcessingController* controller) {
  m_controller = controller;

  connect(m_controller, &ProcessingController::imageLoaded, m_ui->imageView, &ImageView::setImage);
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
