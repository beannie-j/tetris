#pragma once
#include <string>
#include <array>
#include "../../Layers/src/Layer.h"
#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>
#include "../../util/src/Database.h"
#include "../../util/src/Sound.h"

struct GameBoard
{
	inline static constexpr int Width = 10;
	inline static constexpr int Height = 17;
	inline static std::array<int, Width* Height> PlayingArea = {};
};

// how to make some member variables in Application const
class Application
{
public:
	Application(const std::string& name);
	~Application();

	Layer* s_CurrentLayer = nullptr;
	sf::RenderWindow* s_Window = nullptr;
	Database* s_Database = nullptr;
	Sound* s_Sound = nullptr;
	sf::Font* s_Arcade_Font = nullptr;

	static const float block_size;
	static int Window_Width;
	static int Window_Height;

	int s_Score = 0;
	static std::string s_Username;
	static int s_shift;

	static Application& GetApplication();

	sf::Clock clock;

	void Run();
	void Init();
	void Shutdown();

	void DrawMainWindow(unsigned int Window_Width, unsigned int Window_Height);

	void SetLayer(Layer* layer);
	Sound& GetSound() { return *s_Sound; }
	sf::RenderWindow& GetWindow() { return *s_Window; }
	Database& GetDatabase() { return *s_Database; }
	sf::Font& GetFont() { return *s_Arcade_Font; }

private:
	float m_LastFrameTime = 0.0f;
};

