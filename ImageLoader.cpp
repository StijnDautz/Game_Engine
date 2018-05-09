#include <fstream>
#include "ImageLoader.h"
#include "picoPNG.h"
/*
ImageLoader::ImageLoader()
{
}

Sprite ImageLoader::LoadImageAsBuffer(char * filename)
{
	std::vector<unsigned char> buffer, image;
	unsigned long w, h;

	loadFile(buffer, filename);
	int error = decodePNG(image, w, h, &buffer[0], (unsigned long)buffer.size());

	if (error != 0) {
		std::cout << "error: " << error << std::endl;
	}

	return Sprite(image, w, h);
}

// this function was written by the same people who wrote picoPNG.cpp
void ImageLoader::loadFile(std::vector<unsigned char>& buffer, const std::string& filename) //designed for loading files from hard disk in an std::vector
{
	std::ifstream file(filename.c_str(), std::ios::in | std::ios::binary | std::ios::ate);

	//get filesize
	std::streamsize size = 0;
	if (file.seekg(0, std::ios::end).good()) size = file.tellg();
	if (file.seekg(0, std::ios::beg).good()) size -= file.tellg();

	//read contents of the file into the vector
	if (size > 0)
	{
		buffer.resize((size_t)size);
		file.read((char*)(&buffer[0]), size);
	}
	else buffer.clear();
}*/