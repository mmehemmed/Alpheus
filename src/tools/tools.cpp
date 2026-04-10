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
glm::vec3 generateRandomVec3(glm::vec3& start, glm::vec3& end) {
	float x = start.x + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (end.x - start.x)));
	float y = start.y + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (end.y - start.y)));
	float z = start.z + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (end.z - start.z)));
	return glm::vec3(x, y, z);
}
float generateRandomFloat(float start, float end) {
	return start + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (end - start)));
}