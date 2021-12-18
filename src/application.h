#pragma once

class Camera;
class GLFWwindow;
class GridRenderer;

class Application
{
public:
	Application();
	~Application();

public:
	bool Initialize();
	void Run();

private:
	static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
	static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

public:
private:
	double xposPrev_, yposPrev_;
	Camera* camera_;
	GLFWwindow* window_;
	GridRenderer* renderer_;
};