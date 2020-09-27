#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <array>
#include <string>
#include <queue>
#include <vector>
#include <stack>

constexpr float cell_size = 1.0f;

const std::array<char, 7> types = { 'I', 'O', 'T', 'S', 'Z', 'J', 'L' };

struct GameBoard
{
    inline static constexpr int Width = 10;
    inline static constexpr int Height = 17;
    inline static std::array<int, Width* Height> PlayingArea;
};

// inline - same across all compile unit
inline int s_Score = 0;
inline bool s_GameOver = false;
inline sf::Font* s_Arcade_Font;
inline std::string s_Username;
inline int s_shift = 7;

constexpr float block_size = 40.f;
constexpr int Window_Width = 30 * block_size;
constexpr int Window_Height = 30 * block_size;

/*sf::RenderWindow& GetWindow();

class Database;
Database& GetDatabase();

class Sound;
Sound& GetSound();

class Layer;
void SetLayer(Layer* layer);

template<typename T>
void CreateAndSetLayer();*/


inline sf::Color s_Colors[10] =
{
    sf::Color::Black,
    sf::Color::Black,
    sf::Color(59, 237, 237), // cyan
    sf::Color(237, 234, 59), // yellow
    sf::Color(138, 43, 226), // purple
    sf::Color(53, 232, 68), // green
    sf::Color(232, 70, 49), // red
    sf::Color(54, 86, 227), // blue
    sf::Color(138, 43, 226), // purple
    sf::Color(255, 165, 0) // orange-yellow
};