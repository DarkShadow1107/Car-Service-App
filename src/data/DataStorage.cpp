#include "../../include/data/DataStorage.h"
#include <fstream>
#include <sstream>

DataStorage::DataStorage() : dataFilePath("src/data/data.txt") {}
DataStorage::DataStorage(const std::string& filePath) : dataFilePath(filePath) {}

// Example usage of dataFilePath in load/save functions
bool DataStorage::loadCustomers(std::vector<Customer>& customers, const std::string& filename) {
    std::ifstream file(filename.empty() ? dataFilePath : filename);
    // ...stub: implement file reading logic...
    return true;
}

bool DataStorage::saveCustomers(const std::vector<Customer>& customers, const std::string& filename) {
    std::ofstream file(filename.empty() ? dataFilePath : filename);
    // ...stub: implement file writing logic...
    return true;
}

bool DataStorage::loadVehicles(std::vector<Vehicle>&, const std::string&) { return true; }
bool DataStorage::saveVehicles(const std::vector<Vehicle>&, const std::string&) { return true; }
bool DataStorage::loadMechanics(std::vector<Mechanic>&, const std::string&) { return true; }
bool DataStorage::saveMechanics(const std::vector<Mechanic>&, const std::string&) { return true; }

bool DataStorage::loadAppointments(std::vector<Appointment>& appointments) {
    appointments.clear();
    std::ifstream file(dataFilePath);
    if (!file.is_open()) return false;
    std::string line;
    while (getline(file, line)) {
        if (line.rfind("APPOINTMENT|", 0) == 0) {
            std::stringstream ss(line);
            std::string token, cFirst, cLast, cPhone, vMaker, vModel, vYear, vPlate, vFuel, mName, mSpec, sName, sPrice, date;
            getline(ss, token, '|');
            getline(ss, cFirst, '|'); getline(ss, cLast, '|'); getline(ss, cPhone, '|');
            getline(ss, vMaker, '|'); getline(ss, vModel, '|'); getline(ss, vYear, '|'); getline(ss, vPlate, '|'); getline(ss, vFuel, '|');
            getline(ss, mName, '|'); getline(ss, mSpec, '|');
            getline(ss, sName, '|'); getline(ss, sPrice, '|');
            getline(ss, date, '|');
            Customer cust(cFirst, cLast, cPhone);
            Vehicle veh(vMaker, vModel, stoi(vYear), vPlate, vFuel);
            Mechanic mech(mName, mSpec);
            Service serv(sName, stod(sPrice));
            appointments.push_back(Appointment(cust, veh, mech, serv, date));
        }
    }
    return true;
}

bool DataStorage::saveAppointments(const std::vector<Appointment>& appointments) {
    std::ofstream file(dataFilePath, std::ios::app);
    if (!file.is_open()) return false;
    for (const auto& a : appointments) {
        file << "APPOINTMENT|"
             << a.getCustomer().getFirstName() << '|' << a.getCustomer().getLastName() << '|' << a.getCustomer().getPhoneNumber() << '|'
             << a.getVehicle().getMaker() << '|' << a.getVehicle().getModel() << '|' << a.getVehicle().getYear() << '|' << a.getVehicle().getLicensePlate() << '|' << a.getVehicle().getFuelType() << '|'
             << a.getMechanic().getName() << '|' << a.getMechanic().getSpecialization() << '|'
             << a.getService().getName() << '|' << a.getService().getPrice() << '|'
             << a.getDate() << '\n';
    }
    return true;
}

bool DataStorage::loadServiceHistory(std::vector<ServiceHistory>& histories) {
    histories.clear();
    std::ifstream file(dataFilePath);
    if (!file.is_open()) return false;
    std::string line;
    ServiceHistory* currentHistory = nullptr;
    while (getline(file, line)) {
        if (line.rfind("SERVICE_HISTORY|", 0) == 0) {
            std::stringstream ss(line);
            std::string token, maker, model, yearStr, plate, fuel;
            getline(ss, token, '|');
            getline(ss, maker, '|');
            getline(ss, model, '|');
            getline(ss, yearStr, '|');
            getline(ss, plate, '|');
            getline(ss, fuel, '|');
            histories.push_back(ServiceHistory(Vehicle(maker, model, stoi(yearStr), plate, fuel)));
            currentHistory = &histories.back();
        } else if (line.rfind("SERVICE_PERFORMED|", 0) == 0 && currentHistory) {
            std::stringstream ss(line);
            std::string token, name, priceStr;
            getline(ss, token, '|');
            getline(ss, name, '|');
            getline(ss, priceStr, '|');
            currentHistory->addService(Service(name, stod(priceStr)));
        }
    }
    return true;
}

bool DataStorage::saveServiceHistory(const std::vector<ServiceHistory>& histories) {
    std::ofstream file(dataFilePath, std::ios::app);
    if (!file.is_open()) return false;
    for (const auto& h : histories) {
        const Vehicle& v = h.getVehicle();
        file << "SERVICE_HISTORY|" << v.getMaker() << '|' << v.getModel() << '|' << v.getYear() << '|' << v.getLicensePlate() << '|' << v.getFuelType() << '\n';
        for (const auto& s : h.getServicesPerformed()) {
            file << "SERVICE_PERFORMED|" << s.getName() << '|' << s.getPrice() << '\n';
        }
    }
    return true;
}

bool DataStorage::saveAll(const std::vector<Customer>& customers) {
    std::ofstream file(dataFilePath);
    if (!file.is_open()) return false;
    for (const auto& c : customers) {
        file << "Customer: " << c.getFirstName() << " " << c.getLastName() << ", " << c.getPhoneNumber() << "\n";
        for (const auto& v : c.getVehicles()) {
            file << "Vehicle: " << v.getMaker() << ", " << v.getModel() << ", " << v.getYear() << ", " << v.getLicensePlate() << ", " << v.getFuelType() << "\n";
        }
    }
    return true;
}

bool DataStorage::loadAll(std::vector<Customer>& customers) {
    customers.clear();
    std::ifstream file(dataFilePath);
    if (!file.is_open()) return false;
    std::string line;
    Customer currentCustomer;
    while (getline(file, line)) {
        if (line.rfind("Customer:", 0) == 0) {
            if (!currentCustomer.getFirstName().empty()) {
                customers.push_back(currentCustomer);
            }
            size_t colon = line.find(":");
            size_t comma = line.rfind(",");
            std::string name = line.substr(colon + 1, comma - colon - 1);
            std::string phone = line.substr(comma + 2);
            size_t space = name.rfind(' ');
            std::string first = name.substr(0, space);
            std::string last = name.substr(space + 1);
            currentCustomer = Customer(first, last, phone);
        } else if (line.rfind("Vehicle:", 0) == 0) {
            size_t colon = line.find(":");
            std::string rest = line.substr(colon + 1);
            std::stringstream ss(rest);
            std::string maker, model, yearStr, plate, fuel;
            getline(ss, maker, ',');
            getline(ss, model, ',');
            getline(ss, yearStr, ',');
            getline(ss, plate, ',');
            getline(ss, fuel);
            // Remove leading/trailing spaces
            auto trim = [](std::string& s) { while (!s.empty() && (s[0] == ' ')) s.erase(0, 1); while (!s.empty() && (s[s.size()-1] == ' ')) s.pop_back(); };
            trim(maker); trim(model); trim(yearStr); trim(plate); trim(fuel);
            Vehicle v(maker, model, stoi(yearStr), plate, fuel);
            currentCustomer.addVehicle(v);
        }
    }
    if (!currentCustomer.getFirstName().empty()) {
        customers.push_back(currentCustomer);
    }
    return true;
}