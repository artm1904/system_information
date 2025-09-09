#pragma once

#include <QDebug>
#include <QObject>

#include "../Utils/command_ulit.h"
#include "../Utils/file_util.h"
#include "../core_global.h"
#include "process.h"

class CORE_EXPORT ProcessInfo : QObject {
    Q_OBJECT
   public:
    explicit ProcessInfo(CommandExecutorPtr commandExecutor, QObject* parent = nullptr);

    QList<Process> GetProcessList() const;

   public slots:
    void UpdateProcessList();

   private:
    QList<Process> m_processList;
    CommandExecutorPtr m_commandExecutor;
};