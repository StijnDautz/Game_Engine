#include "RaytracerGame.h"
#include "Sphere.h"

#include "Engine\MeshFactory.h"
#include "Engine\TextureFactory.h"
#include "Engine\ShaderpackFactory.h"
#include "Engine\TextureEditor.h"

void RaytracerGame::load()
{	
	resourceManager->LoadShader(GL_VERTEX_SHADER, "Shaders/vertexShader.glsl");
	resourceManager->LoadShader(GL_FRAGMENT_SHADER, "Shaders/fragmentShader.glsl");	
}

void RaytracerGame::init()
{
	// init render assets
	Shader* vert = resourceManager->GetShader("Shaders/vertexShader.glsl");
	Shader* frag = resourceManager->GetShader("Shaders/fragmentShader.glsl");
	Shaderpack* basicpack = ShaderpackFactory::create(vert->id, frag->id);
	resourceManager->AddShaderpack("basic", basicpack);

	image = TextureFactory::create(512, 512, RGBA8(0, 0, 0, 255));
	debug = TextureFactory::create(512, 512, RGBA8(0, 0, 0, 255));

	Mesh* lQuad = MeshFactory::createScreenQuad(-1.0f, 0.0f);
	Mesh* rQuad = MeshFactory::createScreenQuad(0.0f, 1.0f);

	CreateGameObject(RenderComponent(basicpack, image, lQuad));
	CreateGameObject(RenderComponent(basicpack, debug, rQuad));

	//init scene
	// objects
	RGBA32 blue = RGBA32(glm::vec3(0.1f, 0.1f, 1.0f));
	RGBA32 red = RGBA32(glm::vec3(0.9f, 0.1f, 0.1f));

	Primitive* sphere0 = new Sphere(glm::vec3(2, 0, 4.0f), 1.0f);
	ColoredObj blueSphere = ColoredObj(sphere0, blue);
	blueSphere.diffuse = 1.0f;
	_scene.AddObject(blueSphere);

	Primitive* sphere1 = new Sphere(glm::vec3(-1.0f, 0, 5.0f), 1.0f);
	ColoredObj dieletricSphere = ColoredObj(sphere1, red); // TODO color should be able to be uninitialized
	dieletricSphere.diffuse = 0.0f;
	dieletricSphere.specular = 1.0f;
	_scene.AddObject(dieletricSphere);

	// lights
	_scene.AddLight(Light(glm::vec3(-1.0f, 0, 2), 1.0f));
}

void RaytracerGame::update()
{
	Game::update();
	if (inputManager->IsKeyDown(SDL_SCANCODE_ESCAPE)) {
		quit();
	}
	// switch mode when key M is pressed
	if (inputManager->IsKeyDown(SDL_SCANCODE_M)) {
		debuggerEnabled = !debuggerEnabled;
	}

	// XAXIS MOVEMENT
	glm::vec3 xAxis = camera.xAxis();
	if (inputManager->IsKeyDown(SDL_SCANCODE_D)) {
		camera.Translate(glm::vec3(1, 0, 1) * camera.xAxis() *  0.1f);
	}
	if (inputManager->IsKeyDown(SDL_SCANCODE_A)) {
		camera.Translate(glm::vec3(1, 0, 1) * camera.xAxis() * -0.1f);
	}

	// YAXIS MOVEMENT
	if (inputManager->IsKeyDown(SDL_SCANCODE_E)) {
		camera.Translate(glm::vec3(0, 1, 0) *  0.1f);
	}
	if (inputManager->IsKeyDown(SDL_SCANCODE_Q)) {
		camera.Translate(glm::vec3(0, 1, 0) * -0.1f);
	}

	// ZAXIS MOVEMENT
	glm::vec3 zAxis = camera.zAxis();
	if (inputManager->IsKeyDown(SDL_SCANCODE_W)) {
		camera.Translate(glm::vec3(1, 0, 1) * zAxis *  0.1f);
	}
	if (inputManager->IsKeyDown(SDL_SCANCODE_S)) {
		camera.Translate(glm::vec3(1, 0, 1) * zAxis * -0.1f);
	}

	ComputePart(0, 0);
	
	image->update();
}

void RaytracerGame::ComputePart(int x, int y)
{
	// can use localPosition, since there is no scenegraph in the raytracer
	glm::vec3 xAxis = camera.xAxis();
	glm::vec3 yAxis = camera.yAxis();
	glm::vec3 zAxis = camera.zAxis();
	glm::vec3 topleft =
		camera.GetLocalPosition() +
		xAxis * -0.5f +
		yAxis * 0.5f +
		zAxis * focalLength;

	// compute interval per pixel
	glm::vec3 xInterval = xAxis * (1.0f / resolutionX);
	glm::vec3 yInterval = -yAxis * (1.0f / resolutionY);

	// setup loop variables
	Ray ray = Ray(camera.GetLocalPosition());
	RGBA8 color;
	glm::vec3 target;

	if (debuggerEnabled) {
		debug->clear();

		RGBA8 color;
		for (int y = 0; y < resolutionY; y++) {
			// change target
			target = topleft + (float)y * yInterval;

			for (int x = 0; x < resolutionX; x++) {
				ray.SetTarget(target);
				if (ray.d.y == 0.0f && x % 20 == 0) {
					color = _scene.TraceAndDebug(debug, ray, 0).toRGBA8();
				}
				else {
					color = _scene.Trace(ray, 0).toRGBA8();
				}
				TextureEditor::drawPixel(image, x, y, color);

				// move to target a little along the x-axis in the camera's localspace
				target += xInterval;
			}
		}

		_scene.DrawDebug(debug);
		debug->update();
	}
	else {
		for (int y = 0; y < resolutionY; y++) {
			// change target
			target = topleft + (float)y * yInterval;

			for (int x = 0; x < resolutionX; x++) {
				ray.SetTarget(target);
				TextureEditor::drawPixel(image, x, y, _scene.Trace(ray, 0).toRGBA8());

				// move to target a little along the x-axis in the camera's localspace
				target += xInterval;
			}
		}
	}
}
