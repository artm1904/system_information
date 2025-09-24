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
    // lazy initialization (only when first use)
    static std::shared_ptr<InfoManager> Instance();

    /** CPU information */
    quint8 GetCpuCoreCount();
    QList<int> GetCpuPercents();

    /** Memory information */
    quint64 GetSwapUsed();
    quint64 GetSwapTotal();
    quint64 GetMemUsed();
    quint64 GetMemTotal();
    void UpdateMemoryInfo();

    /** Disk information */
    QList<Disk> GetDisks();
    void UpdateDiskInfo();

    /** Network information */
    quint64 GetRXbytes();
    quint64 GetTXbytes();

    /** System  log information */
    QFileInfoList GetCrashReports();
    QFileInfoList GetAppLogs();
    QFileInfoList GetAppCaches();

    //** System describe inforamtion */
    QString GetHostname();
    QString GetPlatform();
    QString GetDistribution();
    QString GetKernel();
    QString GetCpuModel();
    QString GetCpuSpeed();
    QString GetCpuCore();

    /** Process information */
    void UpdateProcesses();
    QList<Process> GetProcesses();
    QString GetUserName();

   private:
    InfoManager();

    std::shared_ptr<CpuInfo> m_ci;
    std::unique_ptr<DiskInfo> m_di;
    std::unique_ptr<MemoryInfo> m_mi;
    std::unique_ptr<NetworkInfo> m_ni;
    std::unique_ptr<SystemInfo> m_si;
    std::unique_ptr<ProcessInfo> m_pi;
};