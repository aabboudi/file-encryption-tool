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
  std::string path;
  std::string key;
  bool overwrite = false;
  bool target = false;

  // Parse arguments
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];

    if (arg == "-e" || arg == "--encrypt") {
      mode = "encrypt";
    } else if (arg == "-d" || arg == "--decrypt") {
      mode = "decrypt";
    } else if (arg == "-f" || arg == "--file") {
      if (i + 1 < argc) {
        path = argv[++i];
      } else {
        std::cerr << "Error: Missing target file path" << std::endl;
        return 1;
      }
    } else if (arg == "-r" || arg == "--recursive") {
      if (i + 1 < argc) {
        path = argv[++i];
        target = true;
      } else {
        std::cerr << "Error: Missing target directory path" << std::endl;
        return 1;
      }
    } else if (arg == "-k" || arg == "--key") {
      if (i + 1 < argc) {
        key = argv[++i];
        if (key.length() < 3) {
          std::cerr << "Error: Key cannot be less than 3 characters" << std::endl;
          return 1;
        }
      } else {
        std::cerr << "Error: Missing encryption key. If you want the program to generate one, do not use the --key flag." << std::endl;
        return 1;
      }
    } else if (arg == "-w" || arg == "--overwrite") {
      if(confirmOverwrite()) {
        overwrite = true;
      } else {
        std::cout << "Operation canceled." << std::endl;
        return 0;
      }
    } else if (arg == "-h" || arg == "--help") {
      showHelp();
      return 0;
    } else {
      std::cerr << "Error: Unknown option " << arg << std::endl;
      showHelp();
      return 1;
    }
  }

  /**
   * Validate arguments
   * Switch validation to a class
   * Parsing must detect flags that cannot coexist
   */
  if (mode.empty()) {
    std::cerr << "Error: No mode specified. Use --encrypt or --decrypt to set the mode." << std::endl;
    return 1;
  }

  if (path.empty()) {
    std::cerr << "Error: No target file specified. Use --file followed by the path to the target file." << std::endl;
    return 1;
  }

  if (mode == "decrypt" && key.empty()) {
    std::cerr << "Error: No key specified. The key is required to decrypt the file." << std::endl;
    return 1;
  }

  key = key.empty() ? generateRandomKey(10) : key;

  if (target) {
    xorDirectory(mode, path, key, overwrite);
  } else {
    xorFile(mode, path, key, overwrite);
  }

  return 0;
}
