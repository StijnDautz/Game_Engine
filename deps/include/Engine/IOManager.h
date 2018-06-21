#pragma once
#include <string>
#include <vector>

extern std::string ReadStringFromFile(const std::string filePath);\
extern std::vector<unsigned char> LoadPixelsFromFile(const char* filename, int& width, int& height);
