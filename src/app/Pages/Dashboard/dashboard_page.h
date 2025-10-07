#pragma once

#include <Managers/info_manager.h>

#include <QTimer>
#include <QWidget>
#include <memory>

#include "circlebar.h"
#include "linebar.h"

namespace Ui {
class DashboardPage;
}  // namespace Ui

class DashboardPage : public QWidget {
    Q_OBJECT

   public:
    explicit DashboardPage(QWidget *parent = 0);
    ~DashboardPage() override;

   private slots:
    void Init();
    void SystemInformationInit();

    void UpdateCpuBar();
    void UpdateMemoryBar();
    void UpdateDiskBar();
    void UpdateNetworkBar();

   private:
    std::unique_ptr<Ui::DashboardPage> ui;

   private:
    std::unique_ptr<CircleBar> m_cpuBar;
    std::unique_ptr<CircleBar> m_memBar;
    std::unique_ptr<CircleBar> m_diskBar;
    std::unique_ptr<LineBar> m_downloadBar;
    std::unique_ptr<LineBar> m_uploadBar;
    std::unique_ptr<QTimer> m_timer;
    std::shared_ptr<InfoManager> m_im;
};