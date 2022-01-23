#pragma once

#include <vector>

class Camera;
class Grid;
class GridBuffer;
class Shader;
class Renderable;

class GridRenderer
{
public:
	GridRenderer();
	~GridRenderer();

public:
	bool Initialize();
	void Render(Camera* camera);
	void RegisterRenderable(Renderable* renderable);
	void ClearRenderables();

private:
	Shader* shader_;
	std::vector<Renderable*> renderables_;

	Renderable* axisRenderable_;
	Renderable* gridRenderable_;
};