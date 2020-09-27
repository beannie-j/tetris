#include "Application.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sqlite3.h>


Application::Application(const std::string& name)
{
    Init();
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
    s_Window = new sf::RenderWindow(sf::VideoMode(Window_Width, Window_Height), "Tetris");

    // Initialize fonts
    s_Arcade_Font = new sf::Font();
    s_Arcade_Font->loadFromFile("resources/prstart.ttf");

    /*Database init here*/
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

template<typename T>
void CreateAndSetLayer()
{
    if (s_CurrentLayer)
        s_CurrentLayer->OnShutdown();

    delete s_CurrentLayer;

    s_CurrentLayer = new T();
    s_CurrentLayer->OnInit();
}

void Application::SetLayer(Layer* layer)
{
    if (s_CurrentLayer)
        s_CurrentLayer->OnShutdown();

    delete s_CurrentLayer;

    s_CurrentLayer = layer;
    s_CurrentLayer->OnInit();
}

sf::RenderWindow& Application::GetWindow()
{
	return *s_Window;
}

Database& Application::GetDatabase()
{
	return *s_Database;
}

Sound& Application::GetSound()
{
	return *s_Sound;
}

void Application::Run()
{
    srand((unsigned int)time(NULL));

    Init();
    //CreateAndSetLayer<MainMenuLayer>();
    SetLayer(new MainMenuLayer());
    DrawMainWindow(Window_Width, Window_Height);
    Shutdown();
}

void Application::test()
{
    std::cout << "test" << std::endl;
}

