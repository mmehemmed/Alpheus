#pragma once

#include <string>
#include <glad.h>
#include <glfw3.h>

class Window {
public:
    int width, height;
    std::string title;
    GLFWwindow* window = nullptr;

    Window(int width, int height, std::string title);
    ~Window();

    void create();
	void destroy();
	void updateFPSCounter();


	bool shouldClose();
	void swapBuffers();
	void pollEvents();
	double getDeltaTime() const;
	float getTime() const;

private:
	double lastTime = 0.0;
	double currentTime = 0.0;
	double deltaTime = 0.0;
	double fpsTimer = 0.0;
	int numberOfFrames = 0;

    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

};