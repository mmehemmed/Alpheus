#include "input.h"

std::vector<bool> InputManager::keys = std::vector<bool>(1024, false); // Initialize the keys vector with 1024 entries set to false

void InputManager::checkControls(Window& window){
	keys[W] = glfwGetKey(window.window, W) == GLFW_PRESS;
	keys[S] = glfwGetKey(window.window, S) == GLFW_PRESS;
	keys[A] = glfwGetKey(window.window, A) == GLFW_PRESS;
	keys[D] = glfwGetKey(window.window, D) == GLFW_PRESS;
	keys[Q] = glfwGetKey(window.window, Q) == GLFW_PRESS;
	keys[E] = glfwGetKey(window.window, E) == GLFW_PRESS;
	keys[F] = glfwGetKey(window.window, F) == GLFW_PRESS;
	keys[UP] = glfwGetKey(window.window, UP) == GLFW_PRESS;
	keys[DOWN] = glfwGetKey(window.window, DOWN) == GLFW_PRESS;
	keys[LEFT] = glfwGetKey(window.window, LEFT) == GLFW_PRESS;
	keys[RIGHT] = glfwGetKey(window.window, RIGHT) == GLFW_PRESS;
}
bool InputManager::getKeyState(int key){
	return keys[key];
}