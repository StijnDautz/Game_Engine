#include "RendererV2.h"
#include "Rendering\Material\MeshRenderer.h"
#include "Core\Transform.h"
#include "IO\Logger.h"

#include <iostream>

void RendererV2::setup()
{
	window = Window("TextureTest", 1024, 512);
}

void RendererV2::render(CameraComponent* camera, std::vector<GameObject*> objects)
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	for (unsigned int i = 0; i < objects.size(); i++) {
		MeshRenderer* mr = objects[i]->GetComponent<MeshRenderer>();
		if (mr == nullptr) {
			continue;
		}

		mr->pack->Bind();
		// BIND UNIFORM VARIABLES
		// Texture
		mr->pack->BindTexture(mr->texture->id);

		// ToWorldMatrix
		glm::mat4 worldMat = objects[i]->GetComponent<Transform>()->GetWorldMatrix();
		glUniformMatrix4fv(mr->pack->toWorldLocation, 1, GL_FALSE, &worldMat[0][0]);
		
		// ToScreenMatrix
		glm::mat4 toScreenMat = camera->toScreen;
		glUniformMatrix4fv(mr->pack->toScreenLocation, 1, GL_FALSE, &toScreenMat[0][0]);

		mr->mesh->draw();
	}

	checkErrors();
	window.swap();
}

void RendererV2::checkErrors()
{
	// check for errors
	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		std::cerr << error << std::endl;
		Log("An error occured while rendering");
	}
}
