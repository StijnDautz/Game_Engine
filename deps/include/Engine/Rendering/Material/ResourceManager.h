#pragma once
#include "Shader.h"
#include "Shaderpack.h"
#include "Texture.h"
#include "Mesh.h"

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
	void AddMesh(std::string name, Mesh * mesh);

	//TEXTURES
	Texture* LoadTexture(const std::string filePath);
	Texture* AddTexture(std::string name, Texture* texture);
	Texture* AddTexture(std::string name, std::vector<unsigned char> pixels, int width, int height);

	//SHADERS
	Shader* LoadShader(GLenum type, std::string filePath);

	//SHADERPACKS
	Shaderpack* LoadShaderpack(std::string name, std::string vsFilepath, std::string fsFilepath);
	void AddShaderpack(std::string name, Shaderpack* shaderpack);

	//GET FUNCTIONS
	inline Mesh * GetMesh(std::string name) { return _meshes.at(name); }
	inline Texture* GetTexture(std::string name) { return _textures.at(name); }
	inline Shader* GetShader(std::string name) { return _shaders.at(name); }
	inline Shaderpack* GetShaderpack(std::string name) { return _shaderpacks.at(name); }

private:
	std::map<std::string, Mesh*> _meshes;
	std::map<std::string, Texture*> _textures;
	std::map<std::string, Shader*> _shaders;
	std::map<std::string, Shaderpack*> _shaderpacks;
};