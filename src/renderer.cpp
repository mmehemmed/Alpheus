#include "renderer.h"

void Renderer::prepare() {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}
void Renderer::render(const RawModel& model,const Shader& shader) {
	shader.use();
	glBindVertexArray(model.vaoID);
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_TRIANGLES, 0, model.vertexCount);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
}