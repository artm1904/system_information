#include "disk_info.h"

#include <QDebug>
#include <QRegularExpression>

DiskInfo::DiskInfo(CommandExecutorPtr commandExecutor) : m_commandExecutor(commandExecutor) {}

QList<Disk> DiskInfo::GetDisks() const { return m_disks; }

void DiskInfo::UpdateDiskInfo() {
    m_disks.clear();  // if block devise was plag or unplaged it needs delete

    QSet<QString> processedDevices;

    try {
        QStringList lines = m_commandExecutor->Exec(QString{"df"}, QStringList{"-Pl"}).split("\n");
        if (lines.isEmpty() == false) {
            for (int i = 1; i < lines.size(); i++) {
                QString line = lines.at(i);
                QStringList fields = line.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);

                // qDebug() << "Disk lines found:" << fields;

                if (fields.size() >= 6 &&
                    fields.first().startsWith("/dev")) {  // Get only block device

                    QString deviceName = fields.at(0);

                    if (!processedDevices.contains(deviceName)) {
                        Disk disk;
                        disk.name = fields.at(0);
                        // df -Pl show info in 1024-byte blocks, convert in bytes
                        disk.size = fields.at(1).toULongLong() * 1024;
                        disk.used = fields.at(2).toULongLong() * 1024;
                        disk.free = fields.at(3).toULongLong() * 1024;

                        m_disks << disk;
                        processedDevices.insert(deviceName);
                    }
                }
            }
        }
    } catch (const QString& ex) {
        qCritical() << "Failed to update disk info:" << ex;
    }
}