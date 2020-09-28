#pragma once
#include <string>
#include "Layer.h"
#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>
#include "Database.h"
#include "Sound.h"

class Application
{
public:
	Application(const std::string& name);
	~Application();

	Layer* s_CurrentLayer = nullptr;
	sf::RenderWindow* s_Window = nullptr;
	Database* s_Database = nullptr;
	Sound* s_Sound = nullptr;

	static Application& GetApplication();
	void Run();
	void Init();
	void Shutdown();

	void DrawMainWindow(unsigned int Window_Width, unsigned int Window_Height);

	void SetLayer(Layer* layer);
	Sound& GetSound();
	sf::RenderWindow& GetWindow();
	Database& GetDatabase();

private:

};

