#include "renderer.h"


void Renderer::prepare() {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void Renderer::render(const Camera& camera,const Light& light,const Entity& entity,const Shader& shader, bool debugRenderMode) {
	shader.use();
	shader.setUniform1i("texture_sampler", 0); // Set the texture uniform to use texture unit 0
	shader.setUniform3f("light_color", light.getColor().x, light.getColor().y, light.getColor().z);
	shader.setUniform3f("light_position", light.getPosition().x, light.getPosition().y, light.getPosition().z);
	shader.setUniform1f("shininess", entity.getModel().getShininess());
	shader.setUniform1f("glossiness", entity.getModel().getGlossiness());
	shader.setUniform3f("view_position", camera.getPosition().x, camera.getPosition().y, camera.getPosition().z);

	glActiveTexture(GL_TEXTURE0);
	entity.getModel().getTexture().bind();

	shader.setUniformMat4f("view", camera.getViewMatrix());
	shader.setUniformMat4f("projection", camera.getProjectionMatrix());
	shader.setUniformMat4f("model", glm::mat4(1.0f));
	glBindVertexArray(entity.getModel().getRawModel().getVaoID());
	if(debugRenderMode) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	glDrawElements(GL_TRIANGLES, entity.getModel().getRawModel().getVertexCount(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}