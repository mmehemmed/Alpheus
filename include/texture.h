#pragma once

#include "glad.h"
#include <string>

class Texture {
public:
	unsigned int id;

	Texture(const std::string& filePath);
	void bind() const;
};