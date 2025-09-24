#pragma once

#include <QString>
#include <QStringList>
#include <memory>

// Dependecy injection for testing
class IFileReader {
   public:
    virtual ~IFileReader() = default;
    virtual QStringList ReadListFromFile(const QString& path) const = 0;
};

using FileReaderPtr = std::shared_ptr<IFileReader>;
