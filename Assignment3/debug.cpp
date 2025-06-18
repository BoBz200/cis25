#include <iostream>

using namespace std;

int main() {
    float n1, n2, n3;

    std::cout << "Enter three numbers: ";
    std::cin >> n1 >> n2 >> n3;

    if(n1 >= n2 && n1 >= n3) {
        cout << "Largest number: " << n1 << std::endl;
    }
    else if(n2 >= n1 && n2 >= n3) {
        cout << "Largest number: " << n2 << std::endl;
    }
    else if(n3 >= n1 && n3 >= n2) {
        cout << "Largest number: " << n3 << std::endl;
    }
    return 0;
}
