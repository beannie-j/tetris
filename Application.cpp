#include "Application.h"

static Application* s_Instance = nullptr;

Application::Application(const std::string& name)
{
	s_Instance = this;
}

Application& Application::GetApplication()
{
	//assert(s_Instance);
	return *s_Instance;
}

void Application::Run()
{
}

