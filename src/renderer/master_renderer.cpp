#include "master_renderer.h"

MasterRenderer::MasterRenderer() : shader("C:\\Users\\mmehe\\source\\repos\\Alpheus\\res\\shaders\\vertex.glsl", "C:\\Users\\mmehe\\source\\repos\\Alpheus\\res\\shaders\\fragment.glsl"), terrainTexture("C:\\Users\\mmehe\\source\\repos\\Alpheus\\res\\textures\\tex.png"), terrainShader("C:\\Users\\mmehe\\source\\repos\\Alpheus\\res\\shaders\\terrain_vertex.glsl", "C:\\Users\\mmehe\\source\\repos\\Alpheus\\res\\shaders\\terrain_fragment.glsl") {
	// Initialize the shader and renderer
}
MasterRenderer::~MasterRenderer() {
	cleanUp();
}
void MasterRenderer::addEntity(const Entity& entity) {
	const TexturedModel* model = entity.getModel();
	entities[model].push_back(entity);
}
void MasterRenderer::render(const Camera& camera, const Light& light, bool debugRenderMode) {
	shader.use();

	// 1. GLOBAL UNIFORMS (Set these once per frame, NOT in the loop)
	loadGlobalUniforms(shader, light, camera);

	//PAIR: MODEL -> ENTITIES
	for (auto& pair : entities) {
		const TexturedModel* model = pair.first;
		std::vector<Entity>& batch = pair.second;

		// 2. Material and Model Binding (Bind the model and texture once per batch)
		glBindVertexArray(model->getRawModel().getVaoID()); // Bind the VAO for this model
		glActiveTexture(GL_TEXTURE0);
		model->getTexture().bind();

		loadMaterialUniforms(shader, *model); 


		if(debugRenderMode) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Wireframe mode for debugging
		} else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Normal fill mode
		}

		for (const Entity& entity : batch) {
			// 3. INSTANCE-SPECIFIC BINDING
			shader.setUniformMat4f("model", createTransformationMatrix(entity.position, entity.rotation, entity.scale));

			glDrawArrays(GL_TRIANGLES, 0, model->getRawModel().getVertexCount()); // Draw the entity using the bound model and texture
		}
		// Unbind once after the entire batch is done
		glBindVertexArray(0);
	}
	entities.clear(); // Clear entities after rendering to prepare for the next frame

	// Render terrains
	terrainShader.use();
	loadGlobalUniforms(terrainShader, light, camera); // Set global uniforms for terrain shader
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

		terrainShader.setUniformMat4f("model", createTransformationMatrix(glm::vec3(terrain.getX(), 0.0f, terrain.getZ()), glm::vec3(0.0f), 1.0f));

		glDrawElements(GL_TRIANGLES, model.getVertexCount(), GL_UNSIGNED_INT, 0);
	}
	glBindVertexArray(0);
	terrains.clear(); // Clear terrains after rendering to prepare for the next frame
}


void MasterRenderer::addTerrain(const Terrain& terrain) {
	terrains.push_back(terrain);
}
void MasterRenderer::prepare() {
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void MasterRenderer::cleanUp() {
	shader.deleteShader();
}

void MasterRenderer::loadGlobalUniforms(const Shader& shader, const Light& light, const Camera& camera) const {
	shader.setUniform1i("texture_sampler", 0); // Set the texture uniform to use texture unit 0
	shader.setUniform3f("light_color", light.getColor().x, light.getColor().y, light.getColor().z);
	shader.setUniform3f("light_position", light.getPosition().x, light.getPosition().y, light.getPosition().z);
	shader.setUniform3f("view_position", camera.getPosition().x, camera.getPosition().y, camera.getPosition().z);
	shader.setUniformMat4f("view", camera.getViewMatrix());
	shader.setUniformMat4f("projection", camera.getProjectionMatrix());
}
void MasterRenderer::loadMaterialUniforms(const Shader& shader, const TexturedModel& model) const {
	shader.setUniform1f("shininess", model.getShininess());
	shader.setUniform1f("glossiness", model.getGlossiness());
}