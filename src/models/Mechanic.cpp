#include "../../include/models/Mechanic.h"
#include <iostream>

using namespace std;

Mechanic::Mechanic() {}
Mechanic::Mechanic(const string& n, const string& s) : name(n), specialization(s) {}

void Mechanic::showDetails() const {
    cout << "Mechanic: " << name << ", Specialization: " << specialization << endl;
}

const string& Mechanic::getName() const { return name; }
const string& Mechanic::getSpecialization() const { return specialization; }