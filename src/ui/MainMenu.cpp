#include "../../include/ui/MainMenu.h"
#include "../../include/ui/CustomerMenu.h"
#include "../../include/models/Service.h"
#include "../../include/data/Inventory.h"
#include "../../include/Utilities.h"
#include <limits>
#include <iostream>
#include <windows.h>
#include <fstream>

using namespace std;

MainMenu::MainMenu() {
    customerMenu = new CustomerMenu(&customers, &dataStorage);
    // Default mechanics
    mechanics.push_back(Mechanic("Alice Brown", "Engine"));
    mechanics.push_back(Mechanic("Bob Smith", "Transmission"));
    mechanics.push_back(Mechanic("Carol White", "Electrical"));
    // Default services
    services.push_back(Service("Oil Change", 150));
    services.push_back(Service("Brake Inspection", 200));
    services.push_back(Service("Tire Rotation", 100));
    loadData();
}

MainMenu::~MainMenu() {
    saveData();
    delete customerMenu;
}

void MainMenu::loadData() {
    dataStorage.loadAll(customers);
    dataStorage.loadAppointments(appointments);
    dataStorage.loadServiceHistory(serviceHistories);
    inventory.load();
}

void MainMenu::saveData() {
    dataStorage.saveAll(customers);
    dataStorage.saveAppointments(appointments);
    dataStorage.saveServiceHistory(serviceHistories);
    inventory.save();
}

void MainMenu::display() {
    int choice = 0;
    do {
        system("cls");
        Utilities::setConsoleColor(Utilities::THEME_DARK_RED); // Title
        cout << "===== Car Service Management System =====\n";
        Utilities::setConsoleColor(Utilities::THEME_CREAM);
        cout << "1. Manage Customers\n";
        Utilities::setConsoleColor(Utilities::THEME_BLUE);
        cout << "2. Manage Appointments\n";
        Utilities::setConsoleColor(Utilities::THEME_PURPLE);
        cout << "3. List Mechanics\n";
        Utilities::setConsoleColor(Utilities::THEME_DARK_GREEN);
        cout << "4. Show Service History\n";
        Utilities::setConsoleColor(Utilities::THEME_LT_GREEN);
        cout << "5. Inventory Management\n";
        Utilities::setConsoleColor(Utilities::THEME_SALMON);
        cout << "6. Exit\n";
        Utilities::setConsoleColor(Utilities::THEME_CREAM);
        cout << "Select an option: ";
        Utilities::setConsoleColor(Utilities::THEME_CREAM);
        cin >> choice;
        cin.ignore();
        switch (choice) {
            case 1: manageCustomers(); break;
            case 2: manageAppointments(); break;
            case 3: listMechanics(); break;
            case 4: showServiceHistory(); break;
            case 5: manageInventory(); break;
            case 6: exitApp(); break;
            default:
                Utilities::setConsoleColor(Utilities::THEME_SALMON);
                cout << "Invalid option!\n";
                Utilities::setConsoleColor(Utilities::THEME_CREAM);
                system("pause");
                break;
        }
    } while (choice != 6);
}

void MainMenu::manageCustomers() {
    customerMenu->display();
}
void MainMenu::manageAppointments() {
    int choice = 0;
    do {
        system("cls");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
        cout << "===== Appointments Menu =====\n";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        cout << "1. Create Appointment\n";
        cout << "2. List Appointments\n";
        cout << "3. Delete Appointment\n";
        cout << "4. Back\n";
        cout << "Select an option: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch (choice) {
            case 1: createAppointment(); break;
            case 2: listAppointments(); break;
            case 3: deleteAppointment(); break;
            case 4: return;
            default: cout << "Invalid option!\n"; system("pause"); break;
        }
    } while (choice != 4);
}

