#include "../../include/models/Vehicle.h"
#include <iostream>

using namespace std;

Vehicle::Vehicle() : year(0) {}
Vehicle::Vehicle(const string& mk, const string& mdl, int y, const string& lp, const string& ft)
    : maker(mk), model(mdl), year(y), licensePlate(lp), fuelType(ft) {}

void Vehicle::showDetails() const {
    cout << "  Vehicle: " << maker << " " << model << " (" << year << ") - " << licensePlate << ", Fuel: " << fuelType << endl;
}

const std::string& Vehicle::getMaker() const { return maker; }
const std::string& Vehicle::getModel() const { return model; }
int Vehicle::getYear() const { return year; }
const std::string& Vehicle::getLicensePlate() const { return licensePlate; }
const std::string& Vehicle::getFuelType() const { return fuelType; }