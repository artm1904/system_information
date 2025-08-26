#pragma once

#include <QString>
#include <iostream>

#include "../Utils/command_ulit.h"
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

std::ostream& operator<<(std::ostream& os, const Service& service) {
    os << "Name: " << service.name.toStdString()
       << ", Status: " << (service.status ? "enabled" : "disabled")
       << ", Active: " << (service.active ? "true" : "false");
    return os;
}

class CORE_EXPORT ServiceTool {
   public:
    ServiceTool() = default;

    QList<Service> GetServicesWithSystemctl();

    bool ServiceIsActive(const QString& serviceName);
    bool ChangeServiceStatus(const QString& serviceName, bool status);
    bool ChangeServiceActive(const QString& serviceName, bool active);
    bool ServiceIsEnable(const QString& serviceName);

   private:
};
