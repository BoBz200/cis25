#include <iostream>
#include <string>

#include "Item.h"
#include "Log.h"

Item::Item(int i, std::string n, double c) {
  id = i;
  name = n;
  cost = c;
  quantity = 0;
}
Item::Item(int i, std::string n, double c, int q) : Item(i, n, c) {
  quantity = q;
}

void Item::set_quantity(int new_quantity) {
  quantity = new_quantity;
  log_transaction(name + " quantity = " + std::to_string(quantity));
}
void Item::set_cost(double new_cost) {
  cost = new_cost;
  log_transaction(name + " cost = " + std::to_string(cost));
}

int Item::get_id() const {
  return id;
}
std::string Item::get_name() const {
  return name;
}
int Item::get_quantity() const {
  return quantity;
}
double Item::get_cost() const {
  return cost;
}

// return string for saving to csv
std::string Item::get_csv() const {
  return name + ", " + std::to_string(cost) + ", " + std::to_string(quantity);
}

void Item::display() const {
std::cout << get_name() << " : " << get_quantity() << " : $" << get_cost() << std::endl;
}
