#include "cpu_info.h"

#include <QDebug>
#include <QRegularExpression>

CpuInfo::CpuInfo(FileReaderPtr fileReader) : m_fileReader(fileReader) {
    // Initialize vectors with a size of 1 to avoid issues if GetCpuCoreCount is 0 initially.
    // They will be resized on the first call to GetCpuPercents.
    m_lastIdles.resize(1);
    m_lastTotals.resize(1);
}

quint8 CpuInfo::GetCpuCoreCount() {
    quint8 coreCount = 0;

    QStringList allLines = m_fileReader->ReadListFromFile(PROC_CPUINFO);

    if (allLines.isEmpty() == false) {
        coreCount = allLines.filter(QRegularExpression("^processor\\b")).count();
    }

    return coreCount;
}

QList<int> CpuInfo::GetCpuPercents() {
    QList<double> cpuTimes;

    int coreCount = this->GetCpuCoreCount();
    int vectorSize = coreCount + 1;

    QList<int> cpuPercents;

    QStringList allLine = m_fileReader->ReadListFromFile(PROC_STAT);

    if (allLine.isEmpty() == false) {
        /*  user nice system idle iowait  irq  softirq steal guest guest_nice
       cpu  4705 356  584    3699   23    23     0       0     0      0
        .
       cpuN 4705 356  584    3699   23    23     0       0     0      0

         The meanings of the columns are as follows, from left to right:
            - user: normal processes executing in user mode
            - nice: niced processes executing in user mode
            - system: processes executing in kernel mode
            - idle: twiddling thumbs
            - iowait: waiting for I/O to complete
            - irq: servicing interrupts
            - softirq: servicing softirqs
            - steal: involuntary wait
            - guest: running a normal guest
            - guest_nice: running a niced guest
       */

        // Ensure vectors are initialized and have the correct size
        if (m_lastIdles.size() != vectorSize) {
            m_lastIdles.resize(vectorSize);
            m_lastIdles.fill(0.0);
        }
        if (m_lastTotals.size() != vectorSize) {
            m_lastTotals.resize(vectorSize);
            m_lastTotals.fill(0.0);
        }

        for (int i = 0; i < vectorSize; ++i) {
            QStringList n_times =
                allLine.at(i).split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
            n_times.removeFirst();

            for (const QString& t : n_times) {
                cpuTimes << t.toDouble();
            }

            cpuPercents << GetOneCpuPercent(cpuTimes, i, m_lastIdles, m_lastTotals);
            cpuTimes.clear();
        }
    }
    return cpuPercents;
}

int CpuInfo::GetOneCpuPercent(const QList<double>& cpuTimes, int processor,
                              QVector<double>& l_idles, QVector<double>& l_totals) {
    double idle = 0.0;
    double total = 0.0;
    double idle_delta = 0.0;
    double total_delta = 0.0;

    int utilisation = 0;

    if (cpuTimes.isEmpty() == false) {
        idle = cpuTimes.at(3) + cpuTimes.at(4);  // get (idle + iowait)

        for (double t : cpuTimes) {
            total += t;
        }

        idle_delta = idle - l_idles[processor];
        total_delta = total - l_totals[processor];
        l_idles[processor] = idle;
        l_totals[processor] = total;

        utilisation = 100 * ((total_delta - idle_delta) / total_delta);
    }

    if (utilisation < 0) {
        utilisation = 0;
    } else if (utilisation > 100) {
        utilisation = 100;
    }

    return utilisation;
}
