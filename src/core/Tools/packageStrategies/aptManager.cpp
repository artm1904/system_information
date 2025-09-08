#include "aptManager.h"
#include <QDebug>

QString AptPackageManager::GetManagerName() const { return "apt"; };

bool AptPackageManager::IsManagerInstalled() const {
    return m_commandExecutor->IsExecutable("apt");
};

QStringList AptPackageManager::GetInstalledPackages() {
    QString packages{};
    try {
        packages = m_commandExecutor->Exec("apt", QStringList{"-Qe"});
    } catch (const QString& ex) {
        qCritical() << ex;
        return QStringList{};
    }
    return packages.split("\n");
};
bool AptPackageManager::RemovePackages(const QStringList& packages) {
    if (packages.isEmpty()) {
        return true;
    }

    QStringList args;
    args << "-Rns" << "--noconfirm" << packages;

    try {
        m_commandExecutor->SudoExec("pacman", args);
        return true;
    } catch (const QString& ex) {
        qCritical() << "Failed to remove packages with pacman:" << ex;
        return false;
    }
}

bool AptPackageManager::InstallPackages(const QStringList& packages) {
    if (packages.isEmpty()) {
        return true;
    }

    QStringList args;
    args << "-S" << "--noconfirm" << packages;

    try {
        m_commandExecutor->SudoExec("pacman", args);
        return true;
    } catch (const QString& ex) {
        qCritical() << "Failed to install packages with pacman:" << ex;
        return false;
    }
}