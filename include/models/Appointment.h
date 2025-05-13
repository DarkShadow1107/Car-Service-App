#ifndef APPOINTMENT_H
#define APPOINTMENT_H
#include <string>
#include "Customer.h"
#include "Vehicle.h"
#include "Mechanic.h"
#include "Service.h"

class Appointment {
private:
    Customer customer;
    Vehicle vehicle;
    Mechanic mechanic;
    Service service;
    std::string date;
public:
    Appointment();
    Appointment(const Customer&, const Vehicle&, const Mechanic&, const Service&, const std::string&);
    void showDetails() const;
    const Customer& getCustomer() const;
    const Vehicle& getVehicle() const;
    const Mechanic& getMechanic() const;
    const Service& getService() const;
    const std::string& getDate() const;
};

#endif // APPOINTMENT_H
