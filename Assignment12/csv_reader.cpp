#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "csv_reader.h"

ReadCSV::ReadCSV(std::string file_name) {
  this->file_name = file_name;

  data = std::vector<std::vector<std::string>>();
}

void ReadCSV::load_file() {
  std::ifstream file = std::ifstream(file_name);
  //Exit if cant open file
  if (!file.is_open()) {
    std::cout << "Failed to open " + file_name + "." << std::endl;
    return;
  }

  //read all lines and tokenize
  std::string line;
  while (getline(file, line)) {
    data.push_back(tokenize_line(line));
  }

  file.close();
}

//convert line into an vector of tokens
std::vector<std::string> ReadCSV::tokenize_line(std::string line) {
  std::vector<std::string> tokens = std::vector<std::string>();

  // while a section exists create a token of it and add to vector
  while (line.find(",") != std::string::npos) {
    std::string token = line.substr(0, line.find(","));
    line = line.substr(line.find(",") + 1, line.length() - 1);
    tokens.push_back(token);
  }

  return tokens;
}
