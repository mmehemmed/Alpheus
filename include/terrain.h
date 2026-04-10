#pragma once

#include "loader.h"
#include "texture.h"
#include "noise.h"
#include "glm/glm.hpp"


class Terrain {
public:
	Terrain(int gridX, int gridZ,int tilingFactor, Loader& loader);
	Terrain(int gridX, int gridZ, int tilingFactor, Loader& loader, PerlinNoise& noise);

	RawModel getModel() const;
	float getX() const;
	float getZ() const;
	float getHeightOfTerrain(float worldX, float worldZ, PerlinNoise& noise) const;
private:
	static const float SIZE;
	static const int VERTEX_COUNT;
	float x;
	float z;
	RawModel model;
	int tilingFactor = 1;

	RawModel generateFlatTerrain(Loader& loader);
	RawModel generateRandomTerrain(Loader& loader,PerlinNoise& noise);

	glm::vec3 calculateNormal(int x, int z, PerlinNoise& noise) const;
};
	