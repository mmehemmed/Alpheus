#pragma once

#include "loader.h"
#include "texture.h"

class Terrain {
public:
	Terrain(int gridX, int gridZ, Loader& loader);
	RawModel getModel() const;
	float getX() const;
	float getZ() const;
private:
	static const float SIZE;
	static const int VERTEX_COUNT;
	float x;
	float z;
	RawModel model;

	RawModel generateTerrain(Loader& loader);
};
	