#include "aptManager.h"

#include <QDebug>

QString AptPackageManager::GetManagerName() const { return "apt"; };

bool AptPackageManager::IsManagerInstalled() const {
    return m_commandExecutor->IsExecutable("apt");
};

QStringList AptPackageManager::GetInstalledPackages() {
    QString packages{};
    try {
        packages = m_commandExecutor->Exec("dpkg-query", QStringList{"-W", "-f=${Package}\\n"});
    } catch (const QString& ex) {
        qCritical() << "Failed to get installed packages with dpkg-query:" << ex;
        return QStringList{};
    }
    return packages.split('\n', Qt::SkipEmptyParts);
};

bool AptPackageManager::RemovePackages(const QStringList& packages) {
    if (packages.isEmpty()) {
        return true;
    }

    QStringList args;
    args << "purge" << "-y" << packages;

    try {
        m_commandExecutor->SudoExec("apt", args);
        return true;
    } catch (const QString& ex) {
        qCritical() << "Failed to remove packages with apt:" << ex;
        return false;
    }
}

bool AptPackageManager::InstallPackages(const QStringList& packages) {
    if (packages.isEmpty()) {
        return true;
    }

    QStringList args;
    args << "install" << "-y" << packages;

    try {
        m_commandExecutor->SudoExec("apt", args);
        return true;
    } catch (const QString& ex) {
        qCritical() << "Failed to install packages with apt:" << ex;
        return false;
    }
}
