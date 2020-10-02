#pragma once
#include <string>
#include "../../Layers/src/Layer.h"
#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>
#include "../../util/src/Database.h"
#include "../../util/src/Sound.h"

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
	Sound& GetSound() { return *s_Sound; }
	sf::RenderWindow& GetWindow() { return *s_Window; }
	Database& GetDatabase() { return *s_Database; }

private:

};

