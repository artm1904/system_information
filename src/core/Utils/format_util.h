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
    
    static QString formatBytes(quint64 bytes);
};