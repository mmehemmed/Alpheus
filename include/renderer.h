#pragma once

#include "tools.h"
#include "entity.h"
#include "light.h"
#include "shader.h"
#include "glad.h"
#include "camera.h"
#include <glm/ext/matrix_clip_space.hpp>

class Renderer {
public:
	Renderer();
	~Renderer();
	void prepare();
	void render(const Camera& camera,const Light& light, const Entity& entity,const Shader& shader, bool debugRenderMode);
};