#include "tools.h"

glm::mat4 createTransformationMatrix(const glm::vec3& translation, const glm::vec3& rotation, float scale) {
	glm::mat4 matrix(1.0f); // Start with an identity matrix
	matrix = glm::translate(matrix, translation); // Apply translation
	matrix = glm::rotate(matrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)); // Rotate around X-axis
	matrix = glm::rotate(matrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)); // Rotate around Y-axis
	matrix = glm::rotate(matrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f)); // Rotate around Z-axis
	matrix = glm::scale(matrix, glm::vec3(scale)); // Apply scaling
	return matrix;
}