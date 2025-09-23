#include "info_manager.h"

InfoManager::InfoManager() {
    CommandExecutorPtr commandExecutor = std::make_shared<CommandUtil>();

    m_ci = std::make_unique<CpuInfo>();
    m_di = std::make_unique<DiskInfo>(commandExecutor);
    m_mi = std::make_unique<MemoryInfo>();
    m_ni = std::make_unique<NetworkInfo>();
    m_si = std::make_unique<SystemInfo>();
    m_pi = std::make_unique<ProcessInfo>(commandExecutor);
}

std::shared_ptr<InfoManager> InfoManager::m_instance = nullptr;

std::shared_ptr<InfoManager> InfoManager::Instance() {
    if (m_instance == nullptr) {
        m_instance.reset(new InfoManager());
    }
    return m_instance;
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

/** System information */
QFileInfoList InfoManager::GetCrashReports() { return m_si->GetCrashReports(); }
QFileInfoList InfoManager::GetAppLogs() { return m_si->GetAppLogs(); }
QFileInfoList InfoManager::GetAppCaches() { return m_si->GetAppCaches(); }

/** Process information */
void InfoManager::UpdateProcesses() { m_pi->UpdateProcessList(); }
QList<Process> InfoManager::GetProcesses() { return m_pi->GetProcessList(); }
QString InfoManager::GetUserName() { return m_si->GetUsername(); }
