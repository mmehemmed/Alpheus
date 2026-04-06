#pragma once

#include <tools.h>
#include "terrain.h"
#include "shader.h"
#include "light.h"
#include "camera.h"

class TerrainRenderer {
public:
	TerrainRenderer(Texture& terrainTexture);
	void render(Light& light, Camera& camera, bool debugRenderMode);
	void addTerrain(const Terrain& terrain);
private:
	Shader shader;
	Texture terrainTexture;
	std::vector<Terrain> terrains;
};