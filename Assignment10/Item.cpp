#include <iostream>
#include "Item.h"

Item::Item() {
    name = "Unknown";
    quantity = 0;
}

Item::Item(std::string itemName, int itemQty) {
    name = itemName;
    quantity = itemQty;
}

void Item::display() {
    std::cout << "Item: " << name << ", Quantity: " << quantity << std::endl;
}
