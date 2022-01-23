#include "renderable.h"

#include <iostream>
#include <glad/glad.h>

#include "shader.h"


Renderable::Renderable() :
	elementCount_(0),
	primitiveType_(PrimitiveType::Triangles),
	color_(0.0f, 0.0f, 0.0f),
	hasColor_(false)
{
	glGenVertexArrays(1, &vao_);
	glGenBuffers(static_cast<int>(VBOType::TypeCount), vbo_);
}

Renderable::~Renderable()
{
}

int Renderable::GetElementCount()
{
	return elementCount_;
}

PrimitiveType Renderable::GetPrimitiveType()
{
	return primitiveType_;
}

unsigned int Renderable::GetPrimitiveTypeInGLEnum()
{
	if (primitiveType_ == PrimitiveType::Lines)
		return GL_LINES;
	else if (primitiveType_ == PrimitiveType::Triangles)
		return GL_TRIANGLES;

	return GL_NONE;
}

void Renderable::SetPrimitiveType(PrimitiveType type)
{
	primitiveType_ = type;
}

void Renderable::SetColor(glm::vec3 color)
{
	color_ = color;
	hasColor_ = true;
}

void Renderable::UpdateVBO(VBOType type, int elementCount, int componentCount, int componentSize, void* buffer)
{
	int index = static_cast<int>(type);

	glBindVertexArray(vao_);

	if (type == VBOType::Position || type == VBOType::Color)
	{
		glBindBuffer(GL_ARRAY_BUFFER, vbo_[index]);
		// Compute shader에서 buffer값 계속 수정하면 이게 STATIC이어야하나 DYNAMIC이어야하나...?
		glBufferData(GL_ARRAY_BUFFER, elementCount * componentCount * componentSize, buffer, GL_STATIC_DRAW);
		glVertexAttribPointer(index, componentCount, GL_FLOAT, GL_FALSE, 0, (void*)nullptr);
		glEnableVertexAttribArray(index);
	}
	else if (type == VBOType::Index)
	{
		elementCount_ = elementCount;
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_[index]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementCount_ * componentCount * componentSize, buffer, GL_STATIC_DRAW);
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Renderable::Bind(Shader* shader)
{
	if (hasColor_)
	{
		shader->SetInteger("hasColor", 1);
		shader->SetVector3f("color", color_);
	}
	else
	{
		shader->SetInteger("hasColor", 0);
	}

	glBindVertexArray(vao_);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_[static_cast<int>(VBOType::Index)]);
}