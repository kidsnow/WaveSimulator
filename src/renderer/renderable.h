#pragma once

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
	void UpdateVBO(VBOType type, int elementCount, int elementSize, void* buffer);
	void Bind();

private:
	int elementCount_;
	PrimitiveType primitiveType_;
	unsigned int vao_;
	unsigned int vbo_[static_cast<int>(VBOType::TypeCount)];
};