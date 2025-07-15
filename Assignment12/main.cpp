#include <iostream>
#include <ostream>

#include "csv_reader.h"

int main() {
  ReadCSV csv = ReadCSV("dinoDatasetCSV.csv");
  csv.load_file();

  int i = 1;
  std::string input;
  do {
    //Print 10 dinos
    for (int j = 0; j < 10; j++) {
      std::cout << "Scientific name: " << csv.data[i][0] << std::endl;
      std::cout << "    meaning: " << csv.data[i][2] << std::endl;
      std::cout << "    diet: " << csv.data[i][3] << std::endl;
      std::cout << "    length(m)/height(m)/weight(kg): " << csv.data[i][4]
                << "m/" << csv.data[i][6] << "m/" << csv.data[i][5] << "kg" << std::endl;
      std::cout << "    locomotion: " << csv.data[i][7] << std::endl;

      i++;
    }

    //prompt user if they want to see more
    std::cout << std::endl;
    std::cout << "Type 'Next' to see more (or Quit): ";
    std::cin >> input;
  } while (input != "Quit" && i < csv.data.size());
}
