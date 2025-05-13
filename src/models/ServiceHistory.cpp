#include "../../include/models/ServiceHistory.h"
#include <iostream>

using namespace std;

ServiceHistory::ServiceHistory() {}
ServiceHistory::ServiceHistory(const Vehicle& v) : vehicle(v) {}

void ServiceHistory::addService(const Service& s) {
    servicesPerformed.push_back(s);
}

void ServiceHistory::showHistory() const {
    cout << "Service History for Vehicle: ";
    vehicle.showDetails();
    for (const auto& s : servicesPerformed) {
        s.showDetails();
    }
}

const Vehicle& ServiceHistory::getVehicle() const { return vehicle; }
void ServiceHistory::setVehicle(const Vehicle& v) { vehicle = v; }
const std::vector<Service>& ServiceHistory::getServicesPerformed() const { return servicesPerformed; }