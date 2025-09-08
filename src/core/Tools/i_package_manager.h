#pragma once

#include <QStringList>

#include "../Utils/i_command_executor.h"

/**
 * @brief Интерфейс (стратегия) для взаимодействия с пакетным менеджером.
 */
class IPackageManager {
   public:
    virtual ~IPackageManager() = default;

    // Возврат имени пакетного менеджера
    virtual QString GetManagerName() const = 0;

    // Установлен ли данный пакетный менеджер в системе
    virtual bool IsManagerInstalled() const = 0;


    //Операции с пакетным менеджером
    virtual QStringList GetInstalledPackages() = 0;
    virtual bool RemovePackages(const QStringList& packages) = 0;
    virtual bool InstallPackages(const QStringList& packages) = 0;
};

using PackageManagerPtr = std::shared_ptr<IPackageManager>;
