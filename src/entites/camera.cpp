#include "camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glfw3.h>

void Camera::move(float deltaTime, InputManager inputManager) {
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
}

void Camera::rotate(float deltaTime, InputManager inputManager) {
	// Rotate up/down
	if (inputManager.getKeyState(UP)) { // Up arrow key
		pitch += speed * deltaTime * rotationSpeed; // Adjust rotation speed as needed
	}
	if (inputManager.getKeyState(DOWN)) { // Down arrow key
		pitch -= speed * deltaTime * rotationSpeed;
	}
	// Rotate left/right
	if (inputManager.getKeyState(LEFT)) { // Left arrow key
		yaw -= speed * deltaTime * rotationSpeed;
	}
	if (inputManager.getKeyState(RIGHT)) { // Right arrow key
		yaw += speed * deltaTime * rotationSpeed;
	}
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