#pragma once

#include <vector>
#include "glad.h"
#include "rawmodel.h"

class Loader{
public:
	RawModel loadToVAO(const std::vector<float>& positions);

	void cleanUp();
private:
	std::vector<unsigned int> vaos;
	std::vector<unsigned int> vbos;

	unsigned int createVAO();
	void storeDataInAttributeList(int attributeNumber, int coordinateSize, const std::vector<float>& data);
	void unbindVAO();
};