#include <iostream>
#include <string>

class Item {
public:
  std::string name;
  int quantity;

  void display() {
    std::cout << "Item: " << name << ", Quantity: " << quantity << std::endl;
  }
};

void searchItem(Item inventory[], int size, std::string searchName) {
  bool found = false;
  for (int i = 0; i < size; i++) {
    if (inventory[i].name == searchName) {
      std::cout << "Found: " << inventory[i].name << " - Quantity: " << inventory[i].quantity << std::endl;
      found = true;
      break;
    }
  }
  if (!found) {
    std::cout << "Item not found in inventory." << std::endl;
  }
}

int main() {
  const int SIZE = 5;
  Item inventory[SIZE];

  // Input items
  for (int i = 0; i < SIZE; i++) {
    std::cout << "Enter name for item " << (i + 1) << ": ";
    std::cin >> inventory[i].name;
    std::cout << "Enter quantity for " << inventory[i].name << ": ";
    std::cin >> inventory[i].quantity;
  }

  // Display items
  std::cout << "\nInventory List:\n";
  for (int i = 0; i < SIZE; i++) {
    inventory[i].display();
  }

  // Search for an item
  std::string searchName;
  std::cout << "\nEnter item name to search: ";
  std::cin >> searchName;
  searchItem(inventory, SIZE, searchName);

  return 0;
}
