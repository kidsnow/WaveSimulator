#include "grid_renderer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "camera.h"
#include "shader.h"

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

	axisPosition_ = new float[18]
	{
		0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	};

	axisColor_ = new float[18]
	{
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f
	};

	axisIndices_ = new unsigned int[6]
	{
		0, 1,
		2, 3,
		4, 5
	};

	glGenVertexArrays(1, &vao_);
	glBindVertexArray(vao_);

	glGenBuffers(3, vbo_);
	{
		glGenBuffers(1, &vbo_[0]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * 6, axisPosition_, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(0);
	}

	{
		GLuint vbo;
		glGenBuffers(1, &vbo_[1]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * 6, axisColor_, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(1);
	}

	{
		GLuint vbo;
		glGenBuffers(1, &vbo_[2]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_[2]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * 6, axisIndices_, GL_STATIC_DRAW);
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return true;
}

void GridRenderer::Render(Camera* camera, Grid* grid)
{
	shader_->Use();

	glm::mat4 viewMat = camera->GetViewMatrix();
	glm::mat4 projMat = camera->GetProjectionMatrix();
	
	shader_->SetMatrix4("viewProjection", projMat * viewMat);

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glBindVertexArray(vao_);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_[2]);

	glDrawElements(GL_LINES, 6, GL_UNSIGNED_INT, 0);
}