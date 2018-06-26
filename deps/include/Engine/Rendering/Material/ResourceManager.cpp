#include "ResourceManager.h"
#include "ShaderFactory.h"
#include "TextureFactory.h"
#include "ShaderpackFactory.h"

//MESH
void ResourceManager::AddMesh(std::string name, Mesh * mesh)
{
	_meshes.insert(std::make_pair(name, mesh));
}

//TEXTURE
Texture * ResourceManager::LoadTexture(std::string filePath)
{
	return AddTexture(filePath, TextureFactory::loadFromFile(filePath));
}

Texture* ResourceManager::AddTexture(std::string name, Texture* texture)
{
	_textures.insert(std::make_pair(name, texture));
	return texture;
}

Texture * ResourceManager::AddTexture(std::string name, std::vector<unsigned char> pixels, int width, int height)
{
	return AddTexture(name, TextureFactory::create(pixels, width, height));
}

//SHADER
Shader* ResourceManager::LoadShader(GLenum type, std::string filePath)
{
	Shader* shader = ShaderFactory::create(type, filePath);

	_shaders.insert(std::make_pair(filePath, shader));
	return shader;
}

Shaderpack * ResourceManager::LoadShaderpack(std::string name, std::string vsFilepath, std::string fsFilepath)
{
	GLuint vsID = LoadShader(GL_VERTEX_SHADER, vsFilepath)->id;
	GLuint fsID = LoadShader(GL_FRAGMENT_SHADER, fsFilepath)->id;
	Shaderpack* pack = ShaderpackFactory::create(vsID, fsID);
	AddShaderpack(name, pack);
	return pack;
}

//SHADERPACK
void ResourceManager::AddShaderpack(std::string name, Shaderpack * shaderpack)
{
	_shaderpacks.insert(std::make_pair(name, shaderpack));
}
