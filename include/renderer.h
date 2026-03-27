#pragma once

#include "rawmodel.h"
#include "shader.h"
#include "glad.h"
#include "texture.h"

class Renderer {
public:
	void prepare();
	void render(const RawModel& model,const Shader& shader, const Texture& texture);
};