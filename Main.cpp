#include <SFML/Graphics.hpp>
#include <array>
#include <iostream>
#include <cstdlib>
#include <typeinfo>

#include "Tetromino.h"
#include "Button.h"
#include "Menu.h"
#include "TextBox.h"
#include "Layer.h"
#include <sqlite3.h>
#include "Database.h"

static Layer* s_CurrentLayer = nullptr;
static sf::RenderWindow* s_Window = nullptr;
static Database* s_Database = nullptr;

static void DrawMainWindow(unsigned int Window_Width, unsigned int Window_Height)
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

sf::RenderWindow& GetWindow()
{
    return *s_Window;
}

Database& GetDatabase()
{
	return *s_Database;
}

static void Init()
{
    s_Window = new sf::RenderWindow(sf::VideoMode(Window_Width, Window_Height), "Tetris");

    // Initialize fonts
    s_Arcade_Font = new sf::Font();
    s_Arcade_Font->loadFromFile("prstart.ttf");

	/*Database init here*/
    s_Database = new Database();
    s_Database->OnInit();
    s_Database->CreateScoreTable();
    s_Database->GetScoreList();
}

static void Shutdown()
{
    delete s_Arcade_Font;

    // Destroy window
    delete s_Window;
    delete s_Database;
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

void SetLayer(Layer* layer)
{
    if (s_CurrentLayer)
        s_CurrentLayer->OnShutdown();

    delete s_CurrentLayer;

    s_CurrentLayer = layer;
    s_CurrentLayer->OnInit();
}

int main()
{
    srand((unsigned int)time(NULL));

    Init();

    //CreateAndSetLayer<MainMenuLayer>();
    SetLayer(new MainMenuLayer());

    DrawMainWindow(Window_Width, Window_Height);

    Shutdown();

    return 0;
}