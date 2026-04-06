#include "master_renderer.h"
#include <tools.h>

MasterRenderer::MasterRenderer() : shader("C:\\Users\\mmehe\\source\\repos\\Alpheus\\res\\shaders\\vertex.glsl", "C:\\Users\\mmehe\\source\\repos\\Alpheus\\res\\shaders\\fragment.glsl") {
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
	prepare();
	shader.use();

	// 1. GLOBAL UNIFORMS (Set these once per frame, NOT in the loop)
	shader.setUniform1i("texture_sampler", 0); // Set the texture uniform to use texture unit 0
	shader.setUniform3f("light_color", light.getColor().x, light.getColor().y, light.getColor().z);
	shader.setUniform3f("light_position", light.getPosition().x, light.getPosition().y, light.getPosition().z);
	shader.setUniform3f("view_position", camera.getPosition().x, camera.getPosition().y, camera.getPosition().z);
	shader.setUniformMat4f("view", camera.getViewMatrix());
	shader.setUniformMat4f("projection", camera.getProjectionMatrix());


	for (auto& pair : entities) {
		const TexturedModel* model = pair.first;
		std::vector<Entity>& batch = pair.second;

		// 2. MODEL-SPECIFIC BINDING (Happens once per group)
		glBindVertexArray(model->getRawModel().getVaoID());
		glActiveTexture(GL_TEXTURE0);
		model->getTexture().bind();
		shader.setUniform1f("shininess", model->getShininess());
		shader.setUniform1f("glossiness", model->getGlossiness());


		if(debugRenderMode) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Wireframe mode for debugging
		} else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Normal fill mode
		}

		for (const Entity& entity : batch) {
			// 3. INSTANCE-SPECIFIC BINDING (Only the matrix changes)
			shader.setUniformMat4f("model", createTransformationMatrix(entity.position, entity.rotation, entity.scale));

			// DRAW
			glDrawArrays(GL_TRIANGLES, 0, model->getRawModel().getVertexCount());
		}
		// Unbind once after the entire batch is done
		glBindVertexArray(0);
	}
	entities.clear(); // Clear entities after rendering to prepare for the next frame
}
void MasterRenderer::prepare() {
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void MasterRenderer::cleanUp() {
	shader.deleteShader();
}