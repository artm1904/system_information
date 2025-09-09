#pragma once

#include "../Utils/file_util.h"
#include "../core_global.h"

#define PROC_NET_ROUTE "/proc/net/route"

class CORE_EXPORT NetworkInfo {
   public:
    NetworkInfo();

    QString GetDefaultNetworkInterface() const;

    quint64 GetRXbytes();
    quint64 GetTXbytes();

   private:
    QString m_defaultNetworkInterface;

    QString m_rxPath;
    QString m_txPath;
};