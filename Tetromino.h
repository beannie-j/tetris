#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"

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
/*

extern std::array<int, s_GameBoardWidth* s_GameBoardHeight> s_PlayingArea;
extern bool s_GameOver;
extern sf::Font s_Font;

extern sf::Color s_Colors[7];
*/
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
    static constexpr float block_size = 40.f;

private:

};