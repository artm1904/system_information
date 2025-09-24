#pragma once

#include <QDebug>
#include <QVector>

#include "../Utils/i_file_reader.h" //Dependecy injection for testing
#include "../core_global.h"

#define PROC_CPUINFO "/proc/cpuinfo"
#define PROC_STAT "/proc/stat"

class CORE_EXPORT CpuInfo {
   public:
    explicit CpuInfo(FileReaderPtr fileReader);

    quint8 GetCpuCoreCount();
    QList<int> GetCpuPercents();

   private:
    int GetOneCpuPercent(const QList<double>& cpuTimes, int processor, QVector<double>& lastIdles,
                         QVector<double>& lastTotals);
    FileReaderPtr m_fileReader;

    QVector<double> m_lastIdles;
    QVector<double> m_lastTotals;
};