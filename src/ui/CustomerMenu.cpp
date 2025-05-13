#include "../../include/ui/CustomerMenu.h"
#include "../../include/Utilities.h"
#include <iostream>
#include <windows.h>
#include <algorithm>

using namespace std;

CustomerMenu::CustomerMenu(vector<Customer>* c, DataStorage* ds) : customers(c), dataStorage(ds) {}

void CustomerMenu::display() {
    int choice = 0;
    do {
        system("cls");
        Utilities::setConsoleColor(Utilities::THEME_PURPLE); // Heading
        cout << "===== Customer Menu =====\n";
        Utilities::setConsoleColor(Utilities::THEME_CREAM);
        cout << "1. Add Customer\n";
        cout << "2. Search Customer by Phone\n";
        Utilities::setConsoleColor(Utilities::THEME_SALMON);
        cout << "3. Update Customer Info\n";
        Utilities::setConsoleColor(Utilities::THEME_DARK_RED);
        cout << "4. Delete Customer\n";
        Utilities::setConsoleColor(Utilities::THEME_TEAL);
        cout << "5. List Customers\n";
        Utilities::setConsoleColor(Utilities::THEME_LT_GREEN);
        cout << "6. Add Vehicle to Customer\n";
        Utilities::setConsoleColor(Utilities::THEME_PURPLE);
        cout << "7. Show Customer Details\n";
        Utilities::setConsoleColor(Utilities::THEME_CREAM);
        cout << "8. Back\n";
        Utilities::setConsoleColor(Utilities::THEME_TEAL);
        cout << "Select an option: ";
        Utilities::setConsoleColor(Utilities::THEME_CREAM);
        cin >> choice;
        cin.ignore();
        switch (choice) {
            case 1: addCustomer(); break;
            case 2: {
                string phone = Utilities::getStringInput("Enter phone number: ");
                Customer* c = searchCustomerByPhone(phone);
                if (c) showCustomerDetails(*c);
                else {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); // Red for error
                    cout << "Customer not found!\n";
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                }
                system("pause");
                break;
            }
            case 3: {
                string phone = Utilities::getStringInput("Enter phone number: ");
                Customer* c = searchCustomerByPhone(phone);
                if (c) updateCustomerInfo(*c);
                else {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                    cout << "Customer not found!\n";
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                }
                system("pause");
                break;
            }
            case 4: {
                string phone = Utilities::getStringInput("Enter phone number: ");
                deleteCustomer(phone);
                break;
            }
            case 5: listCustomers(); break;
            case 6: {
                string phone = Utilities::getStringInput("Enter phone number: ");
                Customer* c = searchCustomerByPhone(phone);
                if (c) addVehicle(*c);
                else {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                    cout << "Customer not found!\n";
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                }
                system("pause");
                break;
            }
            case 7: {
                string phone = Utilities::getStringInput("Enter phone number: ");
                Customer* c = searchCustomerByPhone(phone);
                if (c) showCustomerDetails(*c);
                else {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                    cout << "Customer not found!\n";
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                }
                system("pause");
                break;
            }
            case 8: return;
            default:
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                cout << "Invalid option!\n";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                system("pause");
                break;
        }
    } while (choice != 8);
}

void CustomerMenu::addCustomer() {
    string first = Utilities::getStringInput("First name: ");
    string last = Utilities::getStringInput("Last name: ");
    string phone = Utilities::getStringInput("Phone number: ");
    if (!Utilities::isValidPhoneNumber(phone)) {
        cout << "Invalid phone number!\n";
        system("pause");
        return;
    }
    customers->push_back(Customer(first, last, phone));
    dataStorage->saveAll(*customers);
    cout << "Customer added!\n";
    system("pause");
}

Customer* CustomerMenu::searchCustomerByPhone(const string& phone) {
    for (auto& c : *customers) {
        if (c.getPhoneNumber() == phone) return &c;
    }
    return nullptr;
}

void CustomerMenu::addVehicle(Customer& customer) {
    string maker = Utilities::getStringInput("Maker: ");
    string model = Utilities::getStringInput("Model: ");
    int year = Utilities::getIntInput("Year: ");
    string plate = Utilities::getStringInput("License Plate: ");
    string fuel = Utilities::getStringInput("Fuel Type: ");
    customer.addVehicle(Vehicle(maker, model, year, plate, fuel));
    dataStorage->saveAll(*customers);
    cout << "Vehicle added!\n";
    system("pause");
}

void CustomerMenu::showCustomerDetails(const Customer& customer) const {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11); // Cyan for customer heading
    cout << "--- Customer Details ---\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); // Green for name
    cout << "Name: " << customer.getFirstName() << " " << customer.getLastName() << "\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); // Yellow for phone
    cout << "Phone: " << customer.getPhoneNumber() << "\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13); // Magenta for vehicles
    if (customer.getVehicles().empty()) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); // Red for no vehicles
        cout << "No vehicles registered.\n";
    } else {
        cout << "Vehicles:\n";
        int idx = 1;
        for (const auto& v : customer.getVehicles()) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9 + (idx % 6)); // Cycle through blue, green, aqua, red, purple, yellow
            cout << idx << ". ";
            v.showDetails();
            ++idx;
        }
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // Reset to white
    system("pause");
}

void CustomerMenu::updateCustomerInfo(Customer& customer) {
    string first = Utilities::getStringInput("New first name: ");
    string last = Utilities::getStringInput("New last name: ");
    string phone = Utilities::getStringInput("New phone number: ");
    if (!Utilities::isValidPhoneNumber(phone)) {
        cout << "Invalid phone number!\n";
        system("pause");
        return;
    }
    customer.updateInfo(first, last, phone);
    dataStorage->saveAll(*customers);
    cout << "Customer updated!\n";
    system("pause");
}

void CustomerMenu::deleteCustomer(const string& phoneNumber) {
    auto it = remove_if(customers->begin(), customers->end(), [&](const Customer& c) {
        return c.getPhoneNumber() == phoneNumber;
    });
    if (it != customers->end()) {
        customers->erase(it, customers->end());
        dataStorage->saveAll(*customers);
        cout << "Customer deleted!\n";
    } else {
        cout << "Customer not found!\n";
    }
    system("pause");
}

void CustomerMenu::listCustomers() const {
    int colors[] = {9, 10, 11, 12, 13, 14};
    if (customers->empty()) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        cout << "No customers found.\n";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    } else {
        int idx = 0;
        for (const auto& c : *customers) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colors[idx % 6]);
            cout << "Customer: " << c.getFirstName() << " " << c.getLastName() << ", " << c.getPhoneNumber() << "\n";
            int vdx = 0;
            for (const auto& v : c.getVehicles()) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colors[(idx + vdx + 1) % 6]);
                cout << "  Vehicle: ";
                v.showDetails();
                ++vdx;
            }
            ++idx;
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    }
    system("pause");
}