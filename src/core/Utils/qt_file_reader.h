#pragma once

#include "file_util.h"
#include "i_file_reader.h"

class QtFileReader : public IFileReader {
   public:
    QStringList ReadListFromFile(const QString& path) const override {
        return FileUtil::ReadListFromFile(path);
    }
};
