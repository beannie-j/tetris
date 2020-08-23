#pragma once
#include <SFML/Graphics.hpp>
#include <string>
class Menu
{
private:
	std::string m_MenuList[4];
	sf::Text m_MenuList_Text[4];
	sf::Font m_Font;

public:
	Menu(float width, float height, sf::Font font);
	~Menu();

	void MoveUp();
	void MoveDown();
	void DrawMenu(sf::RenderTarget& renderTarget);
};

