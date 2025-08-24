#pragma once

#include <QFile>
#include <QStringList>
#include <QString>

#include "../core_global.h"

/**
 * @brief Класс с утилитами для работы с файлами.
 *
 * Макрос CORE_EXPORT делает класс видимым за пределами библиотеки.
 */
class CORE_EXPORT FileUtil {
   public:
    /**
     * @brief Запрещает создание экземпляров класса.
     */
    FileUtil() = delete;

    /**
     * @brief Читает все содержимое файла в одну строку.
     * @param path Путь к файлу.
     * @param mode Режим открытия файла (по умолчанию QIODevice::ReadOnly).
     * @return QString с содержимым файла или пустая строка в случае ошибки.
     */
    static QString ReadStringFromFile(const QString& path,
                                      QIODevice::OpenMode mode = QIODevice::ReadOnly);
    /**
     * @brief Читает текстовый файл построчно в список строк.
     * @param path Путь к файлу.
     * @param mode Режим открытия файла (по умолчанию QIODevice::ReadOnly).
     * @return QStringList, где каждый элемент - это строка из файла.
     */
    static QStringList ReadListFromFile(const QString& path,
                                        QIODevice::OpenMode mode = QIODevice::ReadOnly);

    /**
     * @brief Записывает данные в файл.
     *
     * Если файл существует, его содержимое будет перезаписано, если не указан другой режим.
     * @param path Путь к файлу.
     * @param data Строка для записи.
     * @param mode Режим открытия файла (по умолчанию QIODevice::WriteOnly).
     * @return true в случае успеха, иначе false.
     */
    static bool WriteFile(const QString& path, const QString& data,
                          QIODevice::OpenMode mode = QIODevice::WriteOnly);

    /**
     * @brief Возвращает список имен файлов в указанной директории.
     * @param path Путь к директории.
     * @return QStringList с именами файлов.
     */
    static QStringList DirectoryList(const QString& path);

    /**
     * @brief Рекурсивно вычисляет размер файла или директории.
     * @param path Путь к файлу или директории.
     * @return Общий размер в байтах.
     */
    static quint64 GetFileSize(const QString& path);
};