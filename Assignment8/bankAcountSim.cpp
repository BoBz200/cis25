#include <fstream>
#include <iostream>
#include <string>

class BankAccount {
private:
  double balance;

public:
  BankAccount() {
    balance = 0.0;
  }

  void deposit(double amount) {
    balance += amount;
    saveTransaction("Deposit", amount);
  }

  void makePurchase(std::string item, double cost) {
    if (cost > balance) {
      std::cout << "Insufficient funds for " << item << std::endl;
    }
    else {
      balance -= cost;
      saveTransaction("Purchase - " + item, cost);
    }
  }

  void displayBalance() {
    std::cout << "Current Balance: $" << balance << std::endl;
  }

  void saveTransaction(std::string type, double amount) {
    std::ofstream file("transactions.txt", std::ios::app);
    if (file.is_open()) {
      file << type << ": $" << amount << std::endl;
      file.close();
    }
  }
};

int main() {
  BankAccount myAccount;

  myAccount.deposit(100.00);
  myAccount.makePurchase("Coffee", 4.50);
  myAccount.makePurchase("Book", 25.00);
  myAccount.displayBalance();

  return 0;
}
