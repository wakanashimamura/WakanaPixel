// WakanaPixel - Converts photos into pixelated images
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

#include "wsmainwindow.h"
#include "ui_wsmainwindow.h"
#include <QFileDialog>

WSMainWindow::WSMainWindow(QWidget *parent)
  : QMainWindow(parent), m_ui(new Ui::WSMainWindow)
{
  m_ui->setupUi(this);

  connect (m_ui->actionOpen, &QAction::triggered, this, &WSMainWindow::openImage);
}

WSMainWindow::~WSMainWindow()
{
  delete m_ui;
}

void WSMainWindow::openImage () {
  QString fileName = QFileDialog::getOpenFileName (
    this,
    "Select an image",
    "",
    "Image (*.png *.jpg *.jpeg *.bmp *.svg);;All files (*.*)"
  );

  if(fileName.isEmpty()) {
    return; // User cancelled the dialog
  }

  if (!m_currentImage.load (fileName)) {
    return; // Handle error loading image
  }
  
  m_ui->graphicsView->loadImage (m_currentImage);
}