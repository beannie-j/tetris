#include <SFML/Graphics.hpp>
#include <array>
#include <iostream>
#include <cstdlib>
#include <typeinfo>

#include "Tetromino.h"
#include "Button.h"
#include "Menu.h"
#include "TextBox.h"

int GetColorInt(Tetromino tetromino)
{
    if (tetromino.m_type == TetrominoType::I) return 2;
    if (tetromino.m_type == TetrominoType::O) return 3;
    if (tetromino.m_type == TetrominoType::T) return 4;
    if (tetromino.m_type == TetrominoType::S) return 5;
    if (tetromino.m_type == TetrominoType::Z) return 6;
    if (tetromino.m_type == TetrominoType::J) return 7;
    if (tetromino.m_type == TetrominoType::L) return 8;

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
    for (int y = 0; y < curr.m_size; y++)
    {
        for (int x = 0; x < curr.m_size; x++)
        {
            if (curr.m_arr[y][x] == 0) continue;
            int pos = (x + curr.posX) + (y + curr.posY) * GameBoard::Width;
            if (GameBoard::PlayingArea[pos] && curr.m_landed)
            {
                s_GameOver = true;
            }
        }
    }
    return true;
}

static Tetromino CreateTetromino()
{
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
                int pos = xc + yc  * GameBoard::Width;

                if (yc + 1 > GameBoard::Height)
                {
                    std::cout << "[WARNING] : gameborad height out of bounds" << std::endl;
                    continue;
                }
          
                GameBoard::PlayingArea[pos] = GetColorInt(tetromino);
                
            }
        }
    }

}

static void ClearRow(sf::RenderWindow& window)
{
    for (int y = 0; y < GameBoard::Height; y++)
    {
        int count = 0;
        for (int x = 0; x < GameBoard::Width; x++)
        {
            int block = GameBoard::PlayingArea[x + y * GameBoard::Width];
            if (block) count += 1;
            if (count == GameBoard::Width)
            {
                for (int x = 0; x < GameBoard::Width; x++) {
                    int i = y;
                    int j = 0;
                    while (j < i)
                    {
                        GameBoard::PlayingArea[x + (y - j) * GameBoard::Width] = GameBoard::PlayingArea[x + (y -j -1) * GameBoard::Width];
                        j++;

                    }
                }    
            }
        }
    }
}

static void DrawGameBoard_GameOver(sf::RenderWindow& window)
{
    sf::RectangleShape rect(sf::Vector2f(Tetromino::block_size, Tetromino::block_size));

    for (int y = 0; y < GameBoard::Height; y++)
    {
        for (int x = 0; x < GameBoard::Width; x++)
        {
            float cx = (x + s_shift) * Tetromino::block_size;
            float cy = (y + s_shift) * Tetromino::block_size;
            int block = GameBoard::PlayingArea[x + y * GameBoard::Width];
            if (block < 2)
            {
                rect.setPosition(sf::Vector2f(cx, cy));
                rect.setFillColor(sf::Color(139, 0, 0));
                rect.setOutlineColor(sf::Color(250, 150, 100));
                window.draw(rect);
            }
            
        }
    }
}

