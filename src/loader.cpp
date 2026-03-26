#include "loader.h"

RawModel Loader::loadToVAO(const std::vector<float>& positions)
{
	unsigned int vaoID = createVAO();

	storeDataInAttributeList(0, 3, positions);

	unbindVAO();

	return RawModel(vaoID, positions.size()/3);
}
unsigned int Loader::createVAO()
{
	unsigned int vaoID;
	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);
	vaos.push_back(vaoID);
	return vaoID;
}
void Loader::storeDataInAttributeList(int attributeNumber, int coordinateSize, const std::vector<float>& data)
{
	unsigned int vboID;
	glGenBuffers(1, &vboID);
	vbos.push_back(vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(attributeNumber, coordinateSize, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(attributeNumber);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void Loader::unbindVAO()
{
	glBindVertexArray(0);
}
void Loader::cleanUp()
{
	for (unsigned int vao : vaos) {
		glDeleteVertexArrays(1, &vao);
	}
	for (unsigned int vbo : vbos) {
		glDeleteBuffers(1, &vbo);
	}
}