#pragma once

#include <QString>
#include <QStringList>


#include "../core_global.h"

class CORE_EXPORT CommandUtil {
   public:
    // Запрещаем создание экземпляров класса, так как он содержит только статические методы.
    CommandUtil() = delete;

    static QString SudoExec(QString& command, QStringList& args = {});
    static QString Exec(QString& command, QStringList& args = {});
    static bool IsExecutable(QString* command);
};