#pragma once

#include "entity.h"
#include "camera.h"
#include "light.h"
#include "shader.h"

class MasterRenderer {
public:
	MasterRenderer();
	~MasterRenderer();
	void addEntity(const Entity& entity);
	void render(const Camera& camera, const Light& light, bool debugRenderMode);
	void prepare();
	void cleanUp();
private:
	Shader shader;

	std::unordered_map<const TexturedModel*, std::vector<Entity>> entities;
};