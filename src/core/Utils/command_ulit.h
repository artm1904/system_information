#pragma once

#include <QString>
#include <QStringList>

#include "../core_global.h"

class CORE_EXPORT CommandUtil {
   public:
    /**
     * @brief Запрещает создание экземпляров класса, так как он содержит только статические методы.
     */
    CommandUtil() = delete;

    /**
     * @brief Выполняет команду с повышенными привилегиями, используя pkexec.
     * @details Это блокирующий вызов. Функция ожидает завершения процесса не более 30 секунд.
     *          В случае ошибки она будет записана в лог через qCritical.
     * @param command Команда для выполнения.
     * @param args Список аргументов для команды.
     * @return Стандартный вывод (stdout) команды в виде QString. В случае ошибки возвращает пустую
     * строку.
     */
    static QString SudoExec(const QString& command, QStringList args = {});

    /**
     * @brief Выполняет команду и ожидает ее завершения.
     * @details Это блокирующий вызов. Функция ожидает завершения процесса не более 30 секунд.
     * @param command Команда для выполнения.
     * @param args Список аргументов для команды.
     * @return Стандартный вывод (stdout) команды.
     * @throw QString В случае ошибки (ненулевой код выхода, сбой или таймаут) выбрасывает
     * исключение с сообщением об ошибке.
     */
    static QString Exec(const QString& command, const QStringList& args = {});
    /**
     * @brief Проверяет, существует ли исполняемый файл в системных путях (переменная окружения
     * PATH).
     * @param command Имя команды для проверки (например, "ls", "grep").
     * @return true, если команда найдена и является исполняемым файлом, иначе false.
     */
    static bool IsExecutable(const QString& command);
};