#include "camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glfw3.h>

void Camera::move(float deltaTime, InputManager& inputManager) {
	// Move forward/backward
	if (inputManager.getKeyState(W)) { // W key
		position += forward * speed * deltaTime;
	}
	if (inputManager.getKeyState(S)) { // S key
		position -= forward * speed * deltaTime;
	}
	// Move left/right
	if (inputManager.getKeyState(A)) { // A key
		position -= right * speed * deltaTime;
	}
	if (inputManager.getKeyState(D)) { // D key
		position += right * speed * deltaTime;
	}
	if (inputManager.getKeyState(Q)) { // Q key
		position += worldUp * speed * deltaTime; // Move up
	}
	if (inputManager.getKeyState(E)) { // E key
		position -= worldUp * speed * deltaTime; // Move down
	}
	if (inputManager.getKeyState(LSHIFT)) { // Left Shift key for faster movement
		speed =  15.0f; // Move forward faster
	}
	else {
		speed = 3.0f; // Reset to normal speed when Left Shift is not pressed
	}
}

void Camera::rotate(float deltaTime, InputManager& inputManager) {
	glm::vec2 mousePos = inputManager.getMousePos();

	float mouseXOffset = mousePos.x - lastMouseX;
	float mouseYOffset = lastMouseY - mousePos.y; // Invert Y-axis for typical camera controls

	lastMouseX = mousePos.x;
	lastMouseY = mousePos.y;

	mouseXOffset *= mouseSensitivity;
	mouseYOffset *= mouseSensitivity;

	yaw += mouseXOffset * deltaTime;
	pitch += mouseYOffset * deltaTime;
	
	// Constrain the pitch so the screen doesn't flip upside down
	if (pitch > 89.0f)  pitch = 89.0f;
	if (pitch < -89.0f) pitch = -89.0f;

	recalculateDirectionVectors();
}

void Camera::recalculateDirectionVectors() {
	// Calculate the new forward vector
	glm::vec3 newForward;
	newForward.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	newForward.y = sin(glm::radians(pitch));
	newForward.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	forward = glm::normalize(newForward);
	// Recalculate right and up vectors
	right = glm::normalize(glm::cross(forward, worldUp));
}

glm::mat4 Camera::getViewMatrix() const{
	return glm::lookAt(position, position + forward, worldUp);
}
glm::mat4 Camera::getProjectionMatrix() const{
	return glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
}