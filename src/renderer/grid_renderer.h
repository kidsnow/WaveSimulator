#pragma once

class Camera;
class Grid;
class Shader;

class GridRenderer
{
public:
	GridRenderer();
	~GridRenderer();

public:
	bool Initialize();
	void Render(Camera* camera, Grid* grid);

private:
	Shader* shader_;
	unsigned int vao_;
	unsigned int vbo_[3];
	float* axisPosition_;
	float* axisColor_;
	unsigned int* axisIndices_;
};