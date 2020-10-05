#pragma once
#include <SFML/Graphics.hpp>
#include <array>

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

class Tetromino {
public:
    TetrominoType m_type;
    static constexpr size_t m_size = 4;
    std::array<std::array<int, m_size>, m_size> m_arr;
    RotationState m_rotation_state;

    float posX = 3.0f;
    float posY = 0.f;
    sf::Color m_color;

    // make it const
    float cell_size = 1.0f;

    Tetromino(TetrominoType type);
    void Draw(sf::RenderWindow& window);
    bool MoveDown(float dy);
    bool CollisionWithBlocks(float dx, float dy);
    bool XBoundsCollision();
    bool YBoundsCollision();
    bool Y1BoundsCollision();
    void Rotate_HardCoded(RotationState rotation_state);
    bool TopBoundsCollision();
    bool XLeftBoundsCollision();
    bool XRightBoundsCollision();
    static constexpr float block_size = 40.f;
    static sf::Color s_Colors[10];

    Tetromino() = default;

private:
};