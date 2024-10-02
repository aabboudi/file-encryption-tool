#include <iostream>
#include <string>
#include "utils.h"
#include "actions.h"

int main(int argc, char *argv[]) {
  if (argc < 4) {
    showHelp();
    return 1;
  }

  std::string mode;
  std::string filePath;
  std::string key;
  bool overwrite = false;

  // Parse arguments
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
        std::cerr << "Error: Missing target file path" << std::endl;
        return 1;
      }
    } else if (arg == "-k" || arg == "--key") {
      if (i + 1 < argc) {
        key = argv[++i];
      } else {
        std::cerr << "Error: Missing encryption key. If you want the program to generate one, do not use the --key flag." << std::endl;
        return 1;
      }
    } else if (arg == "-w" || arg == "--overwrite") {
      overwrite = true;
    } else if (arg == "-h" || arg == "--help") {
      showHelp();
      return 0;
    } else {
      std::cerr << "Error: Unknown option " << arg << std::endl;
      showHelp();
      return 1;
    }
  }

  // Validate arguments
  if (mode.empty()) {
    std::cerr << "Error: No mode specified. Use --encrypt or --decrypt to set the mode." << std::endl;
    return 1;
  }

  if (filePath.empty()) {
    std::cerr << "Error: No target file specified. Use --file followed by the path to the target file." << std::endl;
    return 1;
  }

  if (mode == "decrypt" && key.empty()) {
    std::cerr << "Error: No key specified. The key is required to decrypt the file." << std::endl;
    return 1;
  }

  key = key.empty() ? generateRandomKey(10) : key;

  xorFile(mode, filePath, key, overwrite);

  return 0;
}
