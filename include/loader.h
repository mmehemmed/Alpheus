#pragma once

#include <vector>
#include <string>
#include "glad.h"
#include "rawmodel.h"

class Loader{
public:
	RawModel loadToVAO(const std::vector<float>& positions, const std::vector<unsigned int>& indices, const std::vector<float>& textureCoords, const std::vector<float>& normals);
	RawModel loadOBJ(const std::string& path);
	void cleanUp();
private:
	std::vector<unsigned int> vaos;
	std::vector<unsigned int> vbos;

	unsigned int createVAO();
	void storeDataInAttributeList(int attributeNumber, int coordinateSize, const std::vector<float>& data);
	void unbindVAO();
	unsigned int storeElementBuffer(const std::vector<unsigned int>& indices);
};