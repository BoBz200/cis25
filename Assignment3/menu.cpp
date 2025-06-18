#include <iostream> 

int main() { 
    int choice; 
    std::cout << "1. Add Item\n2. View Items\n3. Exit\n"; 
    std::cout << "Choose an option: "; 
    std::cin >> choice; 

    if (choice == 1) {
        std::cout << "Item added!\n";
    }
    else if (choice == 2) {
        std::cout << "Displaying items...\n";
    }
    else if (choice == 3) {
        std::cout << "Exiting...\n";
    }
    else {
        std::cout << "Invalid option.\n";
    }
    return 0; 
}
