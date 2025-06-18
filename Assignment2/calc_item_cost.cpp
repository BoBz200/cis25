#include <iostream>
#include <string>

int main() {
    std::string itemName;
    int quantity;
    float cost;

    std::cout << "Enter item name: "; 
    std::cin >> itemName; 
	std::cout << "Enter quantity: "; 
	std::cin >> quantity; 
	std::cout << "Enter cost: "; 
	std::cin >> cost; 

    std::cout << "Total cost for " << itemName << ": $" << (quantity * cost) << std::endl;
	return 0; 
}
