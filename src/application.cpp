#include "application.h"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "camera.h"
#include "grid.h"
#include "renderer/grid_renderer.h"
#include "renderer/renderable.h"


Application::Application() :
	window_(nullptr),
	renderer_(nullptr),
	camera_(nullptr),
	xposPrev_(0.0),
	yposPrev_(0.0),
	grid_(nullptr),
	axisRenderable_(nullptr)
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

	generateAxisRenderable();

	grid_ = new Grid(2, 1.0f);
	generateGridRenderables(grid_);

	return true;
}

void Application::generateAxisRenderable()
{
	float axisPosition[18] = {
		0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	};

	float axisColor[18] = {
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f
	};

	unsigned int axisIndices[6] = {
		0, 1,
		2, 3,
		4, 5
	};

	axisRenderable_ = new Renderable();

	axisRenderable_->SetPrimitiveType(PrimitiveType::Lines);
	axisRenderable_->UpdateVBO(VBOType::Position, 6, 3, sizeof(float), axisPosition);
	axisRenderable_->UpdateVBO(VBOType::Color, 6, 3, sizeof(float), axisColor);
	axisRenderable_->UpdateVBO(VBOType::Index, 6, 1, sizeof(unsigned int), axisIndices);
}

void Application::generateGridRenderables(Grid* grid)
{
	for (int i = 0; i < grid->GetBufferCount(); i++)
	{
		// Position buffer를 중간에서부터 읽어오는 로직 짜야 함.
		Renderable* gridRenderable = new Renderable();
		int gridSize = grid->GetGridSize();
		GridBuffer* gridBuffer = grid->GetBufferAt(i);

		gridRenderable->SetPrimitiveType(PrimitiveType::Lines);
		gridRenderable->SetColor(glm::vec3(1.0f, 1.0f, 0.2f));
		int positionElementCount = gridSize * gridSize;
		int positionElementSize = sizeof(GridElement);
		gridRenderable->UpdateVBO(
			VBOType::Position,
			positionElementCount,
			4, 4,
			gridBuffer->GetRenderBufferPointer()
		);

		// Generate grid index buffer.
		std::vector<unsigned int> indices;
		int indexElementCount = 4 * gridSize * (gridSize - 1);
		int indexElementSize = sizeof(unsigned int);
		indices.resize(indexElementCount);
		int counter = 0;

		for (int i = 0; i < gridSize; i++)
		{
			for (int j = 0; j < gridSize - 1; j++)
			{
				indices.push_back((i + 1) * gridSize + j);
				indices.push_back((i + 1) * gridSize + j + 1);
				indices.push_back((j + 1) * gridSize + i);
				indices.push_back((j + 2) * gridSize + i);
				counter += 4;
			}
		}

		gridRenderable->UpdateVBO(
			VBOType::Index,
			indexElementCount,
			1, indexElementSize,
			indices.data()
		);

		gridRenderables_.push_back(gridRenderable);
	}

	{
		int gridSize = 10;
		float gridLength = 1.0f;
		std::vector<glm::vec4> elements;
		elements.resize(gridSize * (gridSize + 2));

		for (int i = 0; i < gridSize + 2; i++)
		{
			for (int j = 0; j < gridSize; j++)
			{
				elements[i * gridSize + j].w = 1.0f;
			}
		}

		for (int i = 0; i < gridSize; i++)
		{
			elements[i].w = 0.0f;
			elements[gridSize * (gridSize + 1) + i].w = 0.0f;
		}

		float elementLength = gridLength / (gridSize - 1);
		for (int i = 0; i < gridSize; i++)
		{
			for (int j = 0; j < gridSize; j++)
			{
				int index = gridSize * (i + 1) + j;
				elements[index].x = j * elementLength;
				elements[index].y = i * elementLength;
			}
		}

		dummyGridRenderable_ = new Renderable();
		dummyGridRenderable_->SetPrimitiveType(PrimitiveType::Lines);
		dummyGridRenderable_->SetColor(glm::vec3(1.0f, 1.0f, 0.2f));
		int positionElementCount = gridSize * (gridSize + 2);
		int positionElementSize = sizeof(glm::vec4);
		dummyGridRenderable_->UpdateVBO(
			VBOType::Position,
			positionElementCount,
			4, sizeof(float),
			elements.data()
		);

		std::vector<unsigned int> indices;
		int indexElementCount = 4 * gridSize * (gridSize - 1);
		int indexElementSize = sizeof(unsigned int);
		indices.resize(indexElementCount);
		int counter = 0;

		for (int i = 0; i < gridSize; i++)
		{
			for (int j = 0; j < gridSize - 1; j++)
			{
				indices[counter++] = i * gridSize + j + gridSize;
				indices[counter++] = i * gridSize + j + 1 + gridSize;

				indices[counter++] = j * gridSize + i + gridSize;
				indices[counter++] = (j + 1) * gridSize + i + gridSize;
			}
		}

		dummyGridRenderable_->UpdateVBO(
			VBOType::Index,
			indexElementCount,
			1, sizeof(unsigned int),
			indices.data()
		);
	}
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
		//Renderable* gridRenderable = gridRenderables_[grid_->GetFrontBufferIndex()];
		//renderer_->RegisterRenderable(gridRenderable);
		renderer_->RegisterRenderable(dummyGridRenderable_);
		renderer_->RegisterRenderable(axisRenderable_);
		renderer_->Render(camera_);
		renderer_->ClearRenderables();
		glfwSwapBuffers(window_);
		glfwPollEvents();
	}
}