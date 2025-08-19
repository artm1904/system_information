#pragma once

#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QMainWindow>
#include <QStandardPaths>
#include <QTextStream>

// Предварительное объявление класса, который будет сгенерирован из app.ui
namespace Ui {
class App;
}

class MainWindowImpl : public QMainWindow {
    Q_OBJECT

   public:
    explicit MainWindowImpl(QWidget *parent = nullptr);
    ~MainWindowImpl();

   private:
    Ui::App *ui;

   private slots:
    void init();
};