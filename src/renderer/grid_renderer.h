#pragma once

#include <vector>

class Camera;
class Grid;
class GridBuffer;
class Shader;
class Renderable;

struct Axis
{
	float axisPosition_[18] = {
		0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	};

	float axisColor_[18] = {
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f
	};

	unsigned int axisIndices_[6] = {
		0, 1,
		2, 3,
		4, 5
	};
};

class GridRenderer
{
public:
	GridRenderer();
	~GridRenderer();

public:
	bool Initialize();
	void RegisterGrid(Grid* grid);
	void Render(Camera* camera);

private:
	void registerAxis();
	void generateRenderableFromGridBuffer(int gridSize, GridBuffer* gridBuffer);

private:
	Shader* shader_;
	std::vector<Renderable*> renderables_;
};