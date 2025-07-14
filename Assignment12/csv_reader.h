#pragma once

#include <string>
#include <vector>

class ReadCSV {
public:
  std::vector<std::vector<std::string>> data;
  std::string file_name;

  ReadCSV(std::string file_name);

  void load_file();

private:
  std::vector<std::string> tokenize_line(std::string line);
};
