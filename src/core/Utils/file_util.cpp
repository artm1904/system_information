#include "file_util.h"

#include <QDir>
#include <QTextStream>

QString FileUtil::ReadStringFromFile(const QString& path, QIODevice::OpenMode mode) {
    QFile file{path};

    QString data;

    if (file.open(mode | QIODevice::Text)) {
        data = file.readAll();
        file.close();
    } else {
        qWarning() << "Failed to open file for reading:" << path << "Error:" << file.errorString();
    }

    return data;
}

QStringList FileUtil::ReadListFromFile(const QString& path, QIODevice::OpenMode mode) {
    QFile file{path};
    QStringList list;

    if (file.open(mode | QIODevice::Text)) {  // QIODevice::Text для обработки конца строк
        QTextStream in{&file};                // читаем большой текстовый файл построчно
        // while(!in.atEnd()) is not suitable for в /proc/*.
        for (QString line = in.readLine(); !line.isNull(); line = in.readLine()) {
            list.append(line);
        }
        file.close();
    } else {
        qWarning() << "Failed to open file for reading list:" << path
                   << "Error:" << file.errorString();
    }
    return list;
}

bool FileUtil::WriteFile(const QString& path, const QString& data, QIODevice::OpenMode mode) {
    QFile file{path};

    if (file.open(mode | QIODevice::Text)) {  // QIODevice::Text для обработки конца строк
        QTextStream stream{&file};
        stream << data;
        file.close();

        return true;
    } else {
        qWarning() << "Failed to open file for writing:" << path << "Error:" << file.errorString();
    }
    return false;
}

QStringList FileUtil::DirectoryList(const QString& path) {
    QDir dir{path};

    QStringList list;

    if (dir.exists()) {
        for (const QFileInfo& info : dir.entryInfoList(QDir::NoDotAndDotDot | QDir::Files)) {
            list << info.fileName();
        }
    }
    return list;
}

// TODO Рекурсивный подсчет большой директории "заморозит" интерфейс, в будущем реализовать работу в
// отдельном потоке
quint64 FileUtil::GetFileSize(const QString& path) {
    QFileInfo fileInfo{path};
    if (!fileInfo.exists()) {
        return 0;
    }

    if (fileInfo.isFile()) {
        return fileInfo.size();
    }

    if (fileInfo.isDir()) {
        quint64 dirSize = 0;
        QDir dir(path);
        for (const QFileInfo& info : dir.entryInfoList(QDir::NoDotAndDotDot | QDir::AllEntries)) {
            dirSize +=
                GetFileSize(info.absoluteFilePath());  // рекурсивный обход содержимого директории
        }
        return dirSize;
    }
    return 0;
}
