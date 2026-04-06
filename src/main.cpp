#include "window.h"
#include <iostream>
#include "loader.h"
#include "input.h"
#include "master_renderer.h"
#include "terrain.h"
#include "terrain_renderer.h"

int main() {
	std::cout << "Starting Alpheus Engine..." << std::endl;
	//LOADING ENGINE TEST
	Window window(1600, 900, "Alpheus Window");

	//CREATION TEST	
	window.create();

	Loader loader;
	MasterRenderer renderer;
	Light light(glm::vec3(0.0f, 3.0f, 5.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	Camera camera;
	InputManager inputManager;


	//MODEL LOADING TEST
	Texture texture("C:\\Users\\mmehe\\source\\repos\\Alpheus\\res\\textures\\gold.png");
	Texture greenT("C:\\Users\\mmehe\\source\\repos\\Alpheus\\res\\textures\\green.png");

	RawModel model = loader.loadOBJ("C:\\Users\\mmehe\\source\\repos\\Alpheus\\res\\models\\cube.obj");
	TexturedModel texturedModel(model, texture);
	texturedModel.setShininess(1.0f); // Set a higher specular strength for a shinier surface
	texturedModel.setGlossiness(64.0f); // Set a higher glossiness for sharper specular highlights


	TerrainRenderer terrainRenderer(greenT);
	Terrain terrain(0, 0, loader);



	std::vector<Entity> entities;

	for (size_t i = 0; i < 100; i++)
	{
		entities.push_back(Entity(&texturedModel, generateRandomVec3(glm::vec3(-10.0f), glm::vec3(10.0f)), generateRandomVec3(glm::vec3(0.0f), glm::vec3(360.0f)), 1.0f));
	}



	//RENDER LOOP TEST
	while (!window.shouldClose()) {
		inputManager.checkControls(window);

        camera.move(window.getDeltaTime(),inputManager);
		camera.rotate(window.getDeltaTime(), inputManager);

		renderer.prepare();
		for (Entity& entity : entities) {
			entity.rotate(glm::vec3(0.0f, 20.0f * window.getDeltaTime(), 0.0f)); // Rotate around the Y-axis
			renderer.addEntity(entity);
		}
		terrainRenderer.addTerrain(terrain);

		terrainRenderer.render(light, camera, inputManager.getKeyState(F));

		renderer.render(camera, light, inputManager.getKeyState(F));

		window.updateFPSCounter();
		window.swapBuffers();
		window.pollEvents();
	}
	loader.cleanUp();
	renderer.cleanUp();
	window.destroy();
}
