#include <iostream>

void showMenu() {
    std::cout << "1. Add\n2. View\n3. Exit\n";
}

int main() {
    int option;
    do {
        showMenu();
        std::cin >> option;
    }
    while (option != 3);

    return 0; 
}
