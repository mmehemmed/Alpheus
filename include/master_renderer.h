#pragma once

#include <tools.h>
#include "entity.h"
#include "camera.h"
#include "light.h"
#include "shader.h"
#include "terrain.h"

class MasterRenderer {
public:
	MasterRenderer();
	~MasterRenderer();
	void addEntity(const Entity& entity);
	void addTerrain(const Terrain& terrain);
	void render(const Camera& camera, const Light& light, bool debugRenderMode);
	void prepare();
	void cleanUp();
private:
	Shader shader;
	Shader terrainShader;

	Texture terrainTexture;

	std::vector<Terrain> terrains;
	std::unordered_map<const TexturedModel*, std::vector<Entity>> entities;

	void loadGlobalUniforms(const Shader& shader, const Light& light, const Camera& camera) const;
	void loadMaterialUniforms(const Shader& shader, const TexturedModel& model) const;

};