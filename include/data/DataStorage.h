#ifndef DATA_STORAGE_H
#define DATA_STORAGE_H
#include <vector>
#include <string>
#include "../models/Customer.h"
#include "../models/Vehicle.h"
#include "../models/Mechanic.h"
#include "../models/Appointment.h"
#include "../models/Service.h"
#include "../models/ServiceHistory.h"

class DataStorage {
private:
    std::string dataFilePath = "src/data/data.txt";
public:
    DataStorage();
    DataStorage(const std::string& filePath);
    bool loadCustomers(std::vector<Customer>&, const std::string& filename);
    bool saveCustomers(const std::vector<Customer>&, const std::string& filename);
    bool loadVehicles(std::vector<Vehicle>&, const std::string& filename);
    bool saveVehicles(const std::vector<Vehicle>&, const std::string& filename);
    bool loadMechanics(std::vector<Mechanic>&, const std::string& filename);
    bool saveMechanics(const std::vector<Mechanic>&, const std::string& filename);
    bool loadAppointments(std::vector<Appointment>& appointments);
    bool saveAppointments(const std::vector<Appointment>& appointments);
    bool loadServiceHistory(std::vector<ServiceHistory>& histories);
    bool saveServiceHistory(const std::vector<ServiceHistory>& histories);
    bool loadAll(std::vector<Customer>& customers);
    bool saveAll(const std::vector<Customer>& customers);
    // ...other load/save functions as needed...
};

#endif // DATA_STORAGE_H