#ifndef VEHICLE_H
#define VEHICLE_H
#include <string>

class Vehicle {
private:
    std::string maker;
    std::string model;
    int year;
    std::string licensePlate;
    std::string fuelType;
public:
    Vehicle();
    Vehicle(const std::string&, const std::string&, int, const std::string&, const std::string&);
    void showDetails() const;
    const std::string& getMaker() const;
    const std::string& getModel() const;
    int getYear() const;
    const std::string& getLicensePlate() const;
    const std::string& getFuelType() const;
    // ...other getters/setters as needed...
};

#endif // VEHICLE_H
