#pragma once

#include "glm/glm.hpp"
#include "textured_model.h"

class Entity {
public:
	glm::vec3 position;
	glm::vec3 rotation;

	Entity(const TexturedModel& model, const glm::vec3& position = glm::vec3(0.0f), const glm::vec3& rotation = glm::vec3(0.0f))
		: model(model), position(position), rotation(rotation) {
	}

	void move(const glm::vec3& delta) {
		position += delta;
	}
	void rotate(const glm::vec3& delta) {
		rotation += delta;
	}
	TexturedModel getModel() const {
		return model;
	}
private:
	TexturedModel model;
};