#pragma once

#include <vector>


class Camera;
class GLFWwindow;
class Grid;
class GridRenderer;
class Renderable;
class WaveSimulator;

class Application
{
public:
	Application();
	~Application();

private:
	static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
	static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

public:
	bool Initialize();
	void Run();

private:
	void generateAxisRenderable();
	void generateGridRenderables(Grid* grid);

public:
private:
	double xposPrev_, yposPrev_;
	Camera* camera_;
	GLFWwindow* window_;
	Grid* grid_;
	GridRenderer* renderer_;
	Renderable* axisRenderable_;
	std::vector<Renderable*> gridRenderables_;
	WaveSimulator* waveSimulator_;
};