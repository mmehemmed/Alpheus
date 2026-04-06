#include "terrain.h"


// In terrain.cpp
const float Terrain::SIZE = 128.0f; // Or whatever size you want
const int Terrain::VERTEX_COUNT = 128;

Terrain::Terrain(int gridX, int gridZ, Loader& loader) : model(0,0){
	x = gridX * SIZE;
	z = gridZ * SIZE;
	model = generateTerrain(loader);
}
RawModel Terrain::getModel() const {
	return model;
}
float Terrain::getX() const {
	return x;
}
float Terrain::getZ() const {
	return z;
}
RawModel Terrain::generateTerrain(Loader& loader) {
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	std::vector<float> textureCoords;
	std::vector<float> normals;
	for (int i = 0; i < VERTEX_COUNT; i++) {
		for (int j = 0; j < VERTEX_COUNT; j++) {
			vertices.push_back((float)j / ((float)VERTEX_COUNT - 1) * SIZE);
			vertices.push_back(0.0f); // Flat terrain, so Y is 0
			vertices.push_back((float)i / ((float)VERTEX_COUNT - 1) * SIZE);
			textureCoords.push_back((float)j / ((float)VERTEX_COUNT - 1));
			textureCoords.push_back((float)i / ((float)VERTEX_COUNT - 1));
			normals.push_back(0.0f); // Upward normal
			normals.push_back(1.0f);
			normals.push_back(0.0f);
		}
	}
	for (int gz = 0; gz < VERTEX_COUNT - 1; gz++) {
		for (int gx = 0; gx < VERTEX_COUNT - 1; gx++) {
			int topLeft = (gz * VERTEX_COUNT) + gx;
			int topRight = topLeft + 1;
			int bottomLeft = ((gz + 1) * VERTEX_COUNT) + gx;
			int bottomRight = bottomLeft + 1;
			indices.push_back(topLeft);
			indices.push_back(bottomLeft);
			indices.push_back(topRight);
			indices.push_back(topRight);
			indices.push_back(bottomLeft);
			indices.push_back(bottomRight);
		}
	}
	return loader.loadToVAO(vertices, indices, textureCoords, normals);
}

