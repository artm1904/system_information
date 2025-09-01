#pragma once

#include <QString>
#include <QStringList>

#include "../core_global.h"
#include "i_command_executor.h"

/**
 * @brief Класс с утилитами для выполнения команд.
 */

class CORE_EXPORT CommandUtil : public ICommandExecutor {
   public:
    
    CommandUtil() = default;

    /**
     * @brief Выполняет команду с повышенными привилегиями, используя pkexec.
     * @details Это блокирующий вызов. Функция ожидает завершения процесса не более 30 секунд.
     *          В случае ошибки она будет записана в лог через qCritical.
     * @param command Команда для выполнения.
     * @param args Список аргументов для команды.
     * @return Стандартный вывод (stdout) команды в виде QString. В случае ошибки возвращает пустую
     * строку.
     */
     QString SudoExec(const QString& command, QStringList args = {}) override ;

    /**
     * @brief Выполняет команду и ожидает ее завершения.
     * @details Это блокирующий вызов. Функция ожидает завершения процесса не более 30 секунд.
     * @param command Команда для выполнения.
     * @param args Список аргументов для команды.
     * @return Стандартный вывод (stdout) команды.
     * @throw QString В случае ошибки (ненулевой код выхода, сбой или таймаут) выбрасывает
     * исключение с сообщением об ошибке.
     */
     QString Exec(const QString& command, const QStringList& args = {}) override ;
    /**
     * @brief Проверяет, существует ли исполняемый файл в системных путях (переменная окружения
     * PATH).
     * @param command Имя команды для проверки (например, "ls", "grep").
     * @return true, если команда найдена и является исполняемым файлом, иначе false.
     */
     bool IsExecutable(const QString& command) const override;
};