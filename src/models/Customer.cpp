#include <algorithm>
#include "../../include/models/Customer.h"
#include "../../include/models/Vehicle.h"
#include <iostream>

using namespace std;

Customer::Customer() {}
Customer::Customer(const string& f, const string& l, const string& p)
    : firstName(f), lastName(l), phoneNumber(p) {}

void Customer::addVehicle(const Vehicle& v) {
    vehicles.push_back(v);
}

void Customer::showDetails() const {
    cout << "Customer: " << firstName << " " << lastName << ", Phone: " << phoneNumber << endl;
    for (const auto& v : vehicles) {
        v.showDetails();
    }
}

void Customer::updateInfo(const string& f, const string& l, const string& p) {
    firstName = f;
    lastName = l;
    phoneNumber = p;
}

void Customer::deleteVehicle(const string& licensePlate) {
    vehicles.erase(remove_if(vehicles.begin(), vehicles.end(), [&](const Vehicle& v) {
        return v.getLicensePlate() == licensePlate;
    }), vehicles.end());
}

const vector<Vehicle>& Customer::getVehicles() const { return vehicles; }
const string& Customer::getFirstName() const { return firstName; }
const string& Customer::getLastName() const { return lastName; }
const string& Customer::getPhoneNumber() const { return phoneNumber; }
void Customer::setFirstName(const string& fn) { firstName = fn; }
void Customer::setLastName(const string& ln) { lastName = ln; }
void Customer::setPhoneNumber(const string& pn) { phoneNumber = pn; }