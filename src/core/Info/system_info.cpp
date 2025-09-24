#include "system_info.h"

#include <QDir>
#include <QRegularExpression>
#include <QStandardPaths>

#include "Utils/qt_file_reader.h"

SystemInfo::SystemInfo(std::shared_ptr<CpuInfo> cpuInfo, FileReaderPtr fileReader)
    : m_info(std::make_unique<QSysInfo>()) {
    QStringList allLines = fileReader->ReadListFromFile(PROC_CPUINFO);
    QStringList modelLines = allLines.filter(QRegularExpression("^model name\\b"));
    QStringList speedLines = allLines.filter(QRegularExpression("^cpu MHz\\b"));
    QStringList coreLines = allLines.filter(QRegularExpression("^cpu cores\\b"));

    if (modelLines.isEmpty() == false) {
        //"model name	: 12th Gen Intel(R) Core(TM) i5-12500H"
        QString modeLine = modelLines.first().section(":", 1).trimmed();
        m_cpuModel = modeLine;

    } else {
        m_cpuModel = "N/A";
    }

    if (speedLines.isEmpty() == false) {
        //"cpu MHz		: 3666.382"
        QString speedLine = speedLines.first().section(":", 1).trimmed();
        m_cpuSpeed = speedLine;

    } else {
        m_cpuSpeed = "N/A";
    }

    // Get cpu cores number

    // if (coreLines.isEmpty() == false) {
    //     //"cpu cores	: 12"
    //     QString coreLine = coreLines.first().section(":", 1).trimmed();
    //     m_cpuCore = coreLine;

    // } else {
    //     m_cpuCore = "N/A";
    // }

    m_cpuCore = QString::number(cpuInfo->GetCpuCoreCount());

    // Get user name

    QString name = getenv("USER");
    if (name != nullptr) {
        m_username = name;
    } else {
        m_username = "N/A";
    }
}

QString SystemInfo::GetUsername() const { return m_username; }

QString SystemInfo::GetHostname() const { return m_info->machineHostName(); }

QString SystemInfo::GetPlatform() const { return m_info->kernelType(); }

QString SystemInfo::GetDistribution() const { return QSysInfo::prettyProductName(); }

QString SystemInfo::GetKernel() const { return m_info->kernelVersion(); }

QString SystemInfo::GetCpuModel() const { return m_cpuModel; }

QString SystemInfo::GetCpuSpeed() const { return m_cpuSpeed; }

QString SystemInfo::GetCpuCore() const { return m_cpuCore; }

QFileInfoList SystemInfo::GetCrashReports() const {
    QDir reports("/var/crash");

    return reports.entryInfoList(QDir::Files);
}

QFileInfoList SystemInfo::GetAppLogs() const {
    QDir logs("/var/log");

    return logs.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
}

QFileInfoList SystemInfo::GetAppCaches() const {
    QString homePath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);

    QDir caches(homePath + "/.cache");

    return caches.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
}
