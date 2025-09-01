#pragma once

#include <QStringList>

#include "../Utils/i_command_executor.h"

/**
 * @brief Интерфейс (стратегия) для взаимодействия с пакетным менеджером.
 */
class IPackageManager {
   public:
    virtual ~IPackageManager() = default;

    virtual QString GetManagerName() const = 0;

    virtual bool IsManagerInstalled() const = 0;

    virtual QStringList GetInstalledPackages() = 0;
    virtual bool RemovePackages(const QStringList& packages) = 0;
    virtual bool InstallPackages(const QStringList& packages) = 0;
};

using PackageManagerPtr = std::shared_ptr<IPackageManager>;
