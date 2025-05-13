#include "../../include/models/Appointment.h"
#include <iostream>

using namespace std;

Appointment::Appointment() {}
Appointment::Appointment(const Customer& c, const Vehicle& v, const Mechanic& m, const Service& s, const string& d)
    : customer(c), vehicle(v), mechanic(m), service(s), date(d) {}

void Appointment::showDetails() const {
    cout << "Appointment on " << date << ":\n";
    customer.showDetails();
    vehicle.showDetails();
    mechanic.showDetails();
    service.showDetails();
}

const Customer& Appointment::getCustomer() const { return customer; }
const Vehicle& Appointment::getVehicle() const { return vehicle; }
const Mechanic& Appointment::getMechanic() const { return mechanic; }
const Service& Appointment::getService() const { return service; }
const std::string& Appointment::getDate() const { return date; }