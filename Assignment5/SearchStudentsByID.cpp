#include <iostream>
#include <string>

// Define a struct to represent a student
struct Student {
  int id;
  std::string name;
  double gpa;
};

struct Item {
  std::string name;
  int id;
};

Item binary_search(int id, Item* ary, int ary_size) {
  int start = 0;
  int end = ary_size;
  while (id != ary[(start + end) / 2].id) {
    if (start == end)
      return {"ERROR", id};

    if (ary[(start + end) / 2].id < id)
      start = ((start + end) / 2) + 1;
    else
      end = (start + end) / 2;
  }
  return ary[(start + end) / 2];
}

int main() {
  // Declare an array of Student structs
  Student students[3]; // Initialize the elements of the array
  students[0] = {101, "Michael", 3.8};
  students[1] = {102, "Lakisha", 3.5};
  students[2] = {103, "Charlie", 3.9};

  // Access and print data from the array of structs
  for (int i = 0; i < 3; ++i) {
    std::cout << "Student ID: " << students[i].id << ", Name: "
              << students[i].name << ", GPA: " << students[i].gpa
              << std::endl;
  }

  int item_list_size = 5;
  Item* item_list = new Item[item_list_size];
  item_list[0] = {students[0].name, students[0].id};
  item_list[1] = {students[1].name, students[1].id};
  item_list[2] = {students[2].name, students[2].id};
  item_list[3] = {"Dan", 113};
  item_list[4] = {"Bob", 155};

  int input;
  std::cout << "Input ID: ";
  std::cin >> input;

  Item retreived_item = binary_search(input, item_list, item_list_size);
  std::cout << "Name: " << retreived_item.name
            << "\nID: " << retreived_item.id << std::endl;

  delete[] item_list;

  return 0;
}
