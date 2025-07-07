#pragma once

#include <string>

class Item {
private:
    std::string name;
    int quantity;

public:
    Item();
    Item(std::string itemName, int itemQty);
    void display();
};
