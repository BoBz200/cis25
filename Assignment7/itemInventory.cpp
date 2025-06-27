#include <iostream>
#include <string>

// Base class
class Item {
public:
  std::string name;
  int quantity;

  Item(std::string n, int q) {
    name = n;
    quantity = q;
  }

  virtual void display() = 0; // Pure virtual function
};

// Perishable item
class Perishable : public Item {
public:
    Perishable(std::string n, int q) : Item(n, q) {}

    void display() override {
    std::cout << name << " (Perishable), Qty: " << quantity << std::endl;
    }
};

// Non-Perishable item
class NonPerishable : public Item {
public:
    NonPerishable(std::string n, int q) : Item(n, q) {}

    void display() override {
    std::cout << name << " (Non-Perishable), Qty: " << quantity << std::endl;
    }
};

int main() {
    // Create inventory using base class pointers
    Item* item1 = new Perishable("Milk", 10);
    Item* item2 = new NonPerishable("Cereal", 20);

    item1->display();
    item2->display();

    // Clean up
    delete item1;
    delete item2;

    return 0;
}
