#include "Application.h"
#include "../../Layers/src/MainMenuLayer.h"
#include "SFML/Graphics.hpp"
#include <string>

static Application* s_Instance = nullptr;

const float Application::block_size = 40.f;
int Application::Window_Width = 30 * (int)block_size; 
int Application::Window_Height = 30 * (int)block_size;
int Application::s_shift = 7;
std::string Application::s_Username = "";

Application::Application(const std::string& name)
{
	s_Instance = this;
}

Application::~Application()
{
}

Application& Application::GetApplication()
{
	//assert(s_Instance);
	return *s_Instance;
}

void Application::Run()
{
    SetLayer(new MainMenuLayer());
    DrawMainWindow(Window_Width, Window_Height);
}

void Application::DrawMainWindow(unsigned int Window_Width, unsigned int Window_Height)
{
    while (s_Window->isOpen())
    {
        sf::Event event;
        while (s_Window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                s_Window->close();

            s_CurrentLayer->OnEvent(event);
        }

        s_Window->clear(sf::Color::Black);

        s_CurrentLayer->OnUpdate();

        s_Window->display();
    }
}

void Application::Init()
{
    srand((unsigned int)time(NULL));

    s_Window = new sf::RenderWindow(sf::VideoMode(Window_Width, Window_Height), "Tetris");
    // Initialize fonts
    s_Arcade_Font = new sf::Font();
    if (!s_Arcade_Font->loadFromFile("resources/prstart.ttf"))
    {
        s_Arcade_Font->loadFromFile("C:\\Windows\\Fonts\\Arial.ttf");
    }

    s_Database = new Database();
    s_Database->OnInit();
    s_Database->CreateScoreTable();
    s_Database->GetScoreList();

    s_Sound = new Sound();
    s_Sound->Init();
}

void Application::Shutdown()
{
    delete s_Arcade_Font;
    delete s_Window;
    delete s_Database;
    delete s_Sound;
}

void Application::SetLayer(Layer* layer)
{
    if (s_CurrentLayer)
        s_CurrentLayer->OnShutdown();

    delete s_CurrentLayer;

    s_CurrentLayer = layer;
    s_CurrentLayer->OnInit();
}
