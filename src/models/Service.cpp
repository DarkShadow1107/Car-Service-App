#include "../../include/models/Service.h"
#include <iostream>

using namespace std;

Service::Service() : price(0.0) {}
Service::Service(const string& n, double p) : name(n), price(p) {}

void Service::showDetails() const {
    cout << "Service: " << name << ", Price: $" << price << endl;
}

const string& Service::getName() const { return name; }
double Service::getPrice() const { return price; }