#include <string>
#include <vector>
#include "safeguard.h"

bool isCriticalDir(const std::string &targetPath) {
  std::vector<std::string> criticalDirs = {
    // Windows
    "C:\\Windows", "C:\\Program Files", "C:\\Program Files (x86)", "C:\\System32",
    "C:\\Windows\\", "C:\\Windows\\System32\\", "C:\\Windows\\SysWOW64\\", "C:\\ProgramData\\", "C:\\AppData\\Roaming\\", "C:\\Users\\",

    // Linux/Unix
    "/bin", "/boot", "/dev", "/etc", "/lib", "/usr", "/var", "/proc/", "/sys/",

    // MacOS
    "/etc/hosts", "/Library/SYSTEMConfiguration/com.apple.SysAdmin.plist", "/var/db/dscl.conf", "/usr/bin/login",
  };
  for (const auto &dir : criticalDirs) {
    if (targetPath.find(dir) == 0) {
      return true;
    }
  }

  return false;
}
