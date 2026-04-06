#pragma once

#include "glm/glm.hpp"
#include "textured_model.h"

class Entity {
public:
	glm::vec3 position;
	glm::vec3 rotation;
	float scale = 1.0f;

	Entity(const TexturedModel* model, const glm::vec3& position = glm::vec3(0.0f), const glm::vec3& rotation = glm::vec3(0.0f),const float& scale = 1.0f)
		: model(model), position(position), rotation(rotation), scale(scale) {
	}

	void move(const glm::vec3& delta) {
		position += delta;
	}
	void rotate(const glm::vec3& delta) {
		rotation += delta;
	}
	const TexturedModel* getModel() const {
		return model;
	}
private:
	const TexturedModel* model;
};