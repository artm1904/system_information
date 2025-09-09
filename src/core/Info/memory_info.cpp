#include "memory_info.h"

#include <QRegularExpression>

MemoryInfo::MemoryInfo() : m_memTotal(0), m_memAvailable(0), m_memUsed(0) {};

void MemoryInfo::UpdateMemoryInfo() {
    QStringList lines =
        FileUtil::ReadListFromFile(PROC_MEMINFO)
            .filter(QRegularExpression("^MemTotal|^MemAvailable|^SwapTotal|^SwapFree"));
    ;
    if (lines.isEmpty() == false) {
        m_memTotal = lines.at(0).split(QRegularExpression("\\s+")).at(1).toULongLong();
        m_memAvailable = lines.at(1).split(QRegularExpression("\\s+")).at(1).toULongLong();
        m_swapTotal = lines.at(2).split(QRegularExpression("\\s+")).at(1).toULongLong();
        m_swapFree = lines.at(3).split(QRegularExpression("\\s+")).at(1).toULongLong();
    }

    m_memUsed = m_memTotal - m_memAvailable;
    m_swapUsed = m_swapTotal - m_swapFree;
}

quint64 MemoryInfo::GetMemTotal() const { return m_memTotal; }

quint64 MemoryInfo::GetMemAvailable() const { return m_memAvailable; }

quint64 MemoryInfo::GetMemUsed() const { return m_memUsed; }

quint64 MemoryInfo::GetSwapTotal() const { return m_swapTotal; }

quint64 MemoryInfo::GetSwapFree() const { return m_swapFree; }

quint64 MemoryInfo::GetSwapUsed() const { return m_swapUsed; }