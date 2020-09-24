#pragma once

#include <string>

class Application
{
public:
	Application(const std::string& name);
	~Application();

	static Application& GetApplication();
	void Run();

private:

};

