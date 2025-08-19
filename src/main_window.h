#pragma once

#include <QMainWindow>

namespace Ui {
class MainWindow;
}  // namespace Ui

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  
public slots:
  void on_myButton_clicked();

 private:
  Ui::MainWindow *ui;
};
