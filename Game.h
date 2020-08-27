#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include <string>
#include <queue>
#include <vector>

constexpr float cell_size = 1.0f;

const std::array<char, 7> types = { 'I', 'O', 'T', 'S', 'Z', 'J', 'L' };

struct GameBoard
{
    inline static constexpr int Width = 10;
    inline static constexpr int Height = 16;
    inline static std::array<int, Width* Height> PlayingArea;
};

struct cmp
{
    template<typename T, typename U>
    bool operator() (T const& lhs, U const& rhs) const
    {
        return lhs.second < rhs.second;
    }
};

// inline - same across all compile unit
inline bool s_GameOver = false;
inline sf::Font s_Font;
inline sf::Font* s_Arcade_Font;
inline sf::Font s_Arcade_Font2;
inline std::string s_Username;
inline int s_shift = 7;
inline std::priority_queue<std::pair<std::string, int>,
    std::vector<std::pair<std::string, int>>, cmp> s_priority_queue;

constexpr float block_size = 40.f;
constexpr int Window_Width = 30 * block_size;
constexpr int Window_Height = 30 * block_size;

sf::RenderWindow& GetWindow();

class Layer;
void SetLayer(Layer* layer);

template<typename T>
void CreateAndSetLayer();

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