#include "window.h"
#include <iostream>
#include "loader.h"
#include "input.h"
#include "master_renderer.h"
#include "noise.h"
#include "terrain.h"

int main() {
	std::cout << "Starting Alpheus Engine..." << std::endl;
	//LOADING ENGINE TEST
	Window window(1600, 900, "Alpheus Window");

	//CREATION TEST	
	window.create();

	Loader loader;
	MasterRenderer renderer;
	Light light(glm::vec3(64.0f, 32.0f, 64.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	Camera camera;
	InputManager inputManager;


	//MODEL LOADING TEST
	Texture texture("C:\\Users\\mmehe\\source\\repos\\Alpheus\\res\\textures\\tree.png");
	Texture greenT("C:\\Users\\mmehe\\source\\repos\\Alpheus\\res\\textures\\tex.png");

	RawModel model = loader.loadOBJ("C:\\Users\\mmehe\\source\\repos\\Alpheus\\res\\models\\tree.obj");
	TexturedModel texturedModel(model, texture);
	texturedModel.setShininess(1.0f); // Set a higher specular strength for a shinier surface
	texturedModel.setGlossiness(64.0f); // Set a higher glossiness for sharper specular highlights

	PerlinNoise noise = PerlinNoise(563625); // You can choose any seed value for different terrain variations


	Terrain terrain1(0, 0, 16, loader,noise);
	//Terrain terrain2(0, 1,40, loader, noise);
	//Terrain terrain3(1, 0,40, loader, noise);
	//Terrain terrain4(1, 1,40, loader, noise);


	std::vector<Entity> entities;

	for (size_t i = 0; i < 30; i++)
	{
		float x = generateRandomFloat(terrain1.getX(), terrain1.getX() + 128);
		float z = generateRandomFloat(terrain1.getZ(), terrain1.getZ() + 128);
		float y = terrain1.getHeightOfTerrain(x, z, noise);
		entities.push_back(Entity(&texturedModel, glm::vec3(x, y, z), glm::vec3(0.0f), 3.0f));
	}

	entities.push_back(Entity(&texturedModel, light.getPosition(),glm::vec3(0.0f), 4.0f));



	//RENDER LOOP TEST
	while (!window.shouldClose()) {
		inputManager.checkControls(window);

        camera.move(window.getDeltaTime(),inputManager);
		camera.rotate(inputManager);

		renderer.prepare();
		for (Entity& entity : entities) {
			//entity.rotate(glm::vec3(0.0f, 20.0f * window.getDeltaTime(), 0.0f)); // Rotate around the Y-axis
			renderer.addEntity(entity);
		}
		renderer.addTerrain(terrain1);
		//terrainRenderer.addTerrain(terrain2);
		//terrainRenderer.addTerrain(terrain3);
		//terrainRenderer.addTerrain(terrain4);



		renderer.render(camera, light, inputManager.getKeyState(F));

		window.updateFPSCounter();
		window.swapBuffers();
		window.pollEvents();
	}
	loader.cleanUp();
	renderer.cleanUp();
	window.destroy();
}
