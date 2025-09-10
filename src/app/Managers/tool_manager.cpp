#include "tool_manager.h"

#include <Utils/command_ulit.h>

std::shared_ptr<ToolManager> ToolManager::m_instance = nullptr;

std::shared_ptr<ToolManager> ToolManager::Instance() {
    if (m_instance == nullptr) {
        m_instance.reset(new ToolManager());
    }
    return m_instance;
}

QList<Service> ToolManager::GetServices() { return m_serviceTool->GetServicesWithSystemctl(); }

QStringList ToolManager::GetPackages() {
    QStringList packages;

    QStringList packageManagers = m_packageTool->AvailablePackageManagers();

    for (const QString& manager : packageManagers) {
        packages << m_packageTool->GetInstalledPackages(manager);
    }

    return packages;
}

bool ToolManager::ChangeServiceStatus(QString sname, bool status) {
    return m_serviceTool->ChangeServiceStatus(sname, status);
}

bool ToolManager::ChangeServiceActive(QString sname, bool status) {
    return m_serviceTool->ChangeServiceActive(sname, status);
}

bool ToolManager::ServiceIsActive(QString sname) { return m_serviceTool->ServiceIsActive(sname); }

bool ToolManager::ServiceIsEnabled(QString sname) { return m_serviceTool->ServiceIsEnable(sname); }

void ToolManager::UninstallPackages(QStringList packages) {
    
    UninstallStarted();

    QStringList packageManagers = m_packageTool->AvailablePackageManagers();

    for (const QString& manager : packageManagers) {
        m_packageTool->RemovePackages(manager, packages);
    }

    UninstallFinished();
}

ToolManager::ToolManager(QObject* parent) : QObject(parent) {
    CommandExecutorPtr commandExecutor = std::make_shared<CommandUtil>();
    m_serviceTool = std::make_unique<ServiceTool>(commandExecutor);
    m_packageTool = std::make_unique<PackageTool>(commandExecutor);
}
