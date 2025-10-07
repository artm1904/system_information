#include "disk_info.h"

#include <QDebug>
#include <QRegularExpression>

DiskInfo::DiskInfo(CommandExecutorPtr commandExecutor) : m_commandExecutor(commandExecutor) {}

QList<Disk> DiskInfo::GetDisks() const { return m_disks; }

void DiskInfo::UpdateDiskInfo() {
    try {
        QStringList lines = m_commandExecutor->Exec(QString{"df"}, QStringList{"-Pl"}).split("\n");
        if (lines.isEmpty() == false) {
            for (const QString& line : lines) {
                QStringList fields = line.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
                Disk disk;

                //qDebug() << "Disk lines found:" << fields;

                if (fields.size() >= 6) {
                    disk.size = fields[1].toULongLong();
                    disk.free = fields[2].toULongLong();
                    disk.used = fields[3].toULongLong();
                }

                m_disks << disk;
            }
        }
    } catch (const QString& ex) {
        qCritical() << "Failed to update disk info:" << ex;
    }
}