#include "application.h"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "camera.h"
#include "grid.h"
#include "renderer/grid_renderer.h"


Application::Application() :
	window_(nullptr),
	renderer_(nullptr),
	camera_(nullptr),
	xposPrev_(0.0),
	yposPrev_(0.0)
{
}

Application::~Application()
{
	glfwTerminate();
}

bool Application::Initialize()
{
	// glfw init.
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
		glfwSetWindowUserPointer(window_, this);
		glfwSetCursorPosCallback(window_, cursorPositionCallback);
		glfwSetScrollCallback(window_, scrollCallback);
		glfwSetKeyCallback(window_, keyCallback);
	}

	// GL init.
	{
		glfwMakeContextCurrent(window_);

		renderer_ = new GridRenderer();

		if (!renderer_)
		{
			return false;
		}

		if (!renderer_->Initialize())
		{
			return false;
		}
	}

	camera_ = new Camera();
	camera_->Rotate(glm::radians(45.f), glm::vec3(0.f, 0.f, 1.f));
	camera_->Rotate(glm::radians(-45.f), glm::vec3(1.f, 0.f, 0.f));
	camera_->SetProjectionMode(CameraProjectionMode::Perspective);
	camera_->SetFrustum(glm::vec2(4.f, 3.f), 1.f, 10.f);

	grid_ = new Grid(64, 1.0f);

	delete grid_;

	return true;
}

// Screen 좌측 상단이 원점.
void Application::cursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
	auto app = reinterpret_cast<Application*>(glfwGetWindowUserPointer(window));

	bool leftBtnPressed = false;
	bool rightBtnPressed = false;
	bool middleBtnPressed = false;

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		leftBtnPressed = true;
	}
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		rightBtnPressed = true;
	}
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS)
	{
		middleBtnPressed = true;
	}

	double xDiff = xpos - app->xposPrev_;
	double yDiff = ypos - app->yposPrev_;

	if (leftBtnPressed)
	{
		//printf("xDiff: %f\nyDiff: %f\n", xDiff, yDiff);
		app->camera_->Rotate(glm::radians(-xDiff*0.5), glm::vec3(0.0f, 0.0f, 1.0f));
		app->camera_->Rotate(glm::radians(-yDiff*0.5), glm::vec3(1.0f, 0.0f, 0.0f));
	}
	if (rightBtnPressed)
	{
		//printf("RIGHT:\t%f\t%f\n", xpos, ypos);
	}
	if (middleBtnPressed)
	{
		//printf("MIDDLE:\t%f\t%f\n", xpos, ypos);
	}

	app->xposPrev_ = xpos;
	app->yposPrev_ = ypos;
}

void Application::scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	auto app = reinterpret_cast<Application*>(glfwGetWindowUserPointer(window));

	app->camera_->Zoom(-yoffset * 0.5f);
}

void Application::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	auto app = reinterpret_cast<Application*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

void Application::Run()
{
	while (!glfwWindowShouldClose(window_))
	{
		renderer_->Render(camera_);
		glfwSwapBuffers(window_);
		glfwPollEvents();
	}
}