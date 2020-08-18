#include <SFML/Graphics.hpp>
#include <array>
#include <iostream>
#include <cstdlib>
#include <typeinfo>
#include "Globals.h"

#include "Tetromino.h"


int GetColorInt(Tetromino tetromino)
{
    if (tetromino.m_type == TetrominoType::I) return 1;
    if (tetromino.m_type == TetrominoType::O) return 2;
    if (tetromino.m_type == TetrominoType::T) return 3;
    if (tetromino.m_type == TetrominoType::S) return 4;
    if (tetromino.m_type == TetrominoType::Z) return 5;
    if (tetromino.m_type == TetrominoType::J) return 6;
    if (tetromino.m_type == TetrominoType::L) return 7;

}

TetrominoType GetTypeFromNumeration(int number)
{
    switch (number) {
    case 0: return TetrominoType::I;
    case 1: return TetrominoType::O;
    case 2: return TetrominoType::T;
    case 3: return TetrominoType::S;
    case 4: return TetrominoType::Z;
    case 5: return TetrominoType::J;
    case 6: return TetrominoType::L;
    }
}

static bool CheckGameOver(Tetromino curr)
{
    // it should be game over if there is no where to fit the tetromino.
    for (int y = 0; y < curr.m_size; y++)
    {
        for (int x = 0; x < curr.m_size; x++)
        {
            if (curr.m_arr[y][x] == 0) continue;
            int pos = (x + curr.posX) + (y + curr.posY) * s_GameBoardWidth;
            if (s_PlayingArea[pos] && curr.m_landed)
            {
                //std::cout << "Game over " << std::endl;
                s_GameOver = true;
            }
        }
    }
    return true;
}


Tetromino CreateTetromino()
{
    std::cout << "Creating new" << std::endl;
    int random = rand() % 7;
    TetrominoType type = GetTypeFromNumeration(random);
    Tetromino tetromino(type);
    return tetromino;
}

static void CommitBlock(const Tetromino& tetromino)
{
    int txc = tetromino.posX;
    int tyc = tetromino.posY + 1;


    for (int y = 0; y < tetromino.m_size; y++)
    {
        for (int x = 0; x < tetromino.m_size; x++)
        {
            if (tetromino.m_arr[y][x])
            {

                int xc = txc + x;
                int yc = tyc + y;
                int pos = xc + yc  * s_GameBoardWidth;

                if (yc + 1 > s_GameBoardHeight)
                {
                    std::cout << "[WARNING] : gameborad height out of bounds" << std::endl;
                    continue;
                }
          
                // why only 2 works?? rest paints empty colour.
                s_PlayingArea[pos] = 2;
                
            }
        }
    }

}

static void ClearRow(sf::RenderWindow& window)
{
    for (int y = 0; y < s_GameBoardHeight; y++)
    {
        int count = 0;
        for (int x = 0; x < s_GameBoardWidth; x++)
        {
            int block = s_PlayingArea[x + y * s_GameBoardWidth];
            if (block) count += 1;
            if (count == s_GameBoardWidth)
            {
                std::cout << " y "<< y << std::endl;
                for (int x = 0; x < s_GameBoardWidth; x++) {
                    int i = y;
                    int j = 0;
                    while (j < i)
                    {
                        s_PlayingArea[x + (y - j) * s_GameBoardWidth] = s_PlayingArea[x + (y -j -1) * s_GameBoardWidth];
                        j++;

                    }
                    /*s_PlayingArea[x + y * s_GameBoardWidth] = s_PlayingArea[x + (y - 1) * s_GameBoardWidth];
                    s_PlayingArea[x + (y - 1) * s_GameBoardWidth] = s_PlayingArea[x + (y - 2) * s_GameBoardWidth];
                    s_PlayingArea[x + (y - 2) * s_GameBoardWidth] = s_PlayingArea[x + (y - 3) * s_GameBoardWidth];
                    s_PlayingArea[x + (y - 3) * s_GameBoardWidth] = s_PlayingArea[x + (y - 4) * s_GameBoardWidth];
                    s_PlayingArea[x + (y - 4) * s_GameBoardWidth] = s_PlayingArea[x + (y - 5) * s_GameBoardWidth];
                    s_PlayingArea[x + (y - 5) * s_GameBoardWidth] = s_PlayingArea[x + (y - 6) * s_GameBoardWidth];
                    s_PlayingArea[x + (y - 6) * s_GameBoardWidth] = s_PlayingArea[x + (y - 7) * s_GameBoardWidth];
                    s_PlayingArea[x + (y - 7) * s_GameBoardWidth] = s_PlayingArea[x + (y - 8) * s_GameBoardWidth];
                    s_PlayingArea[x + (y - 8) * s_GameBoardWidth] = s_PlayingArea[x + (y - 9) * s_GameBoardWidth];
                    s_PlayingArea[x + (y - 9) * s_GameBoardWidth] = s_PlayingArea[x + (y - 10) * s_GameBoardWidth];
                    s_PlayingArea[x + (y - 10) * s_GameBoardWidth] = s_PlayingArea[x + (y - 11) * s_GameBoardWidth];
                    s_PlayingArea[x + (y - 11) * s_GameBoardWidth] = s_PlayingArea[x + (y - 12) * s_GameBoardWidth];
                    s_PlayingArea[x + (y - 12) * s_GameBoardWidth] = s_PlayingArea[x + (y - 13) * s_GameBoardWidth];
                    s_PlayingArea[x + (y - 13) * s_GameBoardWidth] = s_PlayingArea[x + (y - 14) * s_GameBoardWidth];*/
                }    
            }
        }
    }
}