void MainMenu::createAppointment() {
    if (customers.empty()) { cout << "No customers available!\n"; system("pause"); return; }
    cout << "Enter customer phone: ";
    string phone; getline(cin, phone);
    Customer* cust = nullptr;
    for (auto& c : customers) if (c.getPhoneNumber() == phone) cust = &c;
    if (!cust) { cout << "Customer not found!\n"; system("pause"); return; }
    if (cust->getVehicles().empty()) { cout << "Customer has no vehicles!\n"; system("pause"); return; }
    cout << "Select vehicle:\n";
    int idx = 1;
    for (const auto& v : cust->getVehicles()) {
        cout << idx << ". "; v.showDetails(); ++idx;
    }
    int vsel; cout << "Choice: "; cin >> vsel; cin.ignore();
    if (vsel < 1 || vsel > (int)cust->getVehicles().size()) { cout << "Invalid!\n"; system("pause"); return; }
    Vehicle vehicle = cust->getVehicles()[vsel-1];
    cout << "Select mechanic:\n";
    for (size_t i=0; i<mechanics.size(); ++i) cout << i+1 << ". ", mechanics[i].showDetails();
    int msel; cout << "Choice: "; cin >> msel; cin.ignore();
    if (msel < 1 || msel > (int)mechanics.size()) { cout << "Invalid!\n"; system("pause"); return; }
    Mechanic mechanic = mechanics[msel-1];
    cout << "Select service:\n";
    for (size_t i=0; i<services.size(); ++i) cout << i+1 << ". ", services[i].showDetails();
    int ssel; cout << "Choice: "; cin >> ssel; cin.ignore();
    if (ssel < 1 || ssel > (int)services.size()) { cout << "Invalid!\n"; system("pause"); return; }
    Service service = services[ssel-1];
    cout << "Enter date (YYYY-MM-DD): ";
    string date; getline(cin, date);
    appointments.push_back(Appointment(*cust, vehicle, mechanic, service, date));
    // Save appointment in requested format
    ofstream out("src/data/data.txt", ios::app);
    if (out.is_open()) {
        out << "Customer: " << cust->getFirstName() << " " << cust->getLastName() << ", " << cust->getPhoneNumber() << "\n";
        out << "Vehicle: " << vehicle.getMaker() << ", " << vehicle.getModel() << ", " << vehicle.getYear() << ", " << vehicle.getLicensePlate() << ", " << vehicle.getFuelType() << ";\n";
        out.close();
    }
    // Update inventory for the service
    if (service.getName() == "Oil Change") inventory.removeItem("Oil Filter", 1);
    if (service.getName() == "Brake Inspection") inventory.removeItem("Brake Pads", 1);
    if (service.getName() == "Tire Rotation") inventory.removeItem("Tire", 1);
    inventory.save();
    cout << "Appointment created!\n"; system("pause");
}

void MainMenu::listAppointments() {
    if (appointments.empty()) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        cout << "No appointments!\n";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        system("pause");
        return;
    }
    int idx = 1;
    for (const auto& a : appointments) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9 + (idx % 6));
        cout << "--- Appointment " << idx << " ---\n";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); // Green for customer
        cout << "Customer: " << a.getCustomer().getFirstName() << " " << a.getCustomer().getLastName() << ", " << a.getCustomer().getPhoneNumber() << "\n";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11); // Cyan for vehicle
        cout << "Vehicle: " << a.getVehicle().getMaker() << ", " << a.getVehicle().getModel() << ", " << a.getVehicle().getYear() << ", " << a.getVehicle().getLicensePlate() << ", " << a.getVehicle().getFuelType() << "\n";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); // Yellow for mechanic
        cout << "Mechanic: " << a.getMechanic().getName() << " (" << a.getMechanic().getSpecialization() << ")\n";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13); // Magenta for service
        cout << "Service: " << a.getService().getName() << " ($" << a.getService().getPrice() << ")\n";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // White for date
        cout << "Date: " << a.getDate() << "\n\n";
        ++idx;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    system("pause");
}

void MainMenu::deleteAppointment() {
    if (appointments.empty()) { cout << "No appointments!\n"; system("pause"); return; }
    listAppointments();
    cout << "Enter appointment number to delete: ";
    int idx; cin >> idx; cin.ignore();
    if (idx < 1 || idx > (int)appointments.size()) { cout << "Invalid!\n"; system("pause"); return; }
    appointments.erase(appointments.begin() + (idx-1));
    cout << "Deleted!\n"; system("pause");
}

void MainMenu::listMechanics() {
    if (mechanics.empty()) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); // Red for error
        cout << "No mechanics!\n";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        system("pause");
        return;
    }
    int idx = 1;
    for (const auto& m : mechanics) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9 + (idx % 6));
        cout << idx << ". ";
        m.showDetails();
        ++idx;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    system("pause");
}

