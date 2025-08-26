#include "command_ulit.h"

#include <QDebug>
#include <QFile>
#include <QProcess>
#include <memory>

QString CommandUtil::SudoExec(const QString& command, QStringList args) {
    args.push_front(command);

    QString result{""};

    try {
        result = CommandUtil::Exec("pkexec", args);
    } catch (const QString& ex) {
        qCritical() << ex;
    }
    return result;
}

// TODO реализация CommandUtil::Exec с помощью QProcess для асинхронного выполнения команды
QString CommandUtil::Exec(const QString& command, const QStringList& args) {
    auto process = std::make_unique<QProcess>();

    process->start(command, args);

    if (!process->waitForFinished(30000)) {
        process->kill();  // Если процесс не завершился, принудительно убиваем его.
        process->close();
        throw QString("Command timed out: %1").arg(command);
    }

    if (process->exitStatus() == QProcess::CrashExit || process->exitCode() != 0) {
        QString error = QString::fromUtf8(process->readAllStandardError()).trimmed();
        if (error.isEmpty()) {
            // Если stderr пуст, используем стандартную ошибку QProcess.
            error = process->errorString();
        }
        throw QString("Failed to execute '%1': %2").arg(command, error);
    } else {
        QTextStream stdOut{process->readAllStandardOutput()};
        return stdOut.readAll();
    }
}

bool CommandUtil::IsExecutable(const QString& command) {
    QStringList paths;
    paths << "/usr/bin" << "/usr/sbin" << "/bin" << "/sbin";

    for (const QString& path : paths) {
        if (QFile::exists(path + "/" + command)) {
            return true;
        }
    }
    return false;
}
