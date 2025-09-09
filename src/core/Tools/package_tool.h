#pragma once

#include <QObject>
#include <QString>
#include <QStringList>
#include <memory>

#include "../Utils/command_ulit.h"
#include "../core_global.h"
#include "i_package_manager.h"

/**
 * @brief Контекст для работы с пакетными менеджерами системы.
 * Использует паттерн "Стратегия".
 */
class CORE_EXPORT PackageTool : public QObject {
    Q_OBJECT

    /**
     * @brief Конструктор. Обнаруживает доступные в системе пакетные менеджеры.
     * @param executor Указатель на исполнителя команд.
     */
    explicit PackageTool(CommandExecutorPtr commandExecutor, QObject* parent = nullptr);

    // Возвращает список имен доступных менеджеров (например, ["pacman", "yay"])
    QStringList AvailablePackageManagers() const;

   public slots:
    QStringList GetInstalledPackages(const QString& managerName);
    bool RemovePackages(const QString& managerName, const QStringList& packages);
    bool InstallPackages(const QString& managerName, const QStringList& packages);

   private:
    // Храним список доступных стратегий
    QList<PackageManagerPtr> m_packageManagers;

    CommandExecutorPtr m_commandExecutor;
};