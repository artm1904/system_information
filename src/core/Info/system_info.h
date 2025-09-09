#pragma once

#include <QFileInfoList>
#include <QSysInfo>
#include <memory>

#include "../core_global.h"
#include "cpu_info.h"

#define PROC_CPUINFO "/proc/cpuinfo"

class CORE_EXPORT SystemInfo {
   public:
    SystemInfo();

    QString GetUsername() const;
    QString GetHostname() const;
    QString GetPlatform() const;
    QString GetDistribution() const;
    QString GetKernel() const;
    QString GetCpuModel() const;
    QString GetCpuSpeed() const;
    QString GetCpuCore() const;

    QFileInfoList GetCrashReports() const;
    QFileInfoList GetAppLogs() const;
    QFileInfoList GetAppCaches() const;

   private:
    QString m_cpuCore;
    QString m_cpuModel;
    QString m_cpuSpeed;

    std::unique_ptr<QSysInfo> m_info;
    QString m_username;
};