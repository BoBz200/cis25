#pragma once

#include <string>

#include "Item.h"

class Inventory {
private:
  double balance;
  Item** storage;
  int storage_size;

public:
  Inventory();

  ~Inventory();

  // getters
  double get_balance() const;
  double get_item_cost(std::string item) const;
  int get_item_quantity(std::string item) const;

  bool is_item_inside(std::string item) const;

  // setters
  void deposit(double amount);
  void set_item_cost(std::string item, double new_cost);

  // purchase or sell
  void purchase_item(std::string item, double item_cost);
  void purchase_items(std::string item, double item_cost, int amount);
  void sell_item(std::string item, double cost);
  void sell_items(std::string item, double cost, int amount);

  // file i/o
  void load_transactions();
  void save_transactions();

  //display inventory and contents
  void display() const;
  void display_item(std::string name) const;

private:
  //insert new items in storage
  Item* insert_item_in_storage(std::string name, double cost);
  Item* insert_item_in_storage(std::string name, double cost, int quantity);

  // get Items
  Item* get_item(std::string item) const;
  Item* get_item_by_id(int id) const;

  // set balance
  void set_balance(double new_balance);
};
