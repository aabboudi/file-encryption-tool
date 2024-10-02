#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdio>
#include "actions.h"

void encryptFile(const std::string &filePath, const std::string &key, bool overwrite) {
  std::ifstream file(filePath, std::ios::binary);

  // Ensure file is not changed mid-encryption
  if (!file.is_open()) {
    std::cerr << "Error opening file for encryption." << std::endl;
    return;
  }

  // Load file and encrypt data
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
    std::cout << "File successfully encrypted and saved to: " << filePath << std::endl;
  } else {
    std::cout << "File successfully encrypted. Copy saved to : " << tempFilePath << std::endl;
  }
}
