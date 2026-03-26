#include "window.h"
#include <iostream>
#include "loader.h"
#include "renderer.h"
#include "shader.h"


int main() {
	std::vector<float> vertices = {
	-0.5f,  0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f
	};


	Window window(800, 450, "Alpheus Window");
	window.create();


	Loader loader;
	Renderer renderer;
	Shader shader("C:\\Users\\mmehe\\source\\repos\\Alpheus\\res\\shaders\\vertex.glsl", "C:\\Users\\mmehe\\source\\repos\\Alpheus\\res\\shaders\\fragment.glsl");

	RawModel model = loader.loadToVAO(vertices);


	while (!window.shouldClose()) {
		renderer.prepare();
		renderer.render(model,shader);

		window.swapBuffers();
		window.pollEvents();
	}
	loader.cleanUp();
	shader.deleteShader();
	window.destroy();
}
