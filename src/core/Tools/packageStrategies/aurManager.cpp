#include "aurManager.h"
#include <QDebug>

QString AurPackageManager::GetManagerName() const { return "aur"; };

bool AurPackageManager::IsManagerInstalled() const {
    if (m_commandExecutor->IsExecutable("yay")) {
        m_aurName = "yay";
    } else if (m_commandExecutor->IsExecutable("paru")) {
        m_aurName = "paru";
    } else {
        return false;
    }

    return true;
};

QStringList AurPackageManager::GetInstalledPackages() {
    QString packages{};
    try {
        packages = m_commandExecutor->Exec(m_aurName, QStringList{"-Qe"});
    } catch (const QString& ex) {
        qCritical() << ex;
        return QStringList{};
    }
    return packages.split("\n");
};
bool AurPackageManager::RemovePackages(const QStringList& packages) {
    if (packages.isEmpty()) {
        return true;
    }

    QStringList args;
    args << "-Rns" << "--noconfirm" << packages;

    try {
        m_commandExecutor->SudoExec(m_aurName, args);
        return true;
    } catch (const QString& ex) {
        qCritical() << "Failed to remove packages with aur:" << ex;
        return false;
    }
}

bool AurPackageManager::InstallPackages(const QStringList& packages) {
    if (packages.isEmpty()) {
        return true;
    }

    QStringList args;
    args << "-S" << "--noconfirm" << packages;

    try {
        m_commandExecutor->SudoExec(m_aurName, args);
        return true;
    } catch (const QString& ex) {
        qCritical() << "Failed to install packages with aur:" << ex;
        return false;
    }
}