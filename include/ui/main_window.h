#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "model/image.h"

#include <QMainWindow>

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

 private:
  Ui::MainWindow* m_ui;
  Image m_image;
};
#endif  // MAIN_WINDOW_H
