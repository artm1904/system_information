#pragma once

#include <QDebug>
#include <QVector>

#include "../Utils/file_util.h"
#include "../core_global.h"

#define PROC_CPUINFO "/proc/cpuinfo"
#define PROC_STAT "/proc/stat"

class CORE_EXPORT CpuInfo {
   public:
    CpuInfo();

    quint8 GetCpuCoreCount();
    QList<int> GetCpuPercents();

   private:
    int GetOneCpuPercent(QList<double> cpuTimes, int processor = 0);
};