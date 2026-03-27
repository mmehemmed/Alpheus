#include "loader.h"

RawModel Loader::loadToVAO(const std::vector<float>& positions, const std::vector<unsigned int>& indices, const std::vector<float>& textureCoords)
{
	unsigned int vaoID = createVAO();

	storeDataInAttributeList(0, 3, positions);
	storeDataInAttributeList(1, 2, textureCoords);


	unsigned int eboID = storeElementBuffer(indices);
	vbos.push_back(eboID);

	unbindVAO();

	return RawModel(vaoID, indices.size());
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
unsigned int Loader::storeElementBuffer(const std::vector<unsigned int>& indices) {
	unsigned int eboID;
	glGenBuffers(1, &eboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
	return eboID;
}