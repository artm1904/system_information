#include "cpu_info.h"

#include <QDebug>
#include <QRegularExpression>


CpuInfo::CpuInfo() {}

quint8 CpuInfo::GetCpuCoreCount() {
    quint8 coreCount = 0;

    QStringList allLines = FileUtil::ReadListFromFile(PROC_CPUINFO);

    if (allLines.isEmpty() == false) {
        coreCount = allLines.filter(QRegularExpression("^processor\\b")).count();
    }

    return coreCount;
}

QList<int> CpuInfo::GetCpuPercents() {
    QList<double> cpuTimes;

    QList<int> cpuPercents;

    QStringList allLine = FileUtil::ReadListFromFile(PROC_STAT);

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

        for (int i = 0; i < CpuInfo::GetCpuCoreCount() + 1; ++i) {
            QStringList n_times =
                allLine.at(i).split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
            n_times.removeFirst();

            for (const QString &t : n_times) {
                cpuTimes << t.toDouble();
            }

            cpuPercents << GetOneCpuPercent(cpuTimes, i);
            cpuTimes.clear();
        }
    }
    return cpuPercents;
}

int CpuInfo::GetOneCpuPercent(QList<double> cpuTimes, int processor) {
    int n = GetCpuCoreCount() + 1;

    static QVector<double> l_idles(n);
    static QVector<double> l_totals(n);

    double idle;
    double total;
    double idle_delta;
    double total_delta;

    int utilisation = 0;

    if (cpuTimes.isEmpty() == false) {
        idle = cpuTimes.at(3) + cpuTimes.at(4);  // get (idle + iowait)

        for (double t : cpuTimes) {
            total += t;
        }

        idle_delta = idle - l_idles.at(processor);
        total_delta = total - l_totals.at(processor);
        l_idles.replace(processor, idle);
        l_totals.replace(processor, total);

        utilisation = 100 * ((total_delta - idle_delta) / total_delta);
    }

    if (utilisation < 0) {
        utilisation = 0;
    } else if (utilisation > 100) {
        utilisation = 100;
    }

    return utilisation;
}
