#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdio>
#include "actions.h"

void xorFile(const std::string &mode, const std::string &filePath, const std::string &key, bool overwrite) {
  std::ifstream file(filePath, std::ios::binary);

  // Ensure file is not changed mid-action
  if (!file.is_open()) {
    std::cerr << "Error opening file for " << mode << "ion." << std::endl;
    return;
  }

  // Load file and scramble data
  std::vector<char> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
  size_t keyLength = key.size();

  for (size_t i = 0; i < buffer.size(); ++i) {
    buffer[i] ^= key[i % keyLength];
  }

  file.close();

  // Create and write to temp file
  std::string tempFilePath = filePath + ".tmp";
  std::ofstream tempFile(tempFilePath, std::ios::binary | std::ios::trunc);

  tempFile.write(buffer.data(), buffer.size());
  tempFile.close();

  /**Remove original file
   * remove() and rename() expect a C-style string
   * used .c_str() to convert it
   */
  if(overwrite) {
    std::remove(filePath.c_str());
    std::rename(tempFilePath.c_str(), filePath.c_str());
    std::cout << "File successfully " << mode << "ed and saved to: " << filePath << std::endl
              << "Secret key: " << key << std::endl
              << "Store it somewhere safe.";
  } else {
    std::cout << "File successfully " << mode << "ed. Copy saved to : " << tempFilePath << std::endl
              << "Secret key: " << key << std::endl
              << "Store it somewhere safe.";
  }
}
