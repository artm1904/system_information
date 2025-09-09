#pragma once

#include "../Utils/file_util.h"
#include "../core_global.h"

#define PROC_MEMINFO "/proc/meminfo"

class CORE_EXPORT MemoryInfo {
   public:
    MemoryInfo();

    void UpdateMemoryInfo();

    quint64 GetMemTotal() const;
    quint64 GetMemAvailable() const;
    quint64 GetMemUsed() const;

    quint64 GetSwapTotal() const;
    quint64 GetSwapFree() const;
    quint64 GetSwapUsed() const;

   private:
    // memory
    quint64 m_memTotal;
    quint64 m_memAvailable;
    quint64 m_memUsed;

    // swap
    quint64 m_swapTotal;
    quint64 m_swapFree;
    quint64 m_swapUsed;
};