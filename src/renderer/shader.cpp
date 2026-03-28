#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		vShaderFile.close();
		fShaderFile.close();
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure& e) {
		std::cerr << "ERROR: Shader file not successfully read: " << e.what() << std::endl;
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();
	unsigned int vertex, fragment;
	int success;
	char infoLog[512];
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, nullptr);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
		std::cerr << "ERROR: Vertex shader compilation failed\n" << infoLog << std::endl;
	}
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, nullptr);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
		std::cerr << "ERROR: Fragment shader compilation failed\n" << infoLog << std::endl;
	}
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(ID, 512, nullptr, infoLog);
		std::cerr << "ERROR: Shader program linking failed\n" << infoLog << std::endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

int Shader::getUniformLocation(const std::string& name) const{
	if (uniformLocationCache.find(name) != uniformLocationCache.end())
		return uniformLocationCache[name];
	int location = glGetUniformLocation(ID, name.c_str());
	if (location == -1)
		std::cerr << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;
	uniformLocationCache[name] = location;
	return location;
}

void Shader::setUniform1b(const std::string& name, bool value) const{
	glUniform1i(getUniformLocation(name), (int)value);
}
void Shader::setUniform1i(const std::string& name, int value) const{
	glUniform1i(getUniformLocation(name), value);
}
void Shader::setUniform1f(const std::string& name, float value) const{
	glUniform1f(getUniformLocation(name), value);
}
void Shader::setUniform2f(const std::string& name, float x, float y) const{
	glUniform2f(getUniformLocation(name), x, y);
}
void Shader::setUniform3f(const std::string& name, float x, float y, float z) const{
	glUniform3f(getUniformLocation(name), x, y, z);
}
void Shader::setUniform4f(const std::string& name, float x, float y, float z, float w) const{
	glUniform4f(getUniformLocation(name), x, y, z, w);
}
void Shader::setUniformMat4f(const std::string& name, const glm::mat4 matrix) const{
	glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::use() const {
	glUseProgram(ID);
}
void Shader::deleteShader() const {
	glDeleteProgram(ID);
}