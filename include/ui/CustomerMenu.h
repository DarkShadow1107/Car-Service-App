#ifndef CUSTOMER_MENU_H
#define CUSTOMER_MENU_H
#include <vector>
#include "../models/Customer.h"
#include "../models/Vehicle.h"
#include "../data/DataStorage.h"

class CustomerMenu {
private:
    std::vector<Customer>* customers;
    DataStorage* dataStorage;
public:
    CustomerMenu(std::vector<Customer>* customers, DataStorage* dataStorage);
    void display();
    void addVehicle(Customer& customer);
    void showCustomerDetails(const Customer& customer) const;
    void updateCustomerInfo(Customer& customer);
    void deleteCustomer(const std::string& phoneNumber);
    void listCustomers() const;
    void addCustomer();
    Customer* searchCustomerByPhone(const std::string& phone);
};

#endif // CUSTOMER_MENU_H