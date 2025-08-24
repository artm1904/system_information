#include "format_util.h"

// Константы для преобразования.
namespace {
constexpr quint64 KIBI = 1ULL << 10;
constexpr quint64 MEBI = 1ULL << 20;
constexpr quint64 GIBI = 1ULL << 30;
constexpr quint64 TEBI = 1ULL << 40;
}  // namespace

QString FormatUtil::FormatBytes(quint64 bytes) {
    if (bytes < KIBI) return QStringLiteral("%1 B").arg(bytes);
    if (bytes < MEBI)
        return QStringLiteral("%1 KiB").arg(static_cast<double>(bytes) / KIBI, 0, 'f', 1);
    if (bytes < GIBI)
        return QStringLiteral("%1 MiB").arg(static_cast<double>(bytes) / MEBI, 0, 'f', 2);
    if (bytes < TEBI)
        return QStringLiteral("%1 GiB").arg(static_cast<double>(bytes) / GIBI, 0, 'f', 2);

    return QStringLiteral("%1 TiB").arg(static_cast<double>(bytes) / TEBI, 0, 'f', 2);
}
