#include "info_manager.h"

#include "Utils/qt_file_reader.h"

InfoManager::InfoManager() {
    CommandExecutorPtr commandExecutor = std::make_shared<CommandUtil>();
    FileReaderPtr fileReader = std::make_shared<QtFileReader>();  // Dependecy injection for testing

    m_ci = std::make_shared<CpuInfo>(fileReader);
    m_di = std::make_unique<DiskInfo>(commandExecutor);
    m_mi = std::make_unique<MemoryInfo>();
    m_ni = std::make_unique<NetworkInfo>();
    m_si = std::make_unique<SystemInfo>(m_ci, fileReader);
    m_pi = std::make_unique<ProcessInfo>(commandExecutor);
}

//'Meyers' Singleton, using static value for multithreding safe (C++11)
std::shared_ptr<InfoManager> InfoManager::Instance() {
    static std::shared_ptr<InfoManager> instance(new InfoManager());
    return instance;
}

/** CPU information */
quint8 InfoManager::GetCpuCoreCount() { return m_ci->GetCpuCoreCount(); }

QList<int> InfoManager::GetCpuPercents() { return m_ci->GetCpuPercents(); }

/** Memory information */
quint64 InfoManager::GetSwapUsed() { return m_mi->GetSwapUsed(); }
quint64 InfoManager::GetSwapTotal() { return m_mi->GetSwapTotal(); }
quint64 InfoManager::GetMemUsed() { return m_mi->GetMemUsed(); }
quint64 InfoManager::GetMemTotal() { return m_mi->GetMemTotal(); }
void InfoManager::UpdateMemoryInfo() { m_mi->UpdateMemoryInfo(); }

/** Disk information */
QList<Disk> InfoManager::GetDisks() { return m_di->GetDisks(); }
void InfoManager::UpdateDiskInfo() { m_di->UpdateDiskInfo(); }

/** Network information */
quint64 InfoManager::GetRXbytes() { return m_ni->GetRXbytes(); }
quint64 InfoManager::GetTXbytes() { return m_ni->GetTXbytes(); }

/** System  log information */
QFileInfoList InfoManager::GetCrashReports() { return m_si->GetCrashReports(); }
QFileInfoList InfoManager::GetAppLogs() { return m_si->GetAppLogs(); }
QFileInfoList InfoManager::GetAppCaches() { return m_si->GetAppCaches(); }

//** System describe inforamtion */
QString InfoManager::GetHostname() { return m_si->GetHostname(); }
QString InfoManager::GetPlatform() { return m_si->GetPlatform(); }
QString InfoManager::GetDistribution() { return m_si->GetDistribution(); }
QString InfoManager::GetKernel() { return m_si->GetKernel(); }
QString InfoManager::GetCpuModel() { return m_si->GetCpuModel(); }
QString InfoManager::GetCpuSpeed() { return m_si->GetCpuSpeed(); }
QString InfoManager::GetCpuCore() { return m_si->GetCpuCore(); }

/** Process information */
void InfoManager::UpdateProcesses() { m_pi->UpdateProcessList(); }
QList<Process> InfoManager::GetProcesses() { return m_pi->GetProcessList(); }
QString InfoManager::GetUserName() { return m_si->GetUsername(); }
