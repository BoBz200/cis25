#include <iostream>
#include <string>

#include "Inventory.h"

void deposite_money(Inventory& inventory);
void buy_item(Inventory& inventory);
void sell_item(Inventory& inventory);
void view_inventory(Inventory& inventory);
void change_item_cost(Inventory& inventory);

int main() {
  Inventory inventory = Inventory();
  std::cout << "Welcome to your inventory managment system.\n" << std::endl;

  bool loop = true;
  while (loop) {
    int input;
    // Prompt User what they want to do with inventory
    std::cout << "Select the number corresponding to the option you want.\n";
    std::cout << "1. Deposite money\n2. Buy an item\n3. Sell an item\n";
    std::cout << "4. View inventory\n5. Change item cost\n6. Quit" << std::endl;
    std::cin >> input;

    switch (input) {
      case 1:
        deposite_money(inventory);
        break;
      case 2:
        buy_item(inventory);
        break;
      case 3:
        sell_item(inventory);
        break;
      case 4:
        view_inventory(inventory);
        break;
      case 5:
        change_item_cost(inventory);
        break;
      case 6:
        loop = false;
        break;
      default:
        std::cout << "That was not a valid input." << std::endl;
        break;
    }

    // clear buffer incase invald input
    std::cin.clear();
    std::cin.ignore();

    std::cout << std::endl;
  }
}


void deposite_money(Inventory& inventory) {
  // Prompt user how much money they want to deposite
  double amount = 0;
  std::cout << "You currently have $" << inventory.get_balance() << std::endl;
  std::cout << "How much money do you want to deposite: ";
  std::cin >> amount;

  // Exit if input was invalid
  if (amount <= 0) {
    std::cout << amount << " is not a valid amount." << std::endl;
    return;
  }

  // Deposite amount
  inventory.deposit(amount);
  std::cout << "Your current balance is now $" << inventory.get_balance() << std::endl;
}


void buy_item(Inventory& inventory) {
  // Prompt user what item they want to buy
  std::string item_name;
  std::cout << "What is the name of the item you would like to buy: ";
  std::cin >> item_name;

  // Prompt user how much they want to buy
  int item_quantity;
  std::cout << "How many " << item_name << "s do you want to buy: ";
  std::cin >> item_quantity;

  // Exit if invalid input
  if (item_quantity <= 0)
    return;

  // Prompt user what the cost is for one item
  double item_cost;
  std::cout << "How much does one " << item_name << " cost: ";
  std::cin >> item_cost;

  // Exit if invalid input
  if (item_cost <= 0)
    return;

  // Exit if cant afford
  if (item_cost * item_quantity > inventory.get_balance()) {
    std::cout << "Cant afford $" << (item_cost * item_quantity) << "." << std::endl;
    return;
  }

  // Prompt user for confermation
  bool is_plural = item_quantity > 1;
  if (is_plural)
    std::cout << item_quantity << " " << item_name << "s will cost $" << (item_cost * item_quantity) << ".\n";
  else
    std::cout << item_quantity << " " << item_name << " will cost $" << item_cost << ".\n";
  std::cout << "This will leave your balance at $" << inventory.get_balance() - (item_cost * item_quantity) << "." << std::endl;
  std::cout << "Are you sure you want to buy this (y/n): ";

  std::string confirm_purchase;
  std::cin >> confirm_purchase;
  if (confirm_purchase != "y")
    return;

  // Purchase item
  if (item_quantity == 1)
    inventory.purchase_item(item_name, item_cost);
  else
    inventory.purchase_items(item_name, item_cost, item_quantity);
}


void sell_item(Inventory& inventory) {
  // Prompt user what item they want to sell
  std::string item_name;
  std::cout << "What is the name of the item you would like to sell: ";
  std::cin >> item_name;

  // Exit if it is not in Inventory
  if (!inventory.is_item_inside(item_name)) {
    std::cout << item_name << " does not exist in inventory." << std::endl;
    return;
  }

  // Prompt user how much they want to sell
  int item_quantity;
  std::cout << "How many " << item_name << "s do you want to sell: ";
  std::cin >> item_quantity;

  // Exit if invalid input or not enough items in inventory
  if (item_quantity <= 0 || item_quantity > inventory.get_item_quantity(item_name))
    return;

  // Prompt user how much one item costs
  double item_cost;
  std::cout << "How much does one " << item_name << " cost (Enter 0 if you want to use item's normal price): ";
  std::cin >> item_cost;

  // Exit if invalid input
  if (item_cost < 0)
    return;

  if (item_cost == 0)
    item_cost = inventory.get_item_cost(item_name);

  //Prompt user for confirmation of exchange
  bool is_plural = item_quantity > 1;
  if (is_plural)
    std::cout << item_quantity << " " << item_name << "s will cost $" << (item_cost * item_quantity) << ".\n";
  else
    std::cout << item_quantity << " " << item_name << " will cost $" << item_cost << ".\n";
  std::cout << "This will make your balance at $" << inventory.get_balance() + (item_cost * item_quantity) << "." << std::endl;
  std::cout << "Are you sure you want to sell this (y/n): ";

  std::string confirm_purchase;
  std::cin >> confirm_purchase;
  if (confirm_purchase != "y")
    return;

  // Sell item
  if (item_quantity == 1)
    inventory.sell_item(item_name, item_cost);
  else
    inventory.sell_items(item_name, item_cost, item_quantity);
}


void view_inventory(Inventory& inventory) {
  // Prompt user how they want view inventory
  std::cout << "Would you like to view your whole inventory or one item.\n";
  std::cout << "1. Whole inventory\n2. One Item\n3. Neither" << std::endl;

  int option;
  std::cin >> option;

  // Exit if invalid input
  if (option != 1 && option != 2)
    return;

  // Display whole tree
  if (option == 1) {
    inventory.display();
    return;
  }

  // Prompt user what item they want to view
  std::string item_name;
  std::cout << "What is the name of the item you would like to view: ";
  std::cin >> item_name;

  // Exit if it is not in inventory
  if (!inventory.is_item_inside(item_name)) {
    std::cout << item_name << " does not exist in inventory." << std::endl;
    return;
  }

  // Display item
  inventory.display_item(item_name);
}


void change_item_cost(Inventory& inventory) {
  // Prompt user what item they to change price
  std::string item_name;
  std::cout << "What is the name of the item you would like to change: ";
  std::cin >> item_name;

  // Exit if item does not exists in inventory
  if (!inventory.is_item_inside(item_name)) {
    std::cout << item_name << " does not exist in inventory." << std::endl;
    return;
  }

  // Prompt user what the new price is
  double old_item_cost = inventory.get_item_cost(item_name);
  std::cout << item_name << " currenty costs " << old_item_cost << "." << std::endl;
  double new_item_cost;
  std::cout << "What do you want to change " << item_name << "'s cost to: ";
  std::cin >> new_item_cost;

// Exit if invalid input
  if (new_item_cost <= 0)
    return;

  // Change price
  inventory.set_item_cost(item_name, new_item_cost);
}