void MainMenu::addServiceRecord() {
    if (customers.empty()) { cout << "No customers!\n"; system("pause"); return; }
    cout << "Enter customer phone: ";
    string phone; getline(cin, phone);
    Customer* cust = nullptr;
    for (auto& c : customers) if (c.getPhoneNumber() == phone) cust = &c;
    if (!cust) { cout << "Customer not found!\n"; system("pause"); return; }
    if (cust->getVehicles().empty()) { cout << "Customer has no vehicles!\n"; system("pause"); return; }
    cout << "Select vehicle:\n";
    int idx = 1;
    for (const auto& v : cust->getVehicles()) {
        cout << idx << ". "; v.showDetails(); ++idx;
    }
    int vsel; cout << "Choice: "; cin >> vsel; cin.ignore();
    if (vsel < 1 || vsel > (int)cust->getVehicles().size()) { cout << "Invalid!\n"; system("pause"); return; }
    Vehicle vehicle = cust->getVehicles()[vsel-1];
    cout << "Select service to add:\n";
    for (size_t i=0; i<services.size(); ++i) cout << i+1 << ". ", services[i].showDetails();
    int ssel; cout << "Choice: "; cin >> ssel; cin.ignore();
    if (ssel < 1 || ssel > (int)services.size()) { cout << "Invalid!\n"; system("pause"); return; }
    Service service = services[ssel-1];
    // Find or create service history for this vehicle
    ServiceHistory* history = nullptr;
    for (auto& h : serviceHistories) {
        if (h.getVehicle().getLicensePlate() == vehicle.getLicensePlate()) {
            history = &h;
            break;
        }
    }
    if (!history) {
        serviceHistories.push_back(ServiceHistory(vehicle));
        history = &serviceHistories.back();
    }
    history->addService(service);
    cout << "Service record added!\n"; system("pause");
}

void MainMenu::showServiceHistory() {
    if (customers.empty()) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        cout << "No customers!\n";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        system("pause");
        return;
    }
    cout << "Enter customer phone: ";
    string phone; getline(cin, phone);
    Customer* cust = nullptr;
    for (auto& c : customers) if (c.getPhoneNumber() == phone) cust = &c;
    if (!cust) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        cout << "Customer not found!\n";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        system("pause");
        return;
    }
    if (cust->getVehicles().empty()) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        cout << "Customer has no vehicles!\n";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        system("pause");
        return;
    }
    cout << "Select vehicle:\n";
    int idx = 1;
    for (const auto& v : cust->getVehicles()) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9 + (idx % 6));
        cout << idx << ". "; v.showDetails(); ++idx;
    }
    int vsel; cout << "Choice: "; cin >> vsel; cin.ignore();
    if (vsel < 1 || vsel > (int)cust->getVehicles().size()) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        cout << "Invalid!\n";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        system("pause");
        return;
    }
    Vehicle vehicle = cust->getVehicles()[vsel-1];
    // Display all appointments for this vehicle
    bool found = false;
    Utilities::setConsoleColor(Utilities::THEME_TEAL);
    cout << "--- Appointment History for this Vehicle ---\n";
    idx = 1;
    for (const auto& a : appointments) {
        if (a.getVehicle().getLicensePlate() == vehicle.getLicensePlate()) {
            found = true;
            Utilities::setConsoleColor(Utilities::THEME_LT_GREEN);
            cout << idx << ". Date: " << a.getDate() << " | Service: " << a.getService().getName() << " | Mechanic: " << a.getMechanic().getName() << "\n";
            ++idx;
        }
    }
    if (!found) {
        Utilities::setConsoleColor(Utilities::THEME_SALMON);
        cout << "No appointments found for this vehicle.\n";
    }
    Utilities::setConsoleColor(Utilities::THEME_CREAM);
    system("pause");
}

void MainMenu::exitApp() {
    saveData();
    cout << "Exiting..." << endl;
}

void MainMenu::manageInventory() {
    int choice = 0;
    do {
        system("cls");
        Utilities::setConsoleColor(Utilities::THEME_TEAL);
        cout << "===== Inventory Management =====\n";
        Utilities::setConsoleColor(Utilities::THEME_CREAM);
        cout << "1. Show Inventory\n2. Add Item\n3. Remove Item\n4. Back\nSelect an option: ";
        cin >> choice; cin.ignore();
        if (choice == 1) { inventory.show(); system("pause"); }
        else if (choice == 2) {
            string name; int qty;
            cout << "Item name: "; getline(cin, name);
            cout << "Quantity: "; cin >> qty; cin.ignore();
            inventory.addItem(name, qty);
            inventory.save();
        } else if (choice == 3) {
            string name; int qty;
            cout << "Item name: "; getline(cin, name);
            cout << "Quantity: "; cin >> qty; cin.ignore();
            if (!inventory.removeItem(name, qty)) cout << "Not enough stock!\n";
            inventory.save();
        }
    } while (choice != 4);
}