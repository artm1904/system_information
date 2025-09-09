#include "pacmanManager.h"

#include <QDebug>

QString PacmanPackageManager::GetManagerName() const { return "pacman"; };

bool PacmanPackageManager::IsManagerInstalled() const {
    return m_commandExecutor->IsExecutable("pacman");
};

QStringList PacmanPackageManager::GetInstalledPackages() {
    QString packages{};
    try {
        packages = m_commandExecutor->Exec("pacman", QStringList{"-Qe"});
    } catch (const QString& ex) {
        qCritical() << "Failed to get installed packages with pacman:" << ex;
        return QStringList{};
    }
    return packages.split("\n");
};

bool PacmanPackageManager::RemovePackages(const QStringList& packages) {
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

bool PacmanPackageManager::InstallPackages(const QStringList& packages) {
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