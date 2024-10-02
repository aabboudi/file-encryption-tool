#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "utils.h"

void showHelp() {
  std::cout << "Usage: .\\lock -e|-d -f|-r <path> -k <key>\n"
            << "Options:\n"
            << "  -e, --encrypt               Encrypt the file\n"
            << "  -d, --decrypt               Decrypt the file\n"
            << "  -f, --file <path>           Specify the file path\n"
            << "  -h, --help                  Show this help message and exit\n"
            << "  -k, --key <key>             Specify the encryption/decryption key\n"
            << "  -r, --recursive <path>      Specify the directory path\n"
            << "  -w, --overwrite             Specify whether to overwrite original file. Defaults to false.\n";
}

std::string generateRandomKey(size_t length) {
  std::string key;
  std::srand(static_cast<unsigned int>(std::time(0)));

  for (size_t i = 0; i < length; ++i) {
    // Generate chars from ASCII code 35 to 125
    key += static_cast<char>(std::rand() % (126 - 35 + 1) + 35);
  }

  return key;
}
