#pragma once

#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QMainWindow>
#include <QStandardPaths>
#include <QTextStream>
#include <memory>

#include "Pages/Dashboard/dashboard_page.h"

// Предварительное объявление класса, который будет сгенерирован из app.ui
namespace Ui {
class App;
}

class MainWindowImpl : public QMainWindow {
    Q_OBJECT

   public:
    explicit MainWindowImpl(QWidget *parent = nullptr);
    ~MainWindowImpl() override;

   private slots:
    void init();
    void pageClick(QPushButton *btn, QWidget *w, QString title);

    void on_dashBtn_clicked();

   private:
     std::unique_ptr<Ui::App> ui;

   private:
    // Pages
    DashboardPage *dashboardPage;
};