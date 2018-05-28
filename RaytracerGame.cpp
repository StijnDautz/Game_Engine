#include "RaytracerGame.h"
#include "Sphere.h"

#include "Engine\MeshFactory.h"
#include "Engine\TextureFactory.h"
#include "Engine\ShaderpackFactory.h"
#include "Engine\TextureEditor.h"

RaytracerGame::RaytracerGame() : resolutionX(512), resolutionY(512), focalLength(1) {}
RaytracerGame::~RaytracerGame() {}

void RaytracerGame::load()
{	
	resourceManager->LoadTexture("Textures/knight.png");

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
	Primitive* sphere = new Sphere(glm::vec3(0, 0, 6.0f), 2.0f);
	RGBA32 blue = RGBA32(glm::vec3(0.1f, 0.1f, 1.0f));
	ColoredObj blueSphere = ColoredObj(sphere, blue);
	blueSphere.diffuse = 1.0f;
	_scene.AddObject(blueSphere);

	// lights
	_scene.AddLight(Light(glm::vec3(-4, 0, 0), 1.0f));
}

void RaytracerGame::update()
{
	Game::update();
	if (inputManager->IsKeyDown(SDL_SCANCODE_ESCAPE)) {
		quit();
	}

	// compute topleft corner of screen
	glm::vec3 xAxis = camera.xAxis();
	glm::vec3 yAxis = camera.yAxis();
	glm::vec3 zAxis = camera.zAxis();
	glm::vec3 topleft = zAxis * focalLength + 
						xAxis * -0.5f + 
						yAxis * 0.5f;

	// compute interval per pixel
	glm::vec3 xInterval = xAxis * (1.0f / resolutionX);
	glm::vec3 yInterval = -yAxis * (1.0f / resolutionY);

	// setup loop variables
	Ray ray = Ray(camera.GetLocalPosition());
	RGBA8 color;
	glm::vec3 target;

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

	image->update();
}