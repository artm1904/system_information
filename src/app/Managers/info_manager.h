#pragma once

#include <memory>

#include "Info/cpu_info.h"
#include "Info/disk_info.h"
#include "Info/memory_info.h"
#include "Info/network_info.h"
#include "Info/process_info.h"
#include "Info/system_info.h"
#include "Utils/format_util.h"

class InfoManager {
   public:
    std::shared_ptr<InfoManager> Instance();

    quint8 GetCpuCoreCount();
    QList<int> GetCpuPercents();

    quint64 GetSwapUsed();
    quint64 GetSwapTotal();
    quint64 GetMemUsed();
    quint64 GetMemTotal();
    void UpdateMemoryInfo();

    QList<Disk> GetDisks();
    void UpdateDiskInfo();

    quint64 GetRXbytes();
    quint64 GetTXbytes();

    QFileInfoList GetCrashReports();
    QFileInfoList GetAppLogs();
    QFileInfoList GetAppCaches();

    void UpdateProcesses();
    QList<Process> GetProcesses();
    QString GetUserName();

   private:
    InfoManager();
    static std::shared_ptr<InfoManager> m_instance;

    std::unique_ptr<CpuInfo> m_ci;
    std::unique_ptr<DiskInfo> m_di;
    std::unique_ptr<MemoryInfo> m_mi;
    std::unique_ptr<NetworkInfo> m_ni;
    std::unique_ptr<SystemInfo> m_si;
    std::unique_ptr<ProcessInfo> m_pi;
};