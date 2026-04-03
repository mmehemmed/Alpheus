#pragma once

#include "window.h"
#include <vector>

class InputManager {

public:
	static void checkControls(Window& window);
	static bool getKeyState(int key);
private:
	static std::vector<bool> keys;
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
	RIGHT = GLFW_KEY_RIGHT
};