#pragma once

#include <QString>
#include <QStringList>
#include <memory>

/**
 * @brief Интерфейс (абстрактный класс) для исполнителя команд.
 * @details Позволяет подменять реального исполнителя на мок в тестах.
 */

class ICommandExecutor {
   public:
    virtual ~ICommandExecutor() = default;

    /**
     * @brief Выполняет команду с повышенными привилегиями.
     * @param command Команда для выполнения из-под суперпользователя.
     * @param args Аргументы для команды.
     * @return Стандартный вывод (stdout) команды.
     */

    virtual QString SudoExec(const QString& command, QStringList args = {}) = 0;
    /**
     * @brief Выполняет команду.
     * @param command Команда для выполнения.
     * @param args Аргументы для команды.
     * @return Стандартный вывод (stdout) команды.
     */
    virtual QString Exec(const QString& command, const QStringList& args = {}) = 0;

    /**
     * @brief Проверяет, существует ли исполняемый файл в системных путях.
     * @param command Имя команды для проверки.
     * @return true, если команда найдена и является исполняемым файлом, иначе false.
     */
    virtual bool IsExecutable(const QString& command) const = 0;
};

using CommandExecutorPtr = std::shared_ptr<ICommandExecutor>;