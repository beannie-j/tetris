#include "Menu.h"
#include <iostream>

Menu::Menu(float width, float height, sf::Font font)
{
	m_Font = font;
	m_MenuList[0] = "Play Tetris";
	m_MenuList[1] = "Options";
	m_MenuList[2] = "View Leaderboard";
	m_MenuList[3] = "Exit";
	int i = 0;
	for (sf::Text menuText : m_MenuList_Text)
	{
		menuText.setFont(m_Font);
		menuText.setFillColor(sf::Color::White);
		menuText.setString(m_MenuList[i]);
		menuText.setCharacterSize(50);
		menuText.setPosition(sf::Vector2f(width + 10.f, (height /4) * i));
		++i;
	}
}

Menu::~Menu()
{

}

void Menu::DrawMenu(sf::RenderTarget& renderTarget)
{
	std::cout << "Drawing menu list items" << std::endl;
	renderTarget.draw(m_MenuList_Text[0]);
	renderTarget.draw(m_MenuList_Text[1]);
	renderTarget.draw(m_MenuList_Text[2]);
	renderTarget.draw(m_MenuList_Text[3]);

}


