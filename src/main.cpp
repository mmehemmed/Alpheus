#include "window.h"
#include <iostream>
#include "loader.h"
#include "renderer.h"
#include "shader.h"
#include "input.h"

int main() {

	//LOADING ENGINE TEST
	Window window(800, 450, "Alpheus Window");

	//CREATION TEST	
	window.create();

	Loader loader;
	Renderer renderer;
	Shader shader("C:\\Users\\mmehe\\source\\repos\\Alpheus\\res\\shaders\\vertex.glsl", "C:\\Users\\mmehe\\source\\repos\\Alpheus\\res\\shaders\\fragment.glsl");
	Light light(glm::vec3(0.0f, 3.0f, 5.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	Camera camera;
	InputManager inputManager;



	//MODEL LOADING TEST
    std::vector<float> vertices;
    std::vector<float> texCoords;
    std::vector<unsigned int> indices;
	Texture texture("C:\\Users\\mmehe\\source\\repos\\Alpheus\\res\\textures\\gold.png");
	RawModel model = loader.loadOBJ("C:\\Users\\mmehe\\source\\repos\\Alpheus\\res\\models\\dragon.obj");
	TexturedModel texturedModel(model, texture);
	texturedModel.setShininess(1.4f); // Set a higher specular strength for a shinier surface
	texturedModel.setGlossiness(256.0f); // Set a higher glossiness for sharper specular highlights
	Entity modelEntity(texturedModel);
	modelEntity.scale = 1.0f; // Scale down the model for better visibility





	//RENDER LOOP TEST
	while (!window.shouldClose()) {
		inputManager.checkControls(window);

        camera.move(window.getDeltaTime(),inputManager);
		camera.rotate(window.getDeltaTime(), inputManager);

		renderer.prepare();
		renderer.render(camera,light,modelEntity,shader,inputManager.getKeyState(F));

		window.updateFPSCounter();
		window.swapBuffers();
		window.pollEvents();
		std::cout << "Hello Debug: " << window.getTime() << std::endl;
	}
	loader.cleanUp();
	shader.deleteShader();
	window.destroy();
}
