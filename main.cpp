#include "AppWindow.h"
#include "InputSystem.h"
#include <exception>

int main()
{
	try
	{
		GraphicsEngine::create();
		InputSystem::create();
	}
	catch (...) 
	{ 
		throw std::exception("Failed to create {GraphicsEngine} and {InputSystem}. Erorr in {main()}.");
		return -1; 
	}

	try
	{
		AppWindow app;
		while (app.isRun());
	}
	catch (...) 
	{
		InputSystem::release();
		GraphicsEngine::release();
		throw std::exception("Failed to create a frame. Erorr in {AppWindow} pipeline.");
		return -1;
	}
	
	InputSystem::release();
	GraphicsEngine::release();

	return 0;
}