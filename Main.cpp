#include <SFML/Graphics.hpp>
#include <array>
#include <iostream>
#include <cstdlib>
#include <typeinfo>

// cw - clockwise
enum class RotationState : int {
    cw0 = 0, cw90 = 1, cw180 = 2, cw270 = 3
};

enum class TetrominoType : int {
    I = 0,
    O = 1,
    T = 2,
    S = 3,
    Z = 4,
    J = 5,
    L = 6,
    NumberOfTetrominoTypes
};




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

// static variables
constexpr static float block_size = 40.f;
constexpr static int s_GameBoardWidth = 10;
constexpr static int s_GameBoardHeight = 17;

constexpr static int width = 30 * block_size;
constexpr static int height = 30 * block_size;

const std::array<char, 7> types = { 'I', 'O', 'T', 'S', 'Z', 'J', 'L' };

float cell_size = 1.0f;

static std::array<int, s_GameBoardWidth* s_GameBoardHeight> s_PlayingArea;
static bool s_GameOver = false;


class Tetromino {
public:
    TetrominoType m_type;
    static constexpr size_t m_size = 4;
    std::array<std::array<int, m_size>, m_size> m_arr;
    RotationState m_rotation_state;

    float posX = 3.0f;
    float posY = 0.f;
    sf::Color m_color;
    bool m_landed = false;

    Tetromino(TetrominoType type);
    void Draw(sf::RenderWindow& window);
    bool MoveDown(float dy);
    bool CheckBounds();
    void Rotate_HardCoded(RotationState rotation_state);

private:

};

static sf::Color s_Colors[7] =
{
    sf::Color(0, 255, 255),
    sf::Color::Yellow,
    sf::Color(138, 43, 226),
    sf::Color::Green,
    sf::Color::Red,
    sf::Color::Blue,
    sf::Color(255, 165, 0)
};

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

Tetromino::Tetromino(TetrominoType type)
    : m_type(type)
{
    switch (m_type) {
    case TetrominoType::I:
        m_arr = { { 
            {0,0,0,0}, {1,1,1,1}, {0,0,0,0}, {0,0,0,0} } };
        m_rotation_state = RotationState::cw0;
        m_color = sf::Color(0, 255, 255);
        break;
    case TetrominoType::O:
        m_arr = { { {1,1,0,0}, {1,1,0,0}, {0,0,0,0}, {0,0,0,0} } };
        m_rotation_state = RotationState::cw0;
        m_color = sf::Color::Yellow;
        break;
    case TetrominoType::T:
        m_arr = { {{0,1,0,0}, {1,1,1,0}, {0,0,0,0}, {0,0,0,0}} };
        m_rotation_state = RotationState::cw0;
        m_color = sf::Color(138, 43, 226);
        break;
    case TetrominoType::S:
        m_arr = { {{0,1,1,0}, {1,1,0,0}, {0,0,0,0}, {0,0,0,0}} };
        m_rotation_state = RotationState::cw0;
        m_color = sf::Color::Green;
        break;
    case TetrominoType::Z:
        m_arr = { {{1,1,0,0}, {0,1,1,0}, {0,0,0,0}, {0,0,0,0}} };
        m_rotation_state = RotationState::cw0;
        m_color = sf::Color::Red;
        break;
    case TetrominoType::J:
        m_arr = { {{1,0,0,0}, {1,1,1,0}, {0,0,0,0}, {0,0,0,0}} };
        m_rotation_state = RotationState::cw0;
        m_color = sf::Color::Blue;
        break;
    case TetrominoType::L:
        m_arr = { {{0,0,1,0}, {1,1,1,0}, {0,0,0,0}, {0,0,0,0}} };
        m_rotation_state = RotationState::cw0;
        m_color = sf::Color(255, 165, 0);
        break;
    default:
        std::cout << "[ERROR] Tetrimino needs a shape\n";
        break;
    }
}

void Tetromino::Rotate_HardCoded(RotationState rotation_state)
{
    int intState = (int)rotation_state; // cw90
    intState = (intState + 1) % 4; // cw180
    m_rotation_state = (RotationState)intState;

    switch (m_type) {
    case TetrominoType::I:
        if (rotation_state == RotationState::cw0) {
            m_arr = { {
            {0,0,1,0},
            {0,0,1,0},
            {0,0,1,0},
            {0,0,1,0} } };

            m_rotation_state = RotationState::cw90;
        }
        if (rotation_state == RotationState::cw90) {
            m_arr = { {
            {0,0,0,0},
            {0,0,0,0},
            {1,1,1,1},
            {0,0,0,0} } };

            m_rotation_state = RotationState::cw180;
        }
        if (rotation_state == RotationState::cw180) {
            m_arr = { {
            {0,1,0,0},
            {0,1,0,0},
            {0,1,0,0},
            {0,1,0,0} } };

            m_rotation_state = RotationState::cw270;
        }
        if (rotation_state == RotationState::cw270) {
            m_arr = { {
            {0,0,0,0},
            {1,1,1,1},
            {0,0,0,0},
            {0,0,0,0} } };
            m_rotation_state = RotationState::cw0;
        }
        break;
    case TetrominoType::O:
        m_arr = { { {1,1,0,0}, 
            {1,1,0,0}, 
            {0,0,0,0}, 
            {0,0,0,0} } };
        break;
    case TetrominoType::T:
        if (rotation_state == RotationState::cw0) {
            m_arr = { {
            {0,1,0,0},
            {0,1,1,0},
            {0,1,0,0},
            {0,0,0,0} } };
            m_rotation_state = RotationState::cw90;
        }
        if (rotation_state == RotationState::cw90) {
            m_arr = { {
            {0,0,0,0},
            {1,1,1,0},
            {0,1,0,0},
            {0,0,0,0} } };
            m_rotation_state = RotationState::cw270;
        }
        if (rotation_state == RotationState::cw270) {
            m_arr = { {
            {0,0,0,0},
            {0,1,0,0},
            {1,1,0,0},
            {0,1,0,0} } };
            m_rotation_state = RotationState::cw0;
        }
        break;

    case TetrominoType::S:
        if (rotation_state == RotationState::cw0) {
            m_arr = { {
            {0,0,0,0},
            {1,0,0,0},
            {1,1,0,0},
            {0,1,0,0} } };
            m_rotation_state = RotationState::cw90;
        }

        if (rotation_state == RotationState::cw90) {
            m_arr = { {
            {0,0,0,0},
            {0,0,0,0},
            {0,1,1,0},
            {1,1,0,0} } };
            m_rotation_state = RotationState::cw180;
        }

        if (rotation_state == RotationState::cw180) {
            m_arr = { {
            {0,0,0,0},
            {1,0,0,0},
            {1,1,0,0},
            {0,1,0,0} } };
            m_rotation_state = RotationState::cw270;
        }

        if (rotation_state == RotationState::cw270) {
            m_arr = { {
            {0,0,0,0},
            {0,0,0,0},
            {0,1,1,0},
            {1,1,0,0} } };
            m_rotation_state = RotationState::cw0;
        }
        break;
    case TetrominoType::Z:
        if (rotation_state == RotationState::cw0) {
            m_arr = { {
            {0,0,0,0},
            {0,1,0,0},
            {1,1,0,0},
            {1,0,0,0} } };
            m_rotation_state = RotationState::cw90;
        }
        if (rotation_state == RotationState::cw90) {
            m_arr = { {
            {0,0,0,0},
            {1,1,0,0},
            {0,1,1,0},
            {0,0,0,0} } };
            m_rotation_state = RotationState::cw180;
        }
        if (rotation_state == RotationState::cw180) {
            m_arr = { {
            {0,0,0,0},
            {0,1,0,0},
            {1,1,0,0},
            {1,0,0,0} } };
            m_rotation_state = RotationState::cw270;
        }
        if (rotation_state == RotationState::cw270) {
            m_arr = { {
            {0,0,0,0},
            {0,0,0,0},
            {1,1,0,0},
            {0,1,1,0} } };
            m_rotation_state = RotationState::cw0;
        }

        break;
    case TetrominoType::J:
        if (rotation_state == RotationState::cw0) {
            m_arr = { {
            {0,0,0,0},
            {1,1,0,0},
            {1,0,0,0},
            {1,0,0,0} } };
            m_rotation_state = RotationState::cw90;
        }
        if (rotation_state == RotationState::cw90) {
            m_arr = { {
            {0,0,0,0},
            {1,1,1,0},
            {0,0,1,0},
            {0,0,0,0} } };
            m_rotation_state = RotationState::cw180;
        }
        if (rotation_state == RotationState::cw180) {
            m_arr = { {
            {0,0,0,0},
            {0,0,1,0},
            {0,0,1,0},
            {0,1,1,0} } };
            m_rotation_state = RotationState::cw270;
        }
        if (rotation_state == RotationState::cw270) {
            m_arr = { {
            {0,0,0,0},
            {0,0,0,0},
            {1,0,0,0},
            {1,1,1,0} } };
            m_rotation_state = RotationState::cw0;
        }

        break;
    case TetrominoType::L:
        if (rotation_state == RotationState::cw0) {
            m_arr = { {
            {0,1,0,0},
            {0,1,0,0},
            {0,1,1,0},
            {0,0,0,0}} };
            m_rotation_state = RotationState::cw90;
        }
        if (rotation_state == RotationState::cw90) {
            m_arr = { {
            {0,0,0,0},
            {0,1,1,1},
            {0,1,0,0},
            {0,0,0,0}} };
            m_rotation_state = RotationState::cw180;
        }
        if (rotation_state == RotationState::cw180) {
            m_arr = { {
            {0,0,0,0},
            {0,1,1,0},
            {0,0,1,0},
            {0,0,1,0}} };
            m_rotation_state = RotationState::cw270;
        }
        if (rotation_state == RotationState::cw270) {
            m_arr = { {
            {0,0,0,0},
            {0,0,0,0},
            {0,0,1,0},
            {1,1,1,0}} };
            m_rotation_state = RotationState::cw0;
        }
        break;
    }
}

bool Tetromino::MoveDown(float dy)
{
    if (CheckBounds())
    {
        posY += dy;
        //std::cout << "Moving down " << dy << std::endl;
        return true;
    }
    this->m_landed = true;
    return false;
}

static bool CheckGameOver(Tetromino curr)
{
    // it should be game over if there is no where to fit the tetromino.
    for (int y = 0; y < curr.m_size; y++)
    {
        for (int x = 0; x < curr.m_size; x++)
        {
            if (curr.m_arr[y][x] == 0) continue;

            if (y + curr.posY <= 1 && curr.m_landed)
            {
                s_GameOver = true;
            }
        }
    }
    return true;
}

bool Tetromino::CheckBounds()
{
    for (int y = 0; y < m_size; y++)
    {
        for (int x = 0; x < m_size; x++)
        {
            if (m_arr[y][x] == 0) continue;

            if ((posX + x) * block_size < 0 || (posX + x) * block_size >= ((s_GameBoardWidth) * block_size) - cell_size) return false;
            if ((y + posY) * block_size >= ((s_GameBoardHeight - 1) * block_size) - (block_size))
            {
                m_landed = true;
                return false;
            }

            int potentialPosition = (x + posX) + (y + posY + 2) * s_GameBoardWidth;
           // std::cout << " position : check bounds" << x + posX << " , " << y + posY << " m_landed:";
          

            if (s_PlayingArea[potentialPosition])
            {
                m_landed = true;

                return false;
            }

        }
    }
    return true;
}

static sf::Font s_Font;

void Tetromino::Draw(sf::RenderWindow& window)
{
    sf::Text text;
    text.setFont(s_Font);
    text.setFillColor(sf::Color(255, 255, 255));
    text.setCharacterSize(14);

    sf::RectangleShape rect(sf::Vector2f(block_size, block_size));
    rect.setFillColor(m_color);
    for (int y = 0; y < m_size; y++)
    {
        for (int x = 0; x < m_size; x++)
        {
            if (m_arr[y][x])
            {
                float cx = (posX + x) * block_size;
                float cy = (posY + y) * block_size;

                rect.setPosition(sf::Vector2f(cx, cy));
                //rect.setOutlineThickness(2);
                //rect.setOutlineColor(sf::Color(250, 150, 100));
                window.draw(rect);

                text.setPosition(sf::Vector2f(cx, cy));
                std::string string = std::to_string((int)(posX + x)) + ", " + std::to_string((int)(posY + y));
                text.setString(string);
                window.draw(text);
            }
        }
    }
}

Tetromino CreateTetromino()
{
    int random = rand() % 7;
    TetrominoType type = GetTypeFromNumeration(random);
    Tetromino tetromino(TetrominoType::I);

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
        }
        window.display();

    }
    
    

    return 0;
}