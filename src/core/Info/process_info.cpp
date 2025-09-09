#include "process_info.h"

#include <QRegularExpression>

ProcessInfo::ProcessInfo(CommandExecutorPtr commandExecutor, QObject* parent)
    : QObject(parent), m_commandExecutor(commandExecutor) {}

void ProcessInfo::UpdateProcessList() {
    m_processList.clear();

    try {
        QStringList columns = {"pid",   "rss",   "pmem", "vsize",   "uname",   "pcpu", "start_time",
                               "state", "group", "nice", "cputime", "session", "seat", "cmd"};

        QStringList lines =
            m_commandExecutor->Exec("ps", {"ax", "-eo", columns.join(","), "--no-headings"})
                .trimmed()
                .split("\n");

        if (lines.isEmpty() == false) {
            for (const QString& line : lines) {
                QStringList fields = line.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
                if (fields.size() >= columns.size()) {
                    Process process;
                    process.SetPid(fields[0].toULongLong());
                    process.SetRss(fields[1].toULongLong());
                    process.SetPmem(fields[2].toDouble());
                    process.SetVsize(fields[3].toULongLong());
                    process.SetUname(fields[4]);
                    process.SetPcpu(fields[5].toDouble());
                    process.SetStartTime(fields[6]);
                    process.SetState(fields[7]);
                    process.SetGroup(fields[8]);
                    process.SetNice(fields[9].toInt());
                    process.SetCpuTime(fields[10]);
                    process.SetSession(fields[11]);
                    process.SetSeat(fields[12]);
                    process.SetCmd(fields[13]);

                    m_processList << process;
                }
            }
        }

    }

    catch (const QString& ex) {
        qCritical() << "Failed to update process list:" << ex;
    }
}

QList<Process> ProcessInfo::GetProcessList() const { return m_processList; }