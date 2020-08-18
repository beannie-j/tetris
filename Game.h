#pragma once
#include <SFML/Graphics.hpp>
#include <array>

constexpr float cell_size = 1.0f;

const std::array<char, 7> types = { 'I', 'O', 'T', 'S', 'Z', 'J', 'L' };

struct GameBoard
{
    inline static constexpr int Width = 10;
    inline static constexpr int Height = 16;
    inline static std::array<int, Width* Height> PlayingArea;
};
// inline - same across all compile unit
inline bool s_GameOver = false;
inline sf::Font s_Font;

inline sf::Color s_Colors[7] =
{
    sf::Color(0, 255, 255),
    sf::Color::Yellow,
    sf::Color(138, 43, 226),
    sf::Color::Green,
    sf::Color::Red,
    sf::Color::Blue,
    sf::Color(255, 165, 0)
};