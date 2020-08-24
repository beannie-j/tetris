#include "Tetromino.h"
#include <iostream>
#include <cstdlib>
#include <typeinfo>

Tetromino::Tetromino(TetrominoType type)
    : m_type(type)
{
    switch (m_type) {
    case TetrominoType::I:
        m_arr = { {
            {1,1,1,1}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0} } };
        m_rotation_state = RotationState::cw0;
        m_color = sf::Color(59, 237, 237);
        break;
    case TetrominoType::O:
        m_arr = { { {1,1,0,0}, {1,1,0,0}, {0,0,0,0}, {0,0,0,0} } };
        m_rotation_state = RotationState::cw0;
        m_color = sf::Color(237, 234, 59);
        break;
    case TetrominoType::T:
        m_arr = { {{0,1,0,0}, {1,1,1,0}, {0,0,0,0}, {0,0,0,0}} };
        m_rotation_state = RotationState::cw0;
        m_color = sf::Color(138, 43, 226);
        break;
    case TetrominoType::S:
        m_arr = { {{0,1,1,0}, {1,1,0,0}, {0,0,0,0}, {0,0,0,0}} };
        m_rotation_state = RotationState::cw0;
        m_color = sf::Color(53, 232, 68);
        break;
    case TetrominoType::Z:
        m_arr = { {{1,1,0,0}, {0,1,1,0}, {0,0,0,0}, {0,0,0,0}} };
        m_rotation_state = RotationState::cw0;
        m_color = sf::Color(232, 70, 49);
        break;
    case TetrominoType::J:
        m_arr = { {{1,0,0,0}, {1,1,1,0}, {0,0,0,0}, {0,0,0,0}} };
        m_rotation_state = RotationState::cw0;
        m_color = sf::Color(54, 86, 227);
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
        return true;
    }
    this->m_landed = true;
    return false;
}

bool Tetromino::CheckBounds()
{
    for (int y = 0; y < m_size; y++)
    {
        for (int x = 0; x < m_size; x++)
        {
            if (m_arr[y][x] == 0) continue;

            if ((posX + x) * block_size < 0 || (posX + x) * block_size >= ((GameBoard::Width)*block_size) - cell_size) return false;
            if ((y + posY) * block_size >= ((GameBoard::Height - 1) * block_size) - (block_size))
            {
                m_landed = true;
                return false;
            }

            int potentialPosition = (x + posX) + (y + posY + 2) * GameBoard::Width;
            // std::cout << " position : check bounds" << x + posX << " , " << y + posY << " m_landed:";
            if (GameBoard::PlayingArea[potentialPosition])
            {
                m_landed = true;
                return false;
            }
        }
    }
    return true;
}

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
                float cx = (posX + x + s_shift) * block_size;
                float cy = (posY + y + s_shift) * block_size;

                rect.setPosition(sf::Vector2f(cx, cy));
                window.draw(rect);

                text.setPosition(sf::Vector2f(cx, cy));
                std::string string = std::to_string((int)(posX + x)) + ", " + std::to_string((int)(posY + y));
                text.setString(string);
                window.draw(text);
            }
        }
    }
}
