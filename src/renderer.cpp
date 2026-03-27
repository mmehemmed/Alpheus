#include "renderer.h"

void Renderer::prepare() {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}
void Renderer::render(const RawModel& model,const Shader& shader, const Texture& texture) {
	shader.use();
	glUniform1i(glGetUniformLocation(shader.ID, "texture_sampler"), 0);

	glActiveTexture(GL_TEXTURE0);
	texture.bind();

	glBindVertexArray(model.getVaoID());
	glDrawElements(GL_TRIANGLES, model.getVertexCount(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}