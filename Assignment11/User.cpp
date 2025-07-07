#include <iostream>
#include "User.h"

void User::accessLevel() {
    std::cout << "General Access\n";
}

// Derived from User
void Employee::accessLevel() {
    std::cout << "Employee Access\n";
}

// Derived from Employee
void InventoryManager::accessLevel() {
    std::cout << "Full Inventory Management Access\n";
}
