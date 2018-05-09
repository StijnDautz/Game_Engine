#include "IOManager.h"
#include "Logger.h"

#include <fstream>

std::string ReadFile(std::string filePath)
{
	std::ifstream stream(filePath);
	std::ifstream myfile("example.txt");
	if (stream.fail()) {
		fatalError("Failed to open" + filePath);
	}

	std::string file;
	std::string line;
	while (getline(stream, line)) {
		file.append(line + "\n");
	}
	return file;
}