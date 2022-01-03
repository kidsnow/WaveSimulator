#include "renderable.h"

#include <iostream>
#include <glad/glad.h>


Renderable::Renderable() :
	elementCount_(0),
	primitiveType_(PrimitiveType::Triangles)
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

void Renderable::UpdateVBO(VBOType type, int elementCount, int elementSize, void* buffer)
{
	int index = static_cast<int>(type);

	glBindVertexArray(vao_);

	if (type == VBOType::Position || type == VBOType::Color)
	{
		glBindBuffer(GL_ARRAY_BUFFER, vbo_[index]);
		// Compute shader���� buffer�� ��� �����ϸ� �̰� STATIC�̾���ϳ� DYNAMIC�̾���ϳ�...?
		glBufferData(GL_ARRAY_BUFFER, elementCount * elementSize, buffer, GL_STATIC_DRAW);
		glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, 0, (void*)nullptr);
		glEnableVertexAttribArray(index);
	}
	else if (type == VBOType::Index)
	{
		elementCount_ = elementCount;
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_[index]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementCount_ * elementSize, buffer, GL_STATIC_DRAW);
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Renderable::Bind()
{
	glBindVertexArray(vao_);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_[static_cast<int>(VBOType::Index)]);
}