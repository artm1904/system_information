#include "package_tool.h"

#include <QDebug>

#include "packageStrategies/aptManager.h"
#include "packageStrategies/aurManager.h"
#include "packageStrategies/pacmanManager.h"
PackageTool::PackageTool(CommandExecutorPtr commandExecutor, QObject* parent)
    : QObject(parent), m_commandExecutor(commandExecutor) {
    QList<PackageManagerPtr> knownManagers;
    knownManagers << std::make_shared<PacmanPackageManager>(m_commandExecutor);

    for (const auto& manager : knownManagers) {
        if (manager->IsManagerInstalled()) {
            m_packageManagers.append(manager);
        }
    }
}

QStringList PackageTool::AvailablePackageManagers() const {
    QStringList managerNames;
    for (const auto& manager : m_packageManagers) {
        managerNames.append(manager->GetManagerName());
    }
    return managerNames;
}

QStringList PackageTool::GetInstalledPackages(const QString& managerName) {
    for (const auto& manager : m_packageManagers) {
        if (manager->GetManagerName() == managerName) {
            return manager->GetInstalledPackages();
        }
    }
    qWarning() << "Package manager " << managerName << " not found";
    return QStringList{};
}

bool PackageTool::RemovePackages(const QString& managerName, const QStringList& packages) {
    for (const auto& manager : m_packageManagers) {
        if (manager->GetManagerName() == managerName) {
            manager->RemovePackages(packages);
            return true;
        }
    }
    qWarning() << "Package manager " << managerName << "or packages " << packages << "not found";
    return false;
}

bool PackageTool::InstallPackages(const QString& managerName, const QStringList& packages) {
    for (const auto& manager : m_packageManagers) {
        if (manager->GetManagerName() == managerName) {
            manager->InstallPackages(packages);
            return true;
        }
    }
    qWarning() << "Package manager " << managerName << "or packages " << packages << "not found";
    return false;
}

