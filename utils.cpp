#include <iostream>
#include "utils.h"

void showHelp() {
  std::cout << "Usage: .\\lock.exe -e|-d -f <file_path> -k [key]\n"
            << "Options:\n"
            << "  -e, --encrypt             Encrypt the file\n"
            << "  -d, --decrypt             Decrypt the file\n"
            << "  --file <file>             Specify the file path\n"
            << "  --key [key]               Specify the encryption/decryption key\n"
            << "  -h, --help                Show this help message and exit\n";
}
