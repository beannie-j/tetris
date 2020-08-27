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


static Layer* s_CurrentLayer = nullptr;
static sf::RenderWindow* s_Window = nullptr;

static void DrawScoreBoardWindow(unsigned int Window_Width, unsigned int Window_Height);

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

static void DrawScoreBoardWindow(unsigned int Window_Width, unsigned int Window_Height)
{
    sf::RenderWindow scoreBoardWindow(sf::VideoMode(Window_Width, Window_Height), "Scores");
    scoreBoardWindow.setFramerateLimit(60);
    sf::Vector2i mouse_position;
    Button backButton(100.f, 100.f, 200.f, 50.f, *s_Arcade_Font, "BACK", 30, sf::Color::Blue, sf::Color::Green);

    auto temp = s_priority_queue;
    int rank = 1;

    while (!temp.empty()) {
        std::string entry = std::to_string(rank) + " " + temp.top().first + " " + std::to_string(temp.top().second);
        temp.pop();
        rank += 1;
        std::cout << entry << std::endl;
    }

    while (scoreBoardWindow.isOpen())
    {
        sf::Event event;
        while (scoreBoardWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                scoreBoardWindow.close();
                // draw main window
                DrawMainWindow(Window_Width, Window_Height);
            }

            if (event.key.code == sf::Keyboard::Escape)
            {
                scoreBoardWindow.close();
                // draw main window
                DrawMainWindow(Window_Width, Window_Height);
            }
        }
        // Clear the whole window before rendering a new frame
        scoreBoardWindow.clear();
        mouse_position = sf::Mouse::getPosition(scoreBoardWindow);

        int order = 1;

        sf::Text boardEntry1;
        boardEntry1.setFont(*s_Arcade_Font);
        boardEntry1.setFillColor(sf::Color::White);
        boardEntry1.setPosition(Window_Width / 4, 50 * order++);
        boardEntry1.setString("1");
        scoreBoardWindow.draw(boardEntry1);

        sf::Text boardEntry2;
        boardEntry2.setFont(*s_Arcade_Font);
        boardEntry2.setFillColor(sf::Color::White);
        boardEntry2.setPosition(Window_Width / 4, 50 * order++);
        boardEntry2.setString("2");
        scoreBoardWindow.draw(boardEntry2);

        sf::Text boardEntry3;
        boardEntry3.setFont(*s_Arcade_Font);
        boardEntry3.setFillColor(sf::Color::White);
        boardEntry3.setPosition(Window_Width / 4, 50 * order);
        boardEntry3.setString("3");
        scoreBoardWindow.draw(boardEntry3);

        backButton.DrawButton(scoreBoardWindow);
        backButton.GetPressed(mouse_position);
        scoreBoardWindow.display();

        if (backButton.m_buttonState == PRESSED)
        {
            scoreBoardWindow.close();
            // draw main window
            DrawMainWindow(Window_Width, Window_Height);
        }
    }
}


sf::RenderWindow& GetWindow()
{
    return *s_Window;
}

static void Init()
{
    s_Window = new sf::RenderWindow(sf::VideoMode(Window_Width, Window_Height), "Tetris");

    // Initialize fonts
    s_Arcade_Font = new sf::Font();
    s_Arcade_Font->loadFromFile("prstart.ttf");
}

static void Shutdown()
{
    delete s_Arcade_Font;

    // Destroy window
    delete s_Window;
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

    s_Font.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf");
    // font made by [ codeman38 | cody@zone38.net | http://www.zone38.net/ ] 

    Init();

    CreateAndSetLayer<MainMenuLayer>();

    s_priority_queue.push(std::make_pair("Jeannie", 100));
    s_priority_queue.push(std::make_pair("Jem", 40));
    s_priority_queue.push(std::make_pair("Susie", 55));

    DrawMainWindow(Window_Width, Window_Height);

    Shutdown();

    return 0;
}