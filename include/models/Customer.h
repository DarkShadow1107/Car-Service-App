#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <string>
#include <vector>
#include "Vehicle.h"

class Customer {
private:
    std::string firstName;
    std::string lastName;
    std::string phoneNumber;
    std::vector<Vehicle> vehicles;
public:
    Customer();
    Customer(const std::string&, const std::string&, const std::string&);
    void addVehicle(const Vehicle&);
    void showDetails() const;
    void updateInfo(const std::string&, const std::string&, const std::string&);
    void deleteVehicle(const std::string& licensePlate);
    const std::vector<Vehicle>& getVehicles() const;
    const std::string& getFirstName() const;
    const std::string& getLastName() const;
    const std::string& getPhoneNumber() const;
    void setFirstName(const std::string& fn);
    void setLastName(const std::string& ln);
    void setPhoneNumber(const std::string& pn);
};

#endif // CUSTOMER_H
