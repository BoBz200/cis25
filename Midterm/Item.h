#pragma once

#include <string>

// Base class
class Item {
private:
  int id;
  std::string name;
  int quantity;
  double cost;

public:
  Item(int i, std::string n, double c);
  Item(int i, std::string n, double c, int q);

  // setters
  void set_quantity(int new_quantity);
  void set_cost(double new_cost);

  // getters
  int get_id() const;
  std::string get_name() const;
  int get_quantity() const;
  double get_cost() const;

  std::string get_csv() const;

  virtual void display() const;
};
