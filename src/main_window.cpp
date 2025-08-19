#include "main_window.h"
#include "ui_main_window.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
 //connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::on_pushButton_clicked);
 setWindowIcon(QIcon(":/app_icon.png"));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_myButton_clicked() {
  //ui->label_2->setText("Hello World");
  QMessageBox::about(this, "My Title", "Hello World");
}