static void DrawGameBoard(sf::RenderWindow& window)
{
    sf::RectangleShape rect(sf::Vector2f(block_size, block_size));

    sf::Text text;
    text.setFont(s_Font);
    text.setFillColor(sf::Color(255, 255, 255));
    text.setCharacterSize(14);

    for (int y = 0; y < s_GameBoardHeight; y++)
    {
        for (int x = 0; x < s_GameBoardWidth; x++)
        {
            float cx = x * block_size;
            float cy = y * block_size;
            int block = s_PlayingArea[x + y * s_GameBoardWidth];
            if (block)
            {
                //colours if the s_PlayingArea == 2
                rect.setPosition(sf::Vector2f(cx, cy));
                rect.setOutlineThickness(3);
                rect.setFillColor(s_Colors[block]);
                rect.setOutlineColor(sf::Color(250, 150, 100));
                window.draw(rect);
            }
            else
            {
                rect.setPosition(sf::Vector2f(cx, cy));
                rect.setOutlineThickness(3);
                rect.setFillColor(sf::Color::Black);
                rect.setOutlineColor(sf::Color::White);

                window.draw(rect);

                text.setPosition(sf::Vector2f(cx, cy));
                std::string string = std::to_string(x) + ", " + std::to_string(y);
                text.setString(string);
                window.draw(text);
            }
        }
    }
}

static void DrawPoints(sf::RenderWindow& window, int points)
{
    sf::Text text;
    text.setFont(s_Font);
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(30);
    text.setPosition(900, 50);
    std::string string = "POINTS : " + std::to_string(points);
    text.setString(string);
    window.draw(text);
}


int main()
{
    srand((unsigned int)time(NULL));

    s_Font.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf");

    sf::RenderWindow window(sf::VideoMode(width, height), "Tetris");

    memset(s_PlayingArea.data(), 0, sizeof(s_PlayingArea));

    Tetromino current_tetromino = CreateTetromino();

    sf::Clock clock;

    float last_time = clock.getElapsedTime().asSeconds();

    int points = 0;

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Left)
                {
                    current_tetromino.posX -= cell_size;

                    if (!current_tetromino.CheckBounds()) current_tetromino.posX += cell_size;
                }

                if (event.key.code == sf::Keyboard::Right)
                {
                    current_tetromino.posX += cell_size;

                    if (!current_tetromino.CheckBounds()) current_tetromino.posX -= cell_size;
                }

                if (event.key.code == sf::Keyboard::Down)
                {
                    current_tetromino.MoveDown(cell_size);
                }

                if (event.key.code == sf::Keyboard::Up)
                {
                    current_tetromino.Rotate_HardCoded(current_tetromino.m_rotation_state);
                }

                if (event.key.code == sf::Keyboard::Space)
                {
                    
                }
            }
        }

        window.clear(sf::Color::Black);

        DrawGameBoard(window);
        current_tetromino.Draw(window);
        ClearRow(window);
        DrawPoints(window, points); 
        CheckGameOver(current_tetromino);


        float now = clock.getElapsedTime().asSeconds();
        if (now - last_time >= 0.7f)
        {
            current_tetromino.MoveDown(cell_size);
            last_time = now;
        } 

        if (current_tetromino.m_landed && !s_GameOver)
        {
            ++points;
            CommitBlock(current_tetromino);
            if (current_tetromino.posY <= 0 && current_tetromino.m_landed) s_GameOver = true;
            if (!s_GameOver) current_tetromino = CreateTetromino();
        }

        if (s_GameOver)
        {
            sf::Text text;
            text.setFont(s_Font);
            text.setFillColor(sf::Color::Red);
            text.setCharacterSize(70);
            text.setPosition(450, 50);
            std::string string = "Game Over";
            text.setString(string);
            window.draw(text);
            current_tetromino.m_color = sf::Color::Transparent;
        }
        window.display();

    }
    
    return 0;
}