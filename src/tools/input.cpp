#include "input.h"

std::vector<bool> InputManager::keys = std::vector<bool>(1024, false); // Initialize the keys vector with 1024 entries set to false
double InputManager::xPos = 0.0;
double InputManager::yPos = 0.0;

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
	keys[LSHIFT] = glfwGetKey(window.window, LSHIFT) == GLFW_PRESS;

	glfwGetCursorPos(window.window, &xPos, &yPos);
}
glm::vec2 InputManager::getMousePos() {
	return glm::vec2(static_cast<float>(xPos), static_cast<float>(yPos));
}
bool InputManager::getKeyState(int key){
	return keys[key];
}