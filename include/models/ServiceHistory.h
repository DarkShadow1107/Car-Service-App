#ifndef SERVICE_HISTORY_H
#define SERVICE_HISTORY_H
#include <string>
#include <vector>
#include "Vehicle.h"
#include "Service.h"

class ServiceHistory {
private:
    Vehicle vehicle;
    std::vector<Service> servicesPerformed;
public:
    ServiceHistory();
    ServiceHistory(const Vehicle& v);
    void setVehicle(const Vehicle& v);
    const std::vector<Service>& getServicesPerformed() const;
    void addService(const Service&);
    void showHistory() const;
    const Vehicle& getVehicle() const;
};

#endif // SERVICE_HISTORY_H
