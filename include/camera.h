#pragma once

#include <glm/glm.hpp>
#include "input.h"

class Camera {
public:
	void move(float deltaTime, InputManager& inputManager);
	void rotate(float deltaTime, InputManager& inputManager);
	glm::mat4 getViewMatrix() const; // View matrix for the camera
	glm::mat4 getProjectionMatrix() const; // Projection matrix for the camera
	glm::vec3 getPosition() const { return position; } // Get the current position of the camera

private:
	float speed = 3.0f; // Movement speed
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f); // Initial position
	float pitch = 0.0f; // Rotation around the X-axis
	float yaw = -90.0f; // Rotation around the Y-axis (initialized to look towards negative Z)
	float roll = 0.0f; // Rotation around the Z-axis (not used in this implementation)

	glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f); // World up vector
	glm::vec3 forward = glm::vec3(0.0f, 0.0f, -1.0f); // Initial forward direction
	glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f); // Initial right direction

	const float farPlane = 100.0f; // Far clipping plane distance
	const float nearPlane = 0.1f; // Near clipping plane distance
	const float fov = 90.0f; // Field of view in degrees
	const float aspectRatio = 16.0f / 9.0f; // Aspect ratio (width/height)
	void recalculateDirectionVectors(); // Recalculate forward, right, and up vectors based on current pitch and yaw

	float lastMouseX = 800.0f; // Initial mouse X position (center of the screen)
	float lastMouseY = 450.0f; // Initial mouse Y position (center of the screen)
	float mouseSensitivity = 1.2f; // Mouse sensitivity for rotation
};