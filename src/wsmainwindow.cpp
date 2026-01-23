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

#include "wsmainwindow.h"

#include <QFileDialog>

#include "ui_wsmainwindow.h"
#include "wsimageprocessing.h"

WSMainWindow::WSMainWindow(QWidget *parent) : QMainWindow(parent), m_ui(new Ui::WSMainWindow) {
  m_ui->setupUi(this);

  connect(m_ui->actionOpen, &QAction::triggered, this, &WSMainWindow::openImage);
  connect(m_ui->actionSave_as, &QAction::triggered, this, &WSMainWindow::saveAsImage);
}

WSMainWindow::~WSMainWindow() {
  delete m_ui;
}

void WSMainWindow::openImage() {
  QString fileName = QFileDialog::getOpenFileName(
      this, "Select an image", "", "Image (*.png *.jpg *.jpeg *.bmp *.svg);;All files (*.*)");

  if (!m_image.load(fileName)) {
    return;
  }

  // === temporary code ===

  m_image.setEdited(ws::downscale(m_image.edited(), 143, 256));

  m_image.setEdited(ws::upscale(m_image.edited(), 683, 1280));

  // ======================

  m_ui->graphicsView->setImage(m_image.edited());
  m_ui->graphicsView->fitToView();
}

void WSMainWindow::saveAsImage() {
  QString fileName = QFileDialog::getSaveFileName(
      this, "Save image as", "", "Image (*.png *.jpg *.jpeg *.bmp *.svg);;All files (*.*)");

  if (!m_image.save(fileName)) {
    return;
  }
}