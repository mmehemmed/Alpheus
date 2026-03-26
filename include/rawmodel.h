#pragma once

class RawModel {
public:
	unsigned int vaoID;
	int vertexCount;

	RawModel(unsigned int vaoID, int vertexCount) {
		this->vaoID = vaoID;
		this->vertexCount = vertexCount;
	}
};