static void DrawGameBoard(sf::RenderWindow& window)
{
    sf::RectangleShape rect(sf::Vector2f(Tetromino::block_size, Tetromino::block_size));

    sf::Text text;
    text.setFont(s_Font);
    text.setFillColor(sf::Color(255, 255, 255));
    text.setCharacterSize(14);

    for (int y = 0; y < GameBoard::Height; y++)
    {
        for (int x = 0; x < GameBoard::Width; x++)
        {
            float cx = (x + s_shift) * Tetromino::block_size;
            float cy = (y + s_shift) * Tetromino::block_size;
            int block = GameBoard::PlayingArea[x + y * GameBoard::Width];
            if (block >= 2)
            {
                //colours if the s_PlayingArea == 2
                rect.setPosition(sf::Vector2f(cx, cy));
                //rect.setOutlineThickness(3);
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

static void DrawUsername(sf::RenderWindow& window)
{
    sf::Text text;
    text.setFont(s_Arcade_Font);
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(30);
    text.setPosition(700, 70);
    std::string string = "PLAYER : " + s_Username;
    text.setString(string);
    window.draw(text);
}

static void DrawPoints(sf::RenderWindow& window, int points)
{
    sf::Text text;
    text.setFont(s_Arcade_Font);
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(30);
    text.setPosition(700, 120);
    std::string string = "POINTS : " + std::to_string(points);
    text.setString(string);
    window.draw(text);

    if (s_GameOver)
    {
        text.setFillColor(sf::Color::Transparent);
    }
}

static void DrawTimer(sf::RenderWindow& window, sf::Clock clock)
{
    float last_time = clock.getElapsedTime().asSeconds();

    sf::Text text;
    text.setFont(s_Arcade_Font);
    text.setFillColor(sf::Color(107, 133, 255));
    text.setCharacterSize(200);
    text.setPosition(window.getSize().x / 2 - 100.f, window.getSize().y / 2 - 100.f);
    int timer = 3;

    float now = clock.getElapsedTime().asSeconds();

    if (now - last_time >= 1.0f)
    {
        while (timer >= 0)
        {
            timer -= 1;
        }
    }

    text.setString(std::to_string(timer));
    window.draw(text);
    clock.restart();
}

static void PlayTetris(unsigned int Window_Width, unsigned int Window_Height)
{
    sf::RenderWindow window(sf::VideoMode(Window_Width, Window_Height), "Tetris");
    memset(GameBoard::PlayingArea.data(), 0, sizeof(GameBoard::PlayingArea));

    Tetromino current_tetromino = CreateTetromino();

    sf::Clock clock;
    float last_time = clock.getElapsedTime().asSeconds();
    int points = 0;
    sf::Vector2i mouse_position;
    Button play_again_button(770.f, 400.f, 350.f, 50.f, s_Arcade_Font, "PLAY AGAIN", 30, sf::Color::Blue, sf::Color::Green);

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

        // draw the timer here only once.

        window.clear(sf::Color::Black);

        DrawTimer(window, clock);
        DrawGameBoard(window);
        current_tetromino.Draw(window);
        ClearRow(window);
        if (!s_GameOver)
        {
            DrawPoints(window, points);
            DrawUsername(window);
        }
        CheckGameOver(current_tetromino);

        mouse_position = sf::Mouse::getPosition(window);

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
            text.setFont(s_Arcade_Font);
            text.setFillColor(sf::Color(254, 0, 2));
            text.setCharacterSize(60);
            text.setPosition(450, 50);
            std::string string = "GAME OVER";
            text.setString(string);
            window.draw(text);
            current_tetromino.m_color = sf::Color::Transparent;

            //sf::RectangleShape red_rectangle(sf::Vector2f(Window_Width, Window_Height));
            //red_rectangle.setFillColor(sf::Color::Red);
            //window.draw(red_rectangle);

            DrawGameBoard_GameOver(window);

            sf::Text score_text;
            score_text.setFont(s_Arcade_Font);
            score_text.setFillColor(sf::Color::Yellow);
            score_text.setCharacterSize(60);
            score_text.setPosition(450, 150);
            std::string score_str = "SCORE : " + std::to_string(points);
            score_text.setString(score_str);
            window.draw(score_text);

            play_again_button.DrawButton(window);
            play_again_button.GetPressed(mouse_position);

            if (play_again_button.m_buttonState == PRESSED)
            {
                s_GameOver = false;
                window.close();
                PlayTetris(Window_Width, Window_Height);
            }
        }
        window.display();
    }
}

static void DrawPreGameWindow(unsigned int Window_Width, unsigned int Window_Height)
{
    sf::RenderWindow preGameWindow(sf::VideoMode(Window_Width, Window_Height), "Tetris");
    // Limit the framerate to 60 frames per second (this step is optional)
    preGameWindow.setFramerateLimit(60);
    TextBox textBox(s_Arcade_Font, Window_Width / 4, 150.f, 500.f, 65.f);
    sf::Vector2i mouse_position;
    Button playButton(Window_Width / 4 + 150, 300.f, 200.f, 50.f, s_Arcade_Font, "START", 30, sf::Color::Blue, sf::Color::Green);

    while (preGameWindow.isOpen())
    {
        sf::Event event;
        while (preGameWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                preGameWindow.close();

            if (event.type == sf::Event::TextEntered)
            {
                textBox.EnterText(event.text.unicode);
            }

            if (event.key.code == sf::Keyboard::Enter)
            {
                std::cout << "[Key] Enter, Username : " << textBox.getString() << std::endl;
                s_Username = textBox.getString();
                playButton.FillColor();
                preGameWindow.close();
                PlayTetris(Window_Width, Window_Height);
            }
        }
        // Clear the whole window before rendering a new frame
        preGameWindow.clear();
        mouse_position = sf::Mouse::getPosition(preGameWindow);

        // Draw some graphical entities
        sf::Text askNameText;
        askNameText.setFont(s_Arcade_Font);
        askNameText.setFillColor(sf::Color::White);
        askNameText.setCharacterSize(30);
        askNameText.setPosition(Window_Width / 4, 100);
        std::string string = "ENTER YOUR NAME :";
        askNameText.setString(string);
        preGameWindow.draw(askNameText);

        textBox.setDimensions(Window_Width / 4, 150.f, 500.f, 65.f);

        playButton.DrawButton(preGameWindow);
        //playButton.GetPressed(mouse_position);
        textBox.DrawTextBox(preGameWindow);

        preGameWindow.display();
    }
}

int main()
{
    srand((unsigned int)time(NULL));

    s_Font.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf");
    // font made by [ codeman38 | cody@zone38.net | http://www.zone38.net/ ] 
    s_Arcade_Font.loadFromFile("prstart.ttf");

    int Window_Width = 30 * Tetromino::block_size;
    int Window_Height = 30 * Tetromino::block_size;

    sf::RenderWindow main_menu_window(sf::VideoMode(Window_Width, Window_Height), "Menu");
    Menu menu(Window_Width, Window_Height - 200.f, s_Arcade_Font);

    sf::Vector2i mouse_position;
    while (main_menu_window.isOpen())
    {
        sf::Event event;
        while (main_menu_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                main_menu_window.close();

            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Up)
                {
                    menu.MoveUp();
                }

                if (event.key.code == sf::Keyboard::Down)
                {
                    menu.MoveDown();
                }

                if (event.key.code == sf::Keyboard::Enter)
                {
                    std::cout << "[Key] Enter\n";
                    switch (menu.GetPressedItem())
                    {
                    default:
                        break;
                    case 0:
                        std::cout << "[Key] Play Button pressed\n";
                        main_menu_window.close();
                        DrawPreGameWindow(Window_Width, Window_Height);
                        break;
                    case 1:
                        std::cout << "[Key] Scores Button pressed\n";
                        break;
                    case 2:
                        std::cout << "[Key] Exit Button pressed\n";
                        main_menu_window.close();
                        break;
                    }
                }
            }
        }

        main_menu_window.clear(sf::Color::Black);
        mouse_position = sf::Mouse::getPosition(main_menu_window);

        sf::Text arcade_game_title_text;
        arcade_game_title_text.setFont(s_Arcade_Font);
        arcade_game_title_text.setFillColor(sf::Color(255, 165, 0));
        arcade_game_title_text.setCharacterSize(70);
        arcade_game_title_text.setPosition(160, 50);
        std::string str = "ARCADE GAMES";
        arcade_game_title_text.setString(str);
        main_menu_window.draw(arcade_game_title_text);

        menu.DrawMenu(main_menu_window);

        main_menu_window.display();
    }

    /*

    sf::RenderWindow window(sf::VideoMode(Window_Width, Window_Height), "Tetris");

    memset(GameBoard::PlayingArea.data(), 0, sizeof(GameBoard::PlayingArea));

    Tetromino current_tetromino = CreateTetromino();

    sf::Clock clock;

    float last_time = clock.getElapsedTime().asSeconds();

    int points = 0;

    sf::Vector2i mouse_position;

    Button play_again_button(450.f, 400.f, 200.f, 50.f, s_Font, "Play again", 30, sf::Color::Blue, sf::Color::Green);

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

        mouse_position = sf::Mouse::getPosition(window);
        play_again_button.DrawButton(window);
        play_again_button.GetPressed(mouse_position);

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
    */
    
    return 0;
}