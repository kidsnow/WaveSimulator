#include "Application.h"


int main()
{
	Application* app = new Application();

	if (!app->Initialize())
	{
		return -1;
	}

	app->Run();

	delete app;

	return 0;
}