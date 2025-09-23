#pragma once

#include <QString>
#include <iostream>
#include <memory>

#include "../Utils/command_ulit.h"
#include "../Utils/i_command_executor.h"
#include "../core_global.h"

class Service {
   public:
    Service(QString name, bool status, bool active) : name(name), status(status), active(active) {}

    QString name;
    bool status;
    bool active;

    friend std::ostream& operator<<(std::ostream& os, const Service& service);

   private:
};

inline std::ostream& operator<<(std::ostream& os, const Service& service) {
    os << "Name: " << service.name.toStdString()
       << ", Status: " << (service.status ? "enabled" : "disabled")
       << ", Active: " << (service.active ? "true" : "false");
    return os;
}

class CORE_EXPORT ServiceTool {
   public:
    /**
     * @brief Конструктор ServiceTool.
     * @param commandExecutor Указатель на исполнителя команд.
     */
    explicit ServiceTool(CommandExecutorPtr commandExecutor)
        : m_commandExecutor(commandExecutor) {};
    ~ServiceTool() = default;

    QList<Service> GetServicesWithSystemctl();

    bool ServiceIsActive(const QString& serviceName);
    bool ServiceIsEnable(const QString& serviceName);
    bool ChangeServiceStatus(const QString& serviceName, bool status);
    bool ChangeServiceActive(const QString& serviceName, bool active);

   private:
    CommandExecutorPtr m_commandExecutor;
};
