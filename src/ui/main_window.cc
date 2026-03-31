#include "ui/main_window.h"

#include "ui_main_window.h"

#include <QFileDialog>
#include <QImage>
#include <QString>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      m_ui(new Ui::MainWindow) {
  m_ui->setupUi(this);

  // -------- Menu Bar --------

  // clang-format off
  connect(m_ui->actionOpen,      &QAction::triggered, this, &MainWindow::onOpen);
  connect(m_ui->actionSaveAs,    &QAction::triggered, this, &MainWindow::onSaveAs);
  connect(m_ui->actionFitToView, &QAction::triggered, this, &MainWindow::onFitToView);
  connect(m_ui->actionZoomIn,    &QAction::triggered, this, &MainWindow::onZoomIn);
  connect(m_ui->actionZoomOut,   &QAction::triggered, this, &MainWindow::onZoomOut);
  // clang-format on
}

MainWindow::~MainWindow() {
  delete m_ui;
}

void MainWindow::onOpen() {
  QString path =
      QFileDialog::getOpenFileName(this, "Save image as", "",
                                   "All Picture Files (*.png *.jpg *.jpeg *.jpe *.jfif);;JPEG "
                                   "(*.jpg *.jpeg *.jpe *.jfif);; PNG(*.png);");

  m_image.open(path);
  m_ui->graphicsView->setImage(m_image.processed());
}

void MainWindow::onSaveAs() {
  QString path =
      QFileDialog::getSaveFileName(this, "Save image as", "",
                                   "All Picture Files (*.png *.jpg *.jpeg *.jpe *.jfif);;JPEG "
                                   "(*.jpg *.jpeg *.jpe *.jfif);; PNG(*.png)");

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
