#pragma once

#include <glm/glm.hpp>
#include <vector>

struct GridElement
{
	GridElement() : x(0.0), y(0.0), z(0.0), w(1.0) {}
	~GridElement() {}
	float x, y, z, w;
};

class GridBuffer
{
public:
	GridBuffer(int gridSize, float gridLength);
	~GridBuffer();

public:
	void* GetBufferPointer();

private:
	std::vector<GridElement> elements_;
};

class Grid
{
public:
	Grid(int gridSize, float gridLength);
	~Grid();

public:
	int GetGridSize();
	float GetGridLength();
	int GetBufferCount();
	GridBuffer* GetBufferAt(int index);

private:
	int gridSize_;
	float gridLength_;
	// 3 for calculation, 1 for rendering.
	const static int bufferCount_ = 4;
	// Index of buffer in use for rendering.
	int frontBufferIndex_;
	std::vector<GridBuffer*> buffers_;
};