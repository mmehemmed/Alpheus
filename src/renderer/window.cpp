#include "Window.h"
#include <iostream>

Window::Window(int width, int height, std::string title) {
	this->width = width;
	this->height = height;
	this->title = title;
}

Window::~Window() {
	glfwDestroyWindow(window);
	glfwTerminate();
}

void Window::create(){
	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		exit(-1);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if(!window) {
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		exit(-1);
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Failed to initialize GLAD" << std::endl;
		exit(-1);
	}
	//glfwSwapInterval(1); // V-Sync
	glEnable(GL_DEPTH_TEST);
	glfwSetWindowAspectRatio(window, 16,9);
	//glfwSetKeyCallback(window, key_callback);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Window::destroy() {
	glfwDestroyWindow(window);
	glfwTerminate();
}

void Window::updateFPSCounter() {
	currentTime = glfwGetTime();
	double frameTime = currentTime - lastTime;
	deltaTime = frameTime;

	lastTime = currentTime;
	fpsTimer +=frameTime;
	numberOfFrames++;
	if (fpsTimer >= 1.0) {
		std::string newTitle = title + " - FPS: " + std::to_string(numberOfFrames);
		glfwSetWindowTitle(window, newTitle.c_str());
		numberOfFrames = 0;
		fpsTimer = 0.0;
	}
}

bool Window::shouldClose() {
	return glfwWindowShouldClose(window);
}

void Window::swapBuffers() {
	glfwSwapBuffers(window);
}

void Window::pollEvents() {
	glfwPollEvents();
}

double Window::getDeltaTime() const {
	return deltaTime;
}

float Window::getTime() const {
	return glfwGetTime();
}

void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}