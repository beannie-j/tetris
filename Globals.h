#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include <iostream>
#include <cstdlib>
#include <typeinfo>

constexpr float block_size = 40.f;
constexpr int s_GameBoardWidth = 10;
constexpr int s_GameBoardHeight = 16;

constexpr int width = 30 * block_size;
constexpr int height = 30 * block_size;

const std::array<char, 7> types = { 'I', 'O', 'T', 'S', 'Z', 'J', 'L' };

constexpr float cell_size = 1.0f;

inline std::array<int, s_GameBoardWidth* s_GameBoardHeight> s_PlayingArea;
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