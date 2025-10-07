#include "dashboard_page.h"

#include <QDesktopServices>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QtConcurrent>

#include "ui_dashboard_page.h"

DashboardPage::~DashboardPage() = default;

DashboardPage::DashboardPage(QWidget* parent)
    : QWidget(parent),
      ui(std::make_unique<Ui::DashboardPage>()),
      m_cpuBar(std::make_unique<CircleBar>(tr("CPU"), QStringList{"#A8E063", "#56AB2F"})),
      m_memBar(std::make_unique<CircleBar>(tr("MEMORY"), QStringList{"#FFB75E", "#ED8F03"})),
      //  m_diskBar(std::make_unique<CircleBar>(tr("DISK"), QStringList{"#DC2430", "#7B4397"})),
      m_downloadBar(std::make_unique<LineBar>(tr("DOWNLOAD"))),
      m_uploadBar(std::make_unique<LineBar>(tr("UPLOAD"))),
      m_timer(std::make_unique<QTimer>()),
      m_im(InfoManager::Instance()) {
    ui->setupUi(this);
    Init();
    SystemInformationInit();
}

void DashboardPage::Init() {
    // Circle bars
    ui->circleBarsLayout->addWidget(m_cpuBar.get());
    ui->circleBarsLayout->addWidget(m_memBar.get());
    // ui->circleBarsLayout->addWidget(m_diskBar.get());

    // line bars
    ui->lineBarsLayout->addWidget(m_downloadBar.get());
    ui->lineBarsLayout->addWidget(m_uploadBar.get());

    // connections
    connect(m_timer.get(), &QTimer::timeout, this, &DashboardPage::UpdateCpuBar);
    connect(m_timer.get(), &QTimer::timeout, this, &DashboardPage::UpdateMemoryBar);
    connect(m_timer.get(), &QTimer::timeout, this, &DashboardPage::UpdateNetworkBar);
    connect(m_timer.get(), &QTimer::timeout, this, &DashboardPage::UpdateDiskBar);

    m_timer->start(1 * 1000);

    // initialization
    UpdateCpuBar();
    UpdateMemoryBar();
    UpdateDiskBar();
    UpdateNetworkBar();
}

void DashboardPage::SystemInformationInit() {
    // get system information

    QStringList infos;
    infos << tr("Hostname: %1").arg(m_im->GetHostname())
          << tr("Platform: %1").arg(m_im->GetPlatform())
          << tr("Distribution: %1").arg(m_im->GetDistribution())
          << tr("Kernel Release: %1").arg(m_im->GetKernel())
          << tr("CPU Model: %1").arg(m_im->GetCpuModel())
          << tr("CPU Speed: %1").arg(m_im->GetCpuSpeed())
          << tr("CPU Core: %1").arg(m_im->GetCpuCore());

    auto* systemInfoModel = new QStringListModel(infos, this);
    ui->systemInfoList->setModel(systemInfoModel);
}

void DashboardPage::UpdateCpuBar() {
    int cpuUsedPercent = m_im->GetCpuPercents().at(0);
    m_cpuBar->SetValue(cpuUsedPercent, QString("%1%").arg(cpuUsedPercent));
}

void DashboardPage::UpdateMemoryBar() {
    m_im->UpdateMemoryInfo();

    int memUsedPercent = 0;
    if (m_im->GetMemTotal())
        memUsedPercent = ((double)m_im->GetMemUsed() / (double)m_im->GetMemTotal()) * 100.0;

    QString f_memUsed = FormatUtil::FormatBytes(m_im->GetMemUsed() * 1024);
    QString f_memTotal = FormatUtil::FormatBytes(m_im->GetMemTotal() * 1024);

    m_memBar->SetValue(memUsedPercent, QString("%1 / %2").arg(f_memUsed).arg(f_memTotal));
}

void DashboardPage::UpdateDiskBar() {
    m_im->UpdateDiskInfo();
    QVector<Disk> disks = m_im->GetDisks();

    // if number of disks changed
    if (m_diskBars.size() != disks.size()) {
        for (auto& bar : m_diskBars) {
            bar->hide();
            bar->deleteLater();
        }

        m_diskBars.clear();

        // create new widgets for each disk
        for (const auto& disk : disks) {
            QString title = disk.name.split("/").last();
            auto bar = std::make_unique<CircleBar>(title, QStringList{"#DC2430", "#7B4397"});
            ui->circleBarsLayout->addWidget(bar.get());
            m_diskBars.append(std::move(bar));
        }
    }

    // update each dick info

    for (int i = 0; i < m_diskBars.size(); i++) {
        const Disk& disk = disks.at(i);
        quint64 size = disk.size;
        quint64 used = disk.used;
        quint64 free = disk.free;

        QString f_size = FormatUtil::FormatBytes(size);
        QString f_used = FormatUtil::FormatBytes(used);
        QString f_free = FormatUtil::FormatBytes(free);

        int diskUsedPercent = 0;
        if (size) diskUsedPercent = ((double)used / (double)size) * 100.0;

        m_diskBars.at(i)->SetValue(diskUsedPercent, QString("%1 / %2").arg(f_used).arg(f_size));
    }
}

void DashboardPage::UpdateNetworkBar() {}