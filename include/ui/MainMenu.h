#ifndef MAIN_MENU_H
#define MAIN_MENU_H
#include <vector>
#include "../models/Customer.h"
#include "../models/Mechanic.h"
#include "../models/Appointment.h"
#include "../models/ServiceHistory.h"
#include "CustomerMenu.h"
#include "../data/DataStorage.h"
#include "../data/Inventory.h"

class MainMenu {
private:
    std::vector<Customer> customers;
    std::vector<Mechanic> mechanics;
    std::vector<Appointment> appointments;
    std::vector<ServiceHistory> serviceHistories;
    std::vector<Service> services;
    CustomerMenu* customerMenu;
    DataStorage dataStorage;
    Inventory inventory;
    void manageInventory();
public:
    MainMenu();
    ~MainMenu();
    void display();
    void manageCustomers();
    void manageAppointments();
    void listMechanics();
    void showServiceHistory();
    void exitApp();
    void loadData();
    void saveData();
    void addServiceRecord();
    void createAppointment();
    void listAppointments();
    void deleteAppointment();
};

#endif // MAIN_MENU_H