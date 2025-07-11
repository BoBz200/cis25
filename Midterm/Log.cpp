#include <string>

#include <fstream>
#include "Log.h"

// Logs message to the file transactionLog.txt
void log_transaction(std::string message) {
  std::ofstream file("transactionLog.txt", std::ios::app);
  if (file.is_open()) {
    file << message << std::endl;
    file.close();
  }
}
