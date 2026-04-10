#include "terrain.h"

// In terrain.cpp
const float Terrain::SIZE = 128.0f; // Or whatever size you want
const int Terrain::VERTEX_COUNT = 128;
const float MAX_HEIGHT = 20.5f; // Maximum height for the terrain, adjust as needed
const float frequency = 0.008f; // Adjust this for more or less detail


Terrain::Terrain(int gridX, int gridZ,int tilingFactor, Loader& loader) : model(0,0), tilingFactor(tilingFactor){
	x = gridX * SIZE;
	z = gridZ * SIZE;
	model = generateFlatTerrain(loader);
}
Terrain::Terrain(int gridX, int gridZ, int tilingFactor, Loader& loader, PerlinNoise& noise) : model(0, 0), tilingFactor(tilingFactor) {
	x = gridX * SIZE;
	z = gridZ * SIZE;
	model = generateRandomTerrain(loader,noise);
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
RawModel Terrain::generateFlatTerrain(Loader& loader) {
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	std::vector<float> textureCoords;
	std::vector<float> normals;
	for (int i = 0; i < VERTEX_COUNT; i++) {
		for (int j = 0; j < VERTEX_COUNT; j++) {
			vertices.push_back((float)j / ((float)VERTEX_COUNT - 1) * SIZE);
			vertices.push_back(0.0f); // Flat terrain, so Y is 0
			vertices.push_back((float)i / ((float)VERTEX_COUNT - 1) * SIZE);
			textureCoords.push_back((float)j / ((float)VERTEX_COUNT - 1) * tilingFactor);
			textureCoords.push_back((float)i / ((float)VERTEX_COUNT - 1) * tilingFactor);
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

RawModel Terrain::generateRandomTerrain(Loader& loader, PerlinNoise& noise) {


	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	std::vector<float> textureCoords;
	std::vector<float> normals;
	for (int i = 0; i < VERTEX_COUNT; i++) {
		for (int j = 0; j < VERTEX_COUNT; j++) {

			float worldX = ((float)j / ((float)VERTEX_COUNT - 1) * SIZE) + this->x;
			float worldZ = ((float)i / ((float)VERTEX_COUNT - 1) * SIZE) + this->z;

			float height = noise.noise(worldX*frequency, worldZ*frequency);
			vertices.push_back((float)j / ((float)VERTEX_COUNT - 1) * SIZE);
			vertices.push_back(height * MAX_HEIGHT); // Scale height for better visibility
			vertices.push_back((float)i / ((float)VERTEX_COUNT - 1) * SIZE);
			textureCoords.push_back((float)j / ((float)VERTEX_COUNT - 1) * tilingFactor);
			textureCoords.push_back((float)i / ((float)VERTEX_COUNT - 1) * tilingFactor);
			glm::vec3 normal = calculateNormal(j, i, noise);
			normals.push_back(normal.x);
			normals.push_back(normal.y);
			normals.push_back(normal.z);
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

float Terrain::getHeightOfTerrain(float worldX, float worldZ, PerlinNoise& noise) const {
	return noise.noise(worldX * frequency, worldZ * frequency) * MAX_HEIGHT;
}

glm::vec3 Terrain::calculateNormal(int x, int z, PerlinNoise& noise) const {
	float heightL = noise.noise((x - 1) / (float)VERTEX_COUNT * SIZE, z / (float)VERTEX_COUNT * SIZE);
	float heightR = noise.noise((x + 1) / (float)VERTEX_COUNT * SIZE, z / (float)VERTEX_COUNT * SIZE);
	float heightD = noise.noise(x / (float)VERTEX_COUNT * SIZE, (z - 1) / (float)VERTEX_COUNT * SIZE);
	float heightU = noise.noise(x / (float)VERTEX_COUNT * SIZE, (z + 1) / (float)VERTEX_COUNT * SIZE);
	glm::vec3 normal(heightL - heightR, 2.0f, heightD - heightU);
	return glm::normalize(normal);
}
