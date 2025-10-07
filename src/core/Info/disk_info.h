#pragma once

#include "../Utils/file_util.h"
#include "../Utils/command_ulit.h"
#include "../core_global.h"


class Disk {
   public:
    Disk() {}

    QString name;
    quint64 size;
    quint64 free;
    quint64 used;
};

class CORE_EXPORT DiskInfo {
   public:
    DiskInfo(CommandExecutorPtr commandExecutor);

    QList<Disk> GetDisks() const;
    void UpdateDiskInfo();

   private:
    QList<Disk> m_disks;
    CommandExecutorPtr m_commandExecutor;
};