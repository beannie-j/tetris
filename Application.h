#pragma once

#include <string>
#include "Database.h"
#include "Sound.h"
#include "Layer.h"

class Application
{
public:
	Application() = default;
	Application(const std::string& name);
	~Application();

	Layer* s_CurrentLayer = nullptr;
	sf::RenderWindow* s_Window = nullptr;
	Database* s_Database = nullptr;
	Sound* s_Sound = nullptr;

	void DrawMainWindow(unsigned int Window_Width, unsigned int Window_Height);
	void Init();
	void Shutdown();
	void SetLayer(Layer* layer);
	void Run();

	sf::RenderWindow& GetWindow();
	Database& GetDatabase();
	Sound& GetSound();

	void test();

private:

};

