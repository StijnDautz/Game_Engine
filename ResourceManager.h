#pragma once
#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"

#include <string>
#include <vector>
#include <map>

class ResourceManager
{
public:
	ResourceManager() {}
	~ResourceManager() {}

	//MESHES
	//TODO Mesh* LoadMesh(std::string filePath);
	void AddMesh(std::string name, Mesh* mesh);

	//TEXTURES
	Texture* LoadTexture(const std::string filePath);
	Texture* AddTexture(std::string name, std::vector<unsigned char> pixels, int width, int height);

	//SHADERS
	Shader* LoadShader(GLenum type, std::string filePath);

	//GET FUNCTIONS
	Mesh * GetMesh(std::string name) { return _meshes.at(name); }
	Texture* GetTexture(std::string name) { return _textures.at(name); }
	Shader* GetShader(std::string name) { return _shaders.at(name); }

private:
	std::map<std::string, Mesh*> _meshes;
	std::map<std::string, Texture*> _textures;
	std::map<std::string, Shader*> _shaders;

	//TEXTURES helper function
	Texture* InsertTexture(std::string name, Texture* texture);
};