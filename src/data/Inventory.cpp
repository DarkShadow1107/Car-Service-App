#include "../../include/data/Inventory.h"
#include <fstream>
#include <iostream>

InventoryItem::InventoryItem(const std::string& name, int quantity) : name(name), quantity(quantity) {}
std::string InventoryItem::getName() const { return name; }
int InventoryItem::getQuantity() const { return quantity; }
void InventoryItem::setQuantity(int q) { quantity = q; }
void InventoryItem::add(int q) { quantity += q; }
void InventoryItem::remove(int q) { if (quantity >= q) quantity -= q; }

void Inventory::load(const std::string& filename) {
    items.clear();
    std::ifstream in(filename);
    if (!in.is_open()) {
        // Create the file if it doesn't exist
        std::ofstream createFile(filename);
        createFile.close();
        return;
    }
    std::string name; int qty;
    while (in >> std::ws && std::getline(in, name, ',')) {
        in >> qty;
        in.ignore(256, '\n');
        items.emplace_back(name, qty);
    }
    in.close();
}

void Inventory::save(const std::string& filename) {
    std::ofstream out(filename);
    for (const auto& item : items) {
        out << item.getName() << "," << item.getQuantity() << "\n";
    }
    out.close();
}

void Inventory::addItem(const std::string& name, int quantity) {
    InventoryItem* item = findItem(name);
    if (item) item->add(quantity);
    else items.emplace_back(name, quantity);
}

bool Inventory::removeItem(const std::string& name, int quantity) {
    InventoryItem* item = findItem(name);
    if (item && item->getQuantity() >= quantity) {
        item->remove(quantity);
        return true;
    }
    return false;
}

InventoryItem* Inventory::findItem(const std::string& name) {
    for (auto& item : items) {
        if (item.getName() == name) return &item;
    }
    return nullptr;
}

void Inventory::show() const {
    std::cout << "--- Inventory ---\n";
    for (const auto& item : items) {
        std::cout << item.getName() << ": " << item.getQuantity() << "\n";
    }
}

std::vector<InventoryItem>& Inventory::getItems() { return items; }
