#include "Menu.h"
#include <iostream>

Menu::Menu(float width, float height, sf::Font font)
{
	int size = m_Menu.size();
	m_Font = font;

	m_Menu[0].setFont(m_Font);
	m_Menu[0].setFillColor(neonPurple);
	m_Menu[0].setString("PLAY");
	m_Menu[0].setCharacterSize(61);
	m_Menu[0].setPosition(sf::Vector2f(width / 2 - 180.f, height / (size + 1) * 1));

	m_Menu[1].setFont(m_Font);
	m_Menu[1].setFillColor(brightOrange);
	m_Menu[1].setString("SCORES");
	m_Menu[1].setCharacterSize(50);
	m_Menu[1].setPosition(sf::Vector2f(width / 2 - 180.f, height / (size + 1) * 2));

	m_Menu[2].setFont(m_Font);
	m_Menu[2].setFillColor(brightOrange);
	m_Menu[2].setString("EXIT");
	m_Menu[2].setCharacterSize(50);
	m_Menu[2].setPosition(sf::Vector2f(width / 2 - 180.f, height / (size + 1) * 3));

}

Menu::~Menu()
{

}

void Menu::DrawMenu(sf::RenderTarget& renderTarget)
{
	for (sf::Text text : m_Menu)
	{
		renderTarget.draw(text);
	}
}

void Menu::MoveDown()
{
	if (selectedIndex < m_Menu.size() - 1)
	{
		m_Menu[selectedIndex].setCharacterSize(50);
		m_Menu[selectedIndex].setFillColor(brightOrange);
		selectedIndex += 1;
		m_Menu[selectedIndex].setFillColor(neonPurple);
		m_Menu[selectedIndex].setCharacterSize(61);

		std::cout << "[INFO] selectedIndex : " << selectedIndex << std::endl;
	}
	else 
	{
		std::cout << "[Out of Bounds] selectedIndex : " << selectedIndex << std::endl;
	}
}

void Menu::MoveUp()
{
	if (selectedIndex - 1 >= 0)
	{
		m_Menu[selectedIndex].setCharacterSize(50);
		m_Menu[selectedIndex].setFillColor(brightOrange);
		selectedIndex -= 1;
		m_Menu[selectedIndex].setFillColor(neonPurple);
		m_Menu[selectedIndex].setCharacterSize(61);

		std::cout << "[INFO] selectedIndex : " << selectedIndex << std::endl;
	}
	else
	{
		std::cout << "[Out of Bounds] selectedIndex : " << selectedIndex << std::endl;
	}
}

int Menu::GetPressedItem()
{
	return selectedIndex;
}


