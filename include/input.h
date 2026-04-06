#pragma once

#include "window.h"
#include <vector>
#include <glm/glm.hpp>

class InputManager {

public:
	static void checkControls(Window& window);
	static bool getKeyState(int key);
	static glm::vec2 getMousePos();
private:
	static std::vector<bool> keys;
	static double xPos, yPos; // Store mouse position
};

enum Key {
	W = GLFW_KEY_W,
	S = GLFW_KEY_S,
	A = GLFW_KEY_A,
	D = GLFW_KEY_D,
	Q = GLFW_KEY_Q,
	E = GLFW_KEY_E,
	F = GLFW_KEY_F,
	UP = GLFW_KEY_UP,
	DOWN = GLFW_KEY_DOWN,
	LEFT = GLFW_KEY_LEFT,
	RIGHT = GLFW_KEY_RIGHT,
	LSHIFT = GLFW_KEY_LEFT_SHIFT
};