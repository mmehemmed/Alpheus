#include "loader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>


RawModel Loader::loadOBJ(const std::string& path) {
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    std::vector<float> texCoords;
	std::vector<float> normals;

    std::vector<glm::vec3> temp_positions;
    std::vector<glm::vec3> temp_normals;
    std::vector<glm::vec2> temp_uvs;

    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "ERROR: Could not open OBJ file at: " << path << std::endl;
        return RawModel(0, 0); // Return an empty model or handle error
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string prefix;
        ss >> prefix;

        if (prefix == "v") {
            glm::vec3 pos;
            ss >> pos.x >> pos.y >> pos.z;
            temp_positions.push_back(pos);
        }
        else if (prefix == "vt") {
            glm::vec2 uv;
            ss >> uv.x >> uv.y;
            uv.y = 1.0f - uv.y; // Flip UVs for OpenGL
            temp_uvs.push_back(uv);
        }
        else if (prefix == "vn") {
            glm::vec3 normal;
            ss >> normal.x >> normal.y >> normal.z;
            temp_normals.push_back(normal);
        }
        else if (prefix == "f") {
            std::string vertexData;
            while (ss >> vertexData) {
                unsigned int vIdx, tIdx, nIdx;
                char slash;

                std::stringstream vss(vertexData);
                // Handle the v/vt/vn format
                if (vss >> vIdx >> slash >> tIdx >> slash >> nIdx) {
                    // Positions
                    glm::vec3 pos = temp_positions[vIdx - 1];
                    vertices.push_back(pos.x); vertices.push_back(pos.y); vertices.push_back(pos.z);

                    // UVs
                    glm::vec2 uv = temp_uvs[tIdx - 1];
                    texCoords.push_back(uv.x); texCoords.push_back(uv.y);

                    //Normals
					glm::vec3 normal = temp_normals[nIdx - 1];
					normals.push_back(normal.x); normals.push_back(normal.y); normals.push_back(normal.z);

                    // Indices
                    indices.push_back((unsigned int)indices.size());
                }
            }
        }
    }

    // Finally, load these vectors into a VAO and return the RawModel
    return loadToVAO(vertices, indices, texCoords, normals);
}

RawModel Loader::loadToVAO(const std::vector<float>& positions, const std::vector<unsigned int>& indices, const std::vector<float>& textureCoords, const std::vector<float>& normals)
{
	unsigned int vaoID = createVAO();

	storeDataInAttributeList(0, 3, positions);
	storeDataInAttributeList(1, 2, textureCoords);
    storeDataInAttributeList(2, 3, normals);



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