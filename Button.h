#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

enum Button_States : int {
	IDLE = 0,
	HOVER = 1,
	PRESSED = 2
};

class Button
{
private:
	bool m_IsPressed;
	bool m_IsHover;

	sf::RectangleShape m_shape;
	sf::Font m_font;
	sf::Text m_text;
	sf::Color m_idleColor;
	sf::Color m_hoverColor;
	int m_character_size;

public:
	int m_buttonState = IDLE;

	Button(float x, float y, float width, float height, sf::Font font, std::string string, int character_size, sf::Color idleColor, sf::Color hoverColor);
	~Button();

	void DrawButton(sf::RenderTarget& renderTarget);
	void GetPressed(sf::Vector2i mousePosition);
	void FillColor();
};

