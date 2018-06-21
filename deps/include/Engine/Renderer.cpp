#include "Renderer.h"
#include "Logger.h"

#include <iostream>

Renderer::Renderer() {}
Renderer::~Renderer() {}

void Renderer::setup()
{
	window = Window("TextureTest", 1024, 512);
}

void Renderer::render()
{
	// clear first
	glClear(GL_COLOR_BUFFER_BIT);

	Shaderpack* shaderpack;
	Texture * texture;
	std::vector<Mesh*> meshes;
	//loop through shaderpacks -> textures -> meshes and draw these
	for (Rendermap::iterator i0 = renderMap.begin(); i0 != renderMap.end(); i0++) {
		shaderpack = i0->first;
		// bind the shaderpack
		shaderpack->Bind();

		for (Texture_Mesh_Combo::iterator i1 = i0->second.begin(); i1 != i0->second.end(); i1++) {
			texture = i1->first;
			meshes = i1->second;
			// bind a texture to the shaderpack
			shaderpack->BindTexture(texture->id);
			for (unsigned int i = 0; i < meshes.size(); i++) {
				// draw the mesh
				meshes.at(i)->draw();
			}
		}
	}

	// check for errors
	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		std::cerr << error << std::endl;
		fatalError("An error occured while rendering");
	}

	window.swap();
}

void Renderer::AddRenderComponent(RenderComponent obj)
{
	if (!renderMap.count(obj.pack)) {
		renderMap.insert(std::make_pair(obj.pack, Texture_Mesh_Combo()));
		renderMap.at(obj.pack).insert(std::make_pair(obj.texture, std::vector<Mesh*> {obj.mesh}));
		return;
	}
	if (!renderMap.at(obj.pack).count(obj.texture)) {
		renderMap.at(obj.pack).insert(std::make_pair(obj.texture, std::vector<Mesh*> {obj.mesh}));
		return;
	}
	renderMap.at(obj.pack).at(obj.texture).push_back(obj.mesh);
}

void Renderer::RemoveRenderComponent(RenderComponent obj)
{
}