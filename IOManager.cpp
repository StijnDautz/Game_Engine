#include "IOManager.h"
#include "Logger.h"
#include "picoPNG.h"

#include <fstream>
#include <iostream>

std::string ReadStringFromFile(std::string filePath)
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

//this function was written by Ben Arnolds
bool readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer) {
	std::ifstream file(filePath, std::ios::binary);
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