#pragma once

#include <string>
#include "glad.h"

class Shader {
public:
	unsigned int ID;

	Shader(const std::string& vertexPath, const std::string& fragmentPath);
	void use() const;
	void deleteShader() const;
};