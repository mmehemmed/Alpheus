#include "window.h"
#include <iostream>
#include "loader.h"
#include "renderer.h"
#include "shader.h"


int main() {
    std::vector<float> vertices;
    std::vector<float> texCoords;
    std::vector<unsigned int> indices;


    std::vector<bool> keys(1024, false);


	Window window(800, 450, "Alpheus Window");
	window.create();


	Texture texture("C:\\Users\\mmehe\\source\\repos\\Alpheus\\res\\textures\\gold.png");

	Loader loader;
	Renderer renderer;
	Shader shader("C:\\Users\\mmehe\\source\\repos\\Alpheus\\res\\shaders\\vertex.glsl", "C:\\Users\\mmehe\\source\\repos\\Alpheus\\res\\shaders\\fragment.glsl");
	Light light(glm::vec3(0.0f, 3.0f, 5.0f), glm::vec3(1.0f, 1.0f, 1.0f));

	RawModel model = loader.loadOBJ("C:\\Users\\mmehe\\source\\repos\\Alpheus\\res\\models\\dragon.obj");
	TexturedModel texturedModel(model, texture);
	texturedModel.setShininess(1.4f); // Set a higher specular strength for a shinier surface
	texturedModel.setGlossiness(256.0f); // Set a higher glossiness for sharper specular highlights
	Entity modelEntity(texturedModel);
    Camera camera;
    glDisable(GL_CULL_FACE);
	while (!window.shouldClose()) {
        // 1. Update Input State
    // (Assuming you add a way to check keys from your window)
        keys[GLFW_KEY_W] = glfwGetKey(window.window, GLFW_KEY_W) == GLFW_PRESS;
        keys[GLFW_KEY_S] = glfwGetKey(window.window, GLFW_KEY_S) == GLFW_PRESS;
        keys[GLFW_KEY_A] = glfwGetKey(window.window, GLFW_KEY_A) == GLFW_PRESS;
        keys[GLFW_KEY_D] = glfwGetKey(window.window, GLFW_KEY_D) == GLFW_PRESS;
		keys[GLFW_KEY_Q] = glfwGetKey(window.window, GLFW_KEY_Q) == GLFW_PRESS;
		keys[GLFW_KEY_E] = glfwGetKey(window.window, GLFW_KEY_E) == GLFW_PRESS;
		keys[GLFW_KEY_UP] = glfwGetKey(window.window, GLFW_KEY_UP) == GLFW_PRESS;
		keys[GLFW_KEY_DOWN] = glfwGetKey(window.window, GLFW_KEY_DOWN) == GLFW_PRESS;
		keys[GLFW_KEY_LEFT] = glfwGetKey(window.window, GLFW_KEY_LEFT) == GLFW_PRESS;
		keys[GLFW_KEY_RIGHT] = glfwGetKey(window.window, GLFW_KEY_RIGHT) == GLFW_PRESS;

        camera.move(window.getDeltaTime(),keys);
		camera.rotate(window.getDeltaTime(), keys);
		renderer.prepare();

		renderer.render(camera,light,modelEntity,shader,glfwGetKey(window.window,GLFW_KEY_F) == GLFW_PRESS);

		window.updateFPSCounter();
		window.swapBuffers();
		window.pollEvents();
	}
	loader.cleanUp();
	shader.deleteShader();
	window.destroy();
}
