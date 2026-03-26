#pragma once

class RawModel {
public:
	RawModel(unsigned int vaoID, int vertexCount) {
		this->vaoID = vaoID;
		this->vertexCount = vertexCount;
	}
	unsigned int getVaoID() const {
		return vaoID;
	}
	int getVertexCount() const {
		return vertexCount;
	}
private:
	unsigned int vaoID;
	int vertexCount;
};