#include "IOManager.h"
#include "Logger.h"
#include "picoPNG.h"

#include <fstream>
#include <iostream>
#include <windows.h>
#include <string>

std::string ExePath() {
	char buffer[MAX_PATH];
	GetModuleFileNameA(NULL, buffer, MAX_PATH);
	std::string::size_type pos = std::string(buffer).find_last_of("\\/");
	return std::string(buffer).substr(0, pos);
}

std::string GetGlobalPath(std::string filePath) {
	return ExePath() + "/" + filePath;
}

std::string ReadStringFromFile(std::string filePath)
{
	std::ifstream stream(GetGlobalPath(filePath));
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

//this function was written by Ben Arnolds
bool readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer) {
	std::ifstream file(GetGlobalPath(filePath), std::ios::binary);
	if (file.fail()) {
		perror(filePath.c_str());
		fatalError(filePath + " could not be loaded");
		return false;
	}

	//seek to the end
	file.seekg(0, std::ios::end);

	//Get the file size
	unsigned int fileSize = (unsigned int)file.tellg();
	file.seekg(0, std::ios::beg);

	//Reduce the file size by any header bytes that might be present
	fileSize -= (unsigned int)file.tellg();

	buffer.resize(fileSize);
	file.read((char *)&(buffer[0]), fileSize);
	file.close();

	return true;
}

// differentiate between editable texture and static texture, when an editable texture is pushed to the GPU is needs to be transformed into a static texture
std::vector<unsigned char> LoadPixelsFromFile(const char * filename, int& width, int& height)
{
	std::vector<unsigned char> buffer, image;
	unsigned long w, h;

	readFileToBuffer(filename, buffer);
	int error = decodePNG(image, w, h, &buffer[0], (unsigned long)buffer.size());

	width = w;
	height = h;

	if (error != 0) {
		std::cout << "error: " << error << std::endl;
	}

	return image;
}