#include "service_tool.h"

#include <QDebug>
#include <QProcess>
#include <QRegularExpression>
#include <iostream>

QList<Service> ServiceTool::GetServicesWithSystemctl() {
    QList<Service> services{};

    try {
        QStringList args{"list-unit-files",          "--type=service", "--all",
                         "--state=enabled,disabled", "--no-legend",    "--no-pager"};

        const QString output = m_commandExecutor->Exec("systemctl", args);
        const QStringList lines = output.split('\n', Qt::SkipEmptyParts);

        for (const QString& serviceFromList : lines) {
            // Пропускаем шаблонные сервисы, такие как getty@.service
            if (serviceFromList.contains('@')) {
                continue;
            }
            QStringList parts = serviceFromList.trimmed().split(QRegularExpression(R"(\s+)"));
            if (parts.size() < 2) {
                continue;
            }
            QString name = parts[0];
            bool status = parts[1] == "enabled";

            bool active = ServiceIsActive(name);

            Service service{name, status, active};
            services << service;
        }

    } catch (const QString& ex) {
        qCritical() << ex;
    }

    // for testing
    //  for (Service& service : services) {
    //      std::cout << service << std::endl;
    //  }

    return services;
}

bool ServiceTool::ServiceIsActive(const QString& serviceName) {
    QStringList args{"is-active", serviceName};
    QString result{""};
    try {
        result = m_commandExecutor->Exec("systemctl", args);
    } catch (const QString& ex) {
        qCritical() << ex;
    }

    return result.trimmed() == "active";

    // Иная реализация, без вызова CommandUtil::Exec
    // QProcess process;
    // process.start("systemctl", args);

    // if (!process.waitForFinished(5000)) {
    //     qWarning() << "Timeout while checking status for service:" << serviceName;
    //     process.kill();
    //     process.close();
    //     return false;
    // }

    // if (process.exitStatus() == QProcess::NormalExit &&
    //     (process.exitCode() == 0 || process.exitCode() == 3)) {
    //     const QString result = QString::fromUtf8(process.readAllStandardOutput()).trimmed();
    //     return result == "active";
    // }

    // qWarning() << "Failed to get status for service" << serviceName
    //            << "Exit code:" << process.exitCode();
    // return false;
}

bool ServiceTool::ServiceIsEnable(const QString& serviceName) {
    QStringList args{"is-enabled", serviceName};
    QString result{""};
    try {
        result = m_commandExecutor->Exec("systemctl", args);
    } catch (const QString& ex) {
        qCritical() << ex;
    }
    return result.trimmed() == "enabled";
}

bool ServiceTool::ChangeServiceStatus(const QString& serviceName, bool status) {
    QStringList args{(status ? "enable" : "disable"), serviceName};
    try {
        m_commandExecutor->SudoExec("systemctl", args);
        return true;
    } catch (const QString& ex) {
        qCritical() << ex;
        return false;
    }
}

bool ServiceTool::ChangeServiceActive(const QString& serviceName, bool active) {
    QStringList args{(active ? "start" : "stop"), serviceName};
    try {
        m_commandExecutor->SudoExec("systemctl", args);
        return true;
    } catch (const QString& ex) {
        qCritical() << ex;
        return false;
    }
}
