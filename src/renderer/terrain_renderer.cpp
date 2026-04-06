#include "terrain_renderer.h"

TerrainRenderer::TerrainRenderer(Texture& terrainTexture) : terrainTexture(terrainTexture), shader("C:\\Users\\mmehe\\source\\repos\\Alpheus\\res\\shaders\\terrain_vertex.glsl", "C:\\Users\\mmehe\\source\\repos\\Alpheus\\res\\shaders\\terrain_fragment.glsl") {
}
void TerrainRenderer::render(Light& light, Camera& camera,bool debugRenderMode) {
	
	shader.use();
	// 1. GLOBAL UNIFORMS (Set these once per frame, NOT in the loop)
	shader.setUniform1i("texture_sampler", 0); // Set the texture uniform to use texture unit 0
	shader.setUniform3f("light_color", light.getColor().x, light.getColor().y, light.getColor().z);
	shader.setUniform3f("light_position", light.getPosition().x, light.getPosition().y, light.getPosition().z);
	shader.setUniformMat4f("view", camera.getViewMatrix());
	shader.setUniformMat4f("projection", camera.getProjectionMatrix());
	glActiveTexture(GL_TEXTURE0);
	terrainTexture.bind();
	for (const Terrain& terrain : terrains) {
		RawModel model = terrain.getModel();
		glBindVertexArray(model.getVaoID());
		if (debugRenderMode) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Wireframe mode for debugging
		}
		else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Normal fill mode
		}
		shader.setUniformMat4f("model", createTransformationMatrix(glm::vec3(terrain.getX(),0.0f,terrain.getZ()),glm::vec3(0.0f),1.0f));

		glDrawElements(GL_TRIANGLES, model.getVertexCount(), GL_UNSIGNED_INT, 0);
	}
	glBindVertexArray(0);
	terrains.clear(); // Clear terrains after rendering to prepare for the next frame
}
void TerrainRenderer::addTerrain(const Terrain& terrain) {
	terrains.push_back(terrain);
}
