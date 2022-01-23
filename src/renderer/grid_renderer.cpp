#include "grid_renderer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "camera.h"
#include "shader.h"
#include "renderable.h"
#include "../grid.h"

GridRenderer::GridRenderer()
{
}

GridRenderer::~GridRenderer()
{

}

bool GridRenderer::Initialize()
{
	// Init GL API first.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		return false;
	}

	shader_ = new Shader();
	shader_->CompileRenderingShader("resource/shader/grid_shader.vert", "resource/shader/grid_shader.frag");

	return true;
}

void GridRenderer::RegisterRenderable(Renderable* renderable)
{
	renderables_.push_back(renderable);
}

void GridRenderer::ClearRenderables()
{
	renderables_.clear();
}

void GridRenderer::Render(Camera* camera)
{
	shader_->Use();

	glm::mat4 viewMat = camera->GetViewMatrix();
	glm::mat4 projMat = camera->GetProjectionMatrix();

	shader_->SetMatrix4("viewProjection", projMat * viewMat);

	glClearColor(0.4f, 0.4f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	for (auto renderable : renderables_)
	{
		renderable->Bind(shader_);
		glDrawElements(
			renderable->GetPrimitiveTypeInGLEnum(),
			renderable->GetElementCount(),
			GL_UNSIGNED_INT, 0);
	}
}