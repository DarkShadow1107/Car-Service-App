#pragma once
#include <string>
#include <vector>

class InventoryItem {
public:
    InventoryItem(const std::string& name, int quantity);
    std::string getName() const;
    int getQuantity() const;
    void setQuantity(int q);
    void add(int q);
    void remove(int q);
private:
    std::string name;
    int quantity;
};

class Inventory {
public:
    void load(const std::string& filename = "c:/Users/Alexandru Gabriel/Desktop/Clinical Death/ISP/Project/V5/inventory.txt");
    void save(const std::string& filename = "c:/Users/Alexandru Gabriel/Desktop/Clinical Death/ISP/Project/V5/inventory.txt");
    void addItem(const std::string& name, int quantity);
    bool removeItem(const std::string& name, int quantity);
    InventoryItem* findItem(const std::string& name);
    void show() const;
    std::vector<InventoryItem>& getItems();
private:
    std::vector<InventoryItem> items;
};
