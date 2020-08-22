#pragma once
#include <SFML/Graphics.hpp>

class Button
{
private:
	sf::RectangleShape m_shape;
	sf::Font m_font;
	sf::Text m_text;
	sf::Color m_idleColor;
	sf::Color m_hoverColor;
	int m_character_size;

public:
	Button(float x, float y, float width, float height, sf::Font font, std::string string, int character_size, sf::Color idleColor, sf::Color hoverColor)
	{
		m_shape.setSize(sf::Vector2f(width, height));
		m_shape.setPosition(sf::Vector2f(x, y));
		m_font = font;
		m_text.setFont(m_font);
		m_text.setString(string);
		m_text.setCharacterSize(character_size);
		m_text.setFillColor(sf::Color::White);
		m_text.setPosition(m_shape.getPosition().x / 2.f, m_shape.getPosition().y / 2.f);

		m_idleColor = idleColor;
		m_hoverColor = hoverColor;

		m_shape.setFillColor(m_idleColor);


	}
	~Button();

	void DrawButton(sf::RenderTarget& renderTarget);

};

