#pragma once

#include <string>
#include "glad.h"
#include <unordered_map>
#include <glm/gtc/type_ptr.hpp>


class Shader {
public:
	unsigned int ID;

	Shader(const std::string& vertexPath, const std::string& fragmentPath);
	void use() const;
	void deleteShader() const;

	void setUniform1b(const std::string& name, bool value) const;
	void setUniform1i(const std::string& name, int value) const;
	void setUniform1f(const std::string& name, float value) const;
	void setUniform2f(const std::string& name, float x, float y) const;
	void setUniform3f(const std::string& name, float x, float y, float z) const;
	void setUniform4f(const std::string& name, float x, float y, float z, float w) const;
	void setUniformMat4f(const std::string& name, const glm::mat4 matrix) const;

private:
	mutable std::unordered_map<std::string, int> uniformLocationCache;
	int getUniformLocation(const std::string& name) const;
};