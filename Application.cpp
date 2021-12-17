#include "Application.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>


Application::Application()
{
}

Application::~Application()
{
	glfwTerminate();
}

bool Application::Initialize()
{
	if (!glfwInit())
	{
		return false;
	}

	window_ = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);

	if (!window_)
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(window_);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		return false;
	}

	return true;
}

void Application::Run()
{
	while (!glfwWindowShouldClose(window_))
	{
		glClearColor(0.0, 1.0, 1.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window_);
		glfwPollEvents();
	}
}