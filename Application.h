#pragma once

class GLFWwindow;

class Application
{
public:
	Application();
	~Application();

public:
	bool Initialize();
	void Run();

private:

private:
	GLFWwindow* window_;
};