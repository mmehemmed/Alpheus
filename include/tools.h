#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

glm::mat4 createTransformationMatrix(const glm::vec3& translation, const glm::vec3& rotation, float scale);
glm::vec3 generateRandomVec3(glm::vec3& start, glm::vec3& end);