#pragma once

#include <Tools/package_tool.h>
#include <Tools/service_tool.h>

#include <QDebug>
#include <QFileInfoList>
#include <QObject>
#include <memory>

class ToolManager : public QObject {
    Q_OBJECT

   public:
    // lazy initialization (only when first use)
    static std::shared_ptr<ToolManager> Instance();

    QList<Service> GetServices();
    QStringList GetPackages();

   public slots:

    bool ChangeServiceStatus(QString sname, bool status);
    bool ChangeServiceActive(QString sname, bool status);
    bool ServiceIsActive(QString sname);
    bool ServiceIsEnabled(QString sname);
    void UninstallPackages(QStringList packages);

   signals:

    // TODO в tool_manager.cpp эти сигналы используются, они описаны в
    // Pages/Uninstaller/uninstaller_page.cpp
    void UninstallFinished();
    void UninstallStarted();

   private:
    ToolManager(QObject* parent = nullptr);

    std::unique_ptr<ServiceTool> m_serviceTool;
    std::unique_ptr<PackageTool> m_packageTool;
};