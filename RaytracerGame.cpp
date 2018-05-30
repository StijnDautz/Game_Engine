#include "RaytracerGame.h"
#include "Sphere.h"
#include "Plane.h"
#include "Constants.h"
#include "ColoredObj.h"
#include "TexturedObj.h"
#include "NormalMapObj.h"

#include "Engine\MeshFactory.h"
#include "Engine\TextureFactory.h"
#include "Engine\ShaderpackFactory.h"
#include "Engine\TextureEditor.h"

#include <vector>
#include <thread>

void RaytracerGame::load()
{	
	resourceManager->LoadTexture("Textures/knight.png");
	resourceManager->LoadShader(GL_VERTEX_SHADER, "Shaders/vertexShader.glsl");
	resourceManager->LoadShader(GL_FRAGMENT_SHADER, "Shaders/fragmentShader.glsl");	
}

void RaytracerGame::init()
{
	SetFocallength();

	// init render assets, image and debug quad
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
	// colors and textures
	RGBA32 blue = RGBA32(glm::vec3(0.1f, 0.1f, 1.0f));
	RGBA32 red = RGBA32(glm::vec3(0.9f, 0.1f, 0.1f));
	Texture* knight = resourceManager->GetTexture("Textures/knight.png");

	// primitives
	Primitive* sphere0 = new Sphere(glm::vec3(2, 0, 4.0f), 1.0f);
	Primitive* sphere1 = new Sphere(glm::vec3(-2.0f, 0.0f, 5.0f), 1.0f);
	Primitive* sphere2 = new Sphere(glm::vec3(0.0f, 0, 8.0f), 1.0f);
	Primitive* plane0 = new Plane(glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(0, 1.0f, 0));

	// combine elements into objects
	_scene.AddObject(new ColoredObj(sphere0, blue, 1.0f, 0.0f));	// blue sphere
	_scene.AddObject(new ColoredObj(sphere2));						// mirror sphere
	_scene.AddObject(new TexturedObj(sphere1, knight, 1.0f, 0.0f));	// textured sphere
	_scene.AddObject(new ColoredObj(plane0, red, 0.8f, 0.2f));		// dielectic plane

	// lights
	_scene.AddLight(Light(glm::vec3(0.0f, 0.0f, 5.0f), 1.0f));
	_scene.AddLight(Light(glm::vec3( 3.0f, 3.0f, 5.0f), 1.0f));
	_scene.AddLight(Light(glm::vec3(0.0f, 0.0f, -3.0f), 1.0f));
	_scene.AddLight(Light(glm::vec3(0.0f, 0.0f, 8.0f), 1.0f));
	_scene.AddLight(Light(glm::vec3(0.0f, 10.0f, 2.0f), 1.0f));
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
	glm::vec3 yAxis = camera.yAxis();
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
	if (inputManager->IsKeyDown(SDL_SCANCODE_R)) {
		camera.Reset();
	}

	// ROTATION
	glm::vec2 move = inputManager->GetMouseMovement();
	//glm::vec3 pitch = camera.xAxis() * glm::vec3(1, 0, 0) * move.y * 0.3f;
	glm::vec3 yaw = glm::vec3(0, 1, 0) * move.x * 0.3f;

	camera.Rotate(yaw);// +pitch);

	// can use localPosition, since there is no scenegraph in the raytracer
	glm::vec3 topleft =
		camera.GetLocalPosition() +
		xAxis * -0.5f +
		yAxis *  0.5f +
		zAxis * focalLength;

	// compute interval per pixel
	glm::vec3 xInterval = xAxis * (1.0f / resolutionX);
	glm::vec3 yInterval = -yAxis * (1.0f / resolutionY);

	if (debuggerEnabled) {
		DebugLoop(topleft, xInterval, yInterval);
	} else {
		std::vector<std::thread> threads;
		for (int i = 0; i < THREADCOUNT; i++) {
			threads.push_back(std::thread(&RaytracerGame::ComputePart, this, i, topleft, xInterval, yInterval));
		}
		for (int i = 0; i < THREADCOUNT; i++) {
			threads[i].join();
		}
	}

	image->update();
}

void RaytracerGame::ComputePart(int x, glm::vec3 topleft, glm::vec3 xInterval, glm::vec3 yInterval)
{
	float xStart = (float)x / THREADCOUNT;
	float xEnd = (float)(x + 1) / THREADCOUNT;
	int resXmin = xStart * resolutionY;
	int resXmax = xEnd * resolutionY;
	
	// can use localPosition, since there is no scenegraph in the raytracer
	topleft += camera.xAxis() * xStart;

	// compute interval per pixel
	glm::vec3 axInterval = xInterval / ANTIALLIASING;
	glm::vec3 ayInterval = yInterval / ANTIALLIASING;

	// setup loop variables
	Ray ray = Ray(camera.GetLocalPosition());
	glm::vec3 target;

	// DEBUGGER
	// Has no antialliasing and multithreading
	if (debuggerEnabled) {
		DebugLoop(topleft, xInterval, yInterval);
	}
	else {
		RGBA32 color;
		RGBA32 tempColor;
		float ANTIALLIASINGSQUARED = ANTIALLIASING * ANTIALLIASING;
		for (int y = 0; y < resolutionY; y++) {
			// change target
			target = topleft + (float)y * yInterval;

			for (int x = resXmin; x < resXmax; x++) {
				color = RGBA32();
				// compute ANTIALLIASINGSQUARED times the color for each pixel, using a little offset
				for (float y1 = 0; y1 < ANTIALLIASING; y1++) {
					for (float x1 = 0; x1 < ANTIALLIASING; x1++) {
						ray.SetTarget(target + x1 * axInterval + y1 * ayInterval);
						tempColor = _scene.Trace(ray, 0);
						if (tempColor.color.x > 1 || tempColor.color.y > 1 || tempColor.color.z > 1) {
							int p = 0;
						}
						color += tempColor;
					}
				}

				TextureEditor::drawPixel(image, x, y, (color / ANTIALLIASINGSQUARED).toRGBA8());
				target += xInterval;
			}
		}
	}
}

void RaytracerGame::DebugLoop(glm::vec3 topleft, glm::vec3 xInterval, glm::vec3 yInterval)
{
	debug->clear();

	Ray ray = Ray(camera.GetLocalPosition());
	glm::vec3 target;

	RGBA8 color;
	for (int y = 0; y < resolutionY; y++) {
		// change target
		target = topleft + (float)y * yInterval;

		for (int x = 0; x < resolutionX; x++) {
			ray.SetTarget(target);
			if (ray.d.y == 0.0f && x % 40 == 0) {
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

void RaytracerGame::SetFocallength()
{
		float halfFOV = FOV * 0.5f;
		focalLength = 0.5f / std::tan(glm::radians(halfFOV));
}