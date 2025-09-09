#include "network_info.h"

#include <QRegularExpression>


NetworkInfo::NetworkInfo() {
    QStringList lines = FileUtil::ReadListFromFile(PROC_NET_ROUTE);
    if (lines.isEmpty() == false) {
        m_defaultNetworkInterface = lines.at(2).split(QRegularExpression("\\s+")).first();
    } else {
        m_defaultNetworkInterface = "wlan0";
    }

    m_rxPath = QString("/sys/class/net/%1/statistics/rx_bytes").arg(m_defaultNetworkInterface);

    m_txPath = QString("/sys/class/net/%1/statistics/tx_bytes").arg(m_defaultNetworkInterface);
}

QString NetworkInfo::GetDefaultNetworkInterface() const { return m_defaultNetworkInterface; }

quint64 NetworkInfo::GetRXbytes() {
    quint64 rx = FileUtil::ReadStringFromFile(m_rxPath).toULongLong();
    return rx;
}

quint64 NetworkInfo::GetTXbytes() {
    quint64 tx = FileUtil::ReadStringFromFile(m_txPath).toULongLong();
    return tx;
}