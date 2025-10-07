#pragma once

#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QMainWindow>
#include <QStandardPaths>
#include <QTextStream>
#include <memory>

#include "Managers/app_manager.h"
#include "Pages/Dashboard/dashboard_page.h"

namespace Ui {
class App;
}  // namespace Ui

class MainWindowImpl : public QMainWindow {
    Q_OBJECT

   public:
    explicit MainWindowImpl(QWidget *parent = nullptr);
    ~MainWindowImpl() override;

   private slots:
    void Init();
    void PageClick(QPushButton *btn, QWidget *w, QString title);

    void on_dashBtn_clicked();

   private:
    std::unique_ptr<Ui::App> ui;

   private:
    std::shared_ptr<AppManager> m_appManager;

    // Pages
    std::unique_ptr<DashboardPage> m_dashboardPage;
};