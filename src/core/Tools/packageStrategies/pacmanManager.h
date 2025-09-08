#pragma once

#include "../i_package_manager.h"

class PacmanPackageManager : public IPackageManager {
   public:
    explicit PacmanPackageManager(CommandExecutorPtr commandExecutor)
        : m_commandExecutor(commandExecutor) {}

    QString GetManagerName() const override;

    bool IsManagerInstalled() const override;

    QStringList GetInstalledPackages() override;
    bool RemovePackages(const QStringList& packages) override;
    bool InstallPackages(const QStringList& packages) override;

   private:
    CommandExecutorPtr m_commandExecutor;
};