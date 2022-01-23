#pragma once

#include <glm/glm.hpp>


class Shader;

enum class VBOType
{
	Position,
	Color,
	Index,
	TypeCount
};

enum class PrimitiveType
{
	Lines,
	Triangles
};

class Renderable
{
public:

public:
	Renderable();
	~Renderable();

public:
	int GetElementCount();
	PrimitiveType GetPrimitiveType();
	unsigned int GetPrimitiveTypeInGLEnum();
	void SetPrimitiveType(PrimitiveType type);
	void SetColor(glm::vec3 color);
	void UpdateVBO(VBOType type, int elementCount, int componentCount, int componentSize, void* buffer);
	void Bind(Shader* shader);

private:
	int elementCount_;
	PrimitiveType primitiveType_;
	glm::vec3 color_;
	bool hasColor_;
	unsigned int vao_;
	unsigned int vbo_[static_cast<int>(VBOType::TypeCount)];
};