#include <iostream>
#include <fstream>
#include <string>

#include "Inventory.h"
#include "Item.h"
#include "Log.h"

Inventory::Inventory() {
  // Initialize members
  balance = 0.0;
  storage_size = 0;
  storage = new Item*[storage_size];

  // load from file
  load_transactions();
}

Inventory::~Inventory() {
  // save to file
  save_transactions();

  // free memory
  for (int i = 0; i < storage_size; i++) {
    delete storage[i];
  }
}

double Inventory::get_balance() const {
  return balance;
}
double Inventory::get_item_cost(std::string name) const {
  return get_item(name)->get_cost();
}
int Inventory::get_item_quantity(std::string name) const {
  return get_item(name)->get_quantity();
}

// checks if item is inside storage
bool Inventory::is_item_inside(std::string item) const {
  Item* received_item = get_item(item);
  if (received_item->get_name() == "None") {
    delete received_item;
    return false;
  }
  return true;
}

// deposite money
void Inventory::deposit(double amount) {
  log_transaction("deposite - $" + std::to_string(amount));
  set_balance(get_balance() + amount);
}

// private: for setting balance and logging
void Inventory::set_balance(double new_balance) {
  balance = new_balance;
  log_transaction("balance = $" + std::to_string(balance));
}

// change item price
void Inventory::set_item_cost(std::string item, double new_cost) {
  // Exit if item is not in storage
  if (!is_item_inside(item))
    return;

  // Change item price
  Item* received_item = get_item(item);
  received_item->set_cost(new_cost);
  log_transaction("changed price - " + item + " = $" + std::to_string(new_cost));
}

// Purchace one item
void Inventory::purchase_item(std::string item, double item_cost) {
  // Exit if cant afford
  if (item_cost > balance)
    return;

  // make sure item exists else create it
  Item* purchasable_item = get_item(item);
  if (purchasable_item->get_name() == "None") {
    delete purchasable_item;
    purchasable_item = insert_item_in_storage(item, item_cost);
  }

  // Purchase item
  log_transaction("purchased - " + item + " for $" + std::to_string(item_cost));
  set_balance(get_balance() - item_cost);
  purchasable_item->set_quantity(purchasable_item->get_quantity() + 1);
}

// purchase multiple items
void Inventory::purchase_items(std::string item, double item_cost, int amount) {
  // Exit if cant afford
  if (item_cost * amount > balance)
    return;

  // make sure item exists else create it
  Item* purchasable_item = get_item(item);
  if (purchasable_item->get_name() == "None") {
    delete purchasable_item;
    purchasable_item = insert_item_in_storage(item, item_cost);
  }

  // Purchase items
  log_transaction("purchased - "+ std::to_string(amount) + " " + item + " for $" + std::to_string(item_cost * amount));
  set_balance(get_balance() - item_cost * amount);
  purchasable_item->set_quantity(purchasable_item->get_quantity() + amount);
}

// sell single item
void Inventory::sell_item(std::string item, double cost) {
  // Exit if item exists or can have enough items to sell
  Item* purchasable_item = get_item(item);
  if (purchasable_item->get_name() == "None") {
    delete purchasable_item;
    return;
  }
  if (purchasable_item->get_quantity() < 1)
    return;

  // sell item
  log_transaction("sold - " + item + " for $" + std::to_string(cost));
  set_balance(get_balance() + cost);
  purchasable_item->set_quantity(purchasable_item->get_quantity() - 1);
}

// see multiple items
void Inventory::sell_items(std::string item, double cost, int amount) {
  // Exit if item exists or can have enough items to sell
  Item* purchasable_item = get_item(item);
  if (purchasable_item->get_name() == "None") {
    delete purchasable_item;
    return;
  }
  if (purchasable_item->get_quantity() < amount)
    return;

  // sell items
  log_transaction("sold - " + std::to_string(amount) + " " + item + " for $" + std::to_string(cost * amount));
  set_balance(get_balance() + cost * amount);
  purchasable_item->set_quantity(purchasable_item->get_quantity() - amount);
}

// load inventory from file
void Inventory::load_transactions() {
  std::ifstream file("Inventory.txt");
  // exit if cant open file
  if (!file.is_open()) {
    std::cout << "Failed to open Inventory.txt to load" << std::endl;
    return;
  }

  // load balance from first line
  std::string line;
  getline(file, line);
  balance = std::stod(line);

  // load storage in a csv format
  while (getline(file, line)) {
    std::string item_name = line.substr(0, line.find(", "));
    line = line.substr(line.find(", ") + 2, line.length());
    double item_cost = std::stod(line.substr(0, line.find(", ")));
    line = line.substr(line.find(", ") + 2, line.length());
    int item_quantity = std::stoi(line.substr(0, line.find(", ")));

    insert_item_in_storage(item_name, item_cost, item_quantity);
  }
  file.close();
}


// save to file as csv
void Inventory::save_transactions() {
  std::ofstream file("Inventory.txt");
  // exit if cant open file
  if (!file.is_open()) {
    std::cout << "Failed to open Inventory.txt to save" << std::endl;
    return;
  }

  // save balance on first line
  file << balance << std::endl;
  // save storage
  for (int i = 0; i < storage_size; i++) {
    file << storage[i]->get_csv() << std::endl;
  }
  file.close();
}

void Inventory::display() const{
  std::cout << "Inventory:" << std::endl;
  for (int i = 0; i < storage_size; i++) {
    storage[i]->display();
  }
}
void Inventory::display_item(std::string name) const {
  if (!is_item_inside(name))
    return;

  Item* item = get_item(name);
  item->display();
}

//---------------
//private members
//---------------

// insert item with an id into a dynamically sized array
Item* Inventory::insert_item_in_storage(std::string name, double cost) {
  // resize array
  storage_size++;
  Item** new_storage = new Item*[storage_size];
  for (int i = 0; i < storage_size - 1; i++) {
    new_storage[i] = storage[i];
  }
  delete[] storage;
  storage = new_storage;

  // append new Item
  storage[storage_size - 1] = new Item(storage_size - 1, name, cost);
  return storage[storage_size - 1];
}
Item* Inventory::insert_item_in_storage(std::string name, double cost, int quantity) {
  // resize array
  storage_size++;
  Item** new_storage = new Item*[storage_size];
  for (int i = 0; i < storage_size - 1; i++) {
    new_storage[i] = storage[i];
  }
  delete[] storage;
  storage = new_storage;

  // append new Item
  storage[storage_size - 1] = new Item(storage_size - 1, name, cost, quantity);
  return storage[storage_size - 1];
}

// linear search for item by name
Item* Inventory::get_item(std::string item) const {
  for (int i = 0; i < storage_size; i++) {
    if (item == storage[i]->get_name())
      return storage[i];
  }
  return new Item(-1, "None", -1, -1);
}
// binary search for item by id
Item* Inventory::get_item_by_id(int id) const {
  int start = 0;
  int end = storage_size;
  while (id != storage[(start + end) / 2]->get_id()) {
    if (start == end)
      return new Item(-1, "None", -1, -1);

    if (storage[(start + end) / 2]->get_id() < id)
      start = ((start + end) / 2) + 1;
    else
      end = (start + end) / 2;
  }
  return storage[(start + end) / 2];
}
