#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <array>
class Menu
{
private:
	std::array <sf::Text, 3> m_Menu;
	sf::Font m_Font;
	int selectedIndex = 0;

	sf::Color neonPurple = sf::Color(190, 0, 254);
	sf::Color brightOrange = sf::Color(255, 165, 0);

public:
	Menu(float width, float height, sf::Font font);
	~Menu();

	void MoveUp();
	void MoveDown();
	void DrawMenu(sf::RenderTarget& renderTarget);
	int GetPressedItem();
};

