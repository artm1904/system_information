#pragma once

#include <QString>

#include "../core_global.h"

/**
 * @brief Класс с утилитами для форматирования данных.
 *
 * Макрос CORE_EXPORT делает класс видимым за пределами библиотеки.
 */
class CORE_EXPORT FormatUtil {
   public:
    // Запрещаем создание экземпляров класса, так как он содержит только статические методы.
    FormatUtil() = delete;

    /**
     * @brief Форматирует количество байт в человекочитаемую строку.
     *
     * Преобразует числовое значение байт в строку с использованием
     * двоичных префиксов (KiB, MiB, GiB, TiB).
     * @param bytes Количество байт для форматирования.
     * @return QString с отформатированным размером.
     */
    static QString FormatBytes(quint64 bytes);
};