#include <iostream>
#include <string>
#include "utils.h"

int main(int argc, char *argv[]) {
  if (argc < 4) {
    showHelp();
    return 1;
  }

  std::string mode;
  std::string filePath;
  std::string key;

  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    
    if (arg == "-e" || arg == "--encrypt") {
      mode = "encrypt";
    } else if (arg == "-d" || arg == "--decrypt") {
      mode = "decrypt";
    } else if (arg == "-f" || arg == "--file") {
      if (i + 1 < argc) {
        filePath = argv[++i];
      } else {
        std::cerr << "Error: Missing file path after -f/--file\n";
        return 1;
      }
    } else if (arg == "-k" || arg == "--key") {
      if (i + 1 < argc) {
        key = argv[++i];
      }
    } else if (arg == "-h" || arg == "--help") {
      showHelp();
      return 0;
    } else {
      std::cerr << "Error: Unknown option " << arg << "\n";
      showHelp();
      return 1;
    }
  }

  std::cout << "Mode: " << (mode.empty() ? "None" : mode) << "\n"
            << "Path: " << (filePath.empty() ? "None" : filePath) << "\n"
            << "Key: " << (key.empty() ? "None" : key) << "\n";

  return 0;
}
