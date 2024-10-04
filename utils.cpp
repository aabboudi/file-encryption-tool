#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <filesystem>
#include "utils.h"

void showHelp() {
  std::cout << "\nUsage:\n"
            << "Encryption: .\\lock -e -f|-r <path> [-w] [-k <key>]\n"
            << "Decryption: .\\lock -d -f|-r <path> [-w] -k <key>\n"
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

bool confirmOverwrite() {
  std::string response;
  std::cout << "Instructed to overwrite original file." << std::endl
            << "Are you sure you want to proceed? [Y/N]: ";
  std::cin >> response;

  if (response == "y" || response == "Y") {
    return true;
  }
  return false;
}

void preventSelfDestruction(const std::string &execPath, const std::string &targetPath) {
  try {
    auto execPathAbsolute = std::filesystem::absolute(execPath);
    auto targetPathAbsolute = std::filesystem::absolute(targetPath);

    // Check if target is the executable
    if (execPathAbsolute == targetPathAbsolute) {
      std::cerr << "Error: Attempting to target the executable at " << execPathAbsolute << std::endl
                << "This operation is blocked to prevent self destruction." << std::endl;
      exit(EXIT_FAILURE);
    }

    // Check if target contains the executable
    for (const auto &file : std::filesystem::recursive_directory_iterator(targetPathAbsolute)) {
      if (std::filesystem::absolute(file.path()) == execPathAbsolute) {
        std::cerr << "Error: Attempting to target a directory containing the executable at " << execPathAbsolute << std::endl
                  << "This operation is blocked to prevent self destruction." << std::endl;
        exit(EXIT_FAILURE);
      }
    }
  } catch (const std::filesystem::filesystem_error &error) {
    std::cerr << "Filesystem error: " << error.what() << std::endl;
    exit(EXIT_FAILURE);
  }
}
