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

	registerAxis();

	return true;
}

void GridRenderer::registerAxis()
{
	Axis axis;

	Renderable* axisRenderable = new Renderable();
	
	axisRenderable->SetPrimitiveType(PrimitiveType::Lines);
	axisRenderable->UpdateVBO(VBOType::Position, 6, 3 * sizeof(float), axis.axisPosition_);
	axisRenderable->UpdateVBO(VBOType::Color, 6, 3 * sizeof(float), axis.axisColor_);
	axisRenderable->UpdateVBO(VBOType::Index, 6, sizeof(unsigned int), axis.axisIndices_);

	renderables_.push_back(axisRenderable);
}

void GridRenderer::RegisterGrid(Grid* grid)
{
	for (int i = 0; i < grid->GetBufferCount(); i++)
	{
		generateRenderableFromGridBuffer(
			grid->GetGridSize(),
			grid->GetBufferAt(i)
		);
	}
}

void GridRenderer::generateRenderableFromGridBuffer(int gridSize, GridBuffer* gridBuffer)
{
	Renderable* gridRenderable = new Renderable();

	gridRenderable->SetPrimitiveType(PrimitiveType::Lines);
	int elementCount = gridSize * (gridSize + 2);

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
		renderable->Bind();
		glDrawElements(
			renderable->GetPrimitiveTypeInGLEnum(),
			renderable->GetElementCount(),
			GL_UNSIGNED_INT, 0);
	}
}