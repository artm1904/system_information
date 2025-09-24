#include "dashboard_page.h"
#include "ui_dashboard_page.h"


#include <QDesktopServices>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QtConcurrent>

DashboardPage::~DashboardPage() = default;

DashboardPage::DashboardPage(QWidget *parent)
    : QWidget(parent),
      ui(std::make_unique<Ui::DashboardPage>()),
      m_cpuBar(std::make_unique<CircleBar>(tr("CPU"), QStringList{"#A8E063", "#56AB2F"})),
      m_memBar(std::make_unique<CircleBar>(tr("MEMORY"), QStringList{"#FFB75E", "#ED8F03"})),
      m_diskBar(std::make_unique<CircleBar>(tr("DISK"), QStringList{"#DC2430", "#7B4397"})),
      m_downloadBar(std::make_unique<LineBar>(tr("DOWNLOAD"))),
      m_uploadBar(std::make_unique<LineBar>(tr("UPLOAD"))),
      m_timer(std::make_unique<QTimer>()),
      m_im(InfoManager::Instance()) {
    ui->setupUi(this);
    Init();
}


void DashboardPage::Init()
{
    
}

void DashboardPage::CheckUpdate()
{
   
}

void DashboardPage::on_downloadUpdateBtn_clicked()
{
    QDesktopServices::openUrl(QUrl("https://github.com/oguzhaninan/Stacer/releases/latest"));
}

void DashboardPage::SystemInformationInit()
{
   
}

void DashboardPage::UpdateCpuBar()
{
    
}

void DashboardPage::UpdateMemoryBar()
{
   
}

void DashboardPage::UpdateDiskBar()
{
   
}

void DashboardPage::UpdateNetworkBar()
{
    
}