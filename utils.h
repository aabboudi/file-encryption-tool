#ifndef UTILS_H
#define UTILS_H

#include <string>

void showHelp();
std::string generateRandomKey(size_t);
bool confirmOverwrite();
void preventSelfDestruction(const std::string&, const std::string&);

#endif
