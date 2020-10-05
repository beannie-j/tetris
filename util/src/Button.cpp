#include "Button.h"
Button::Button(float x, float y, float width, float height, sf::Font font, std::string string, int character_size, sf::Color idleColor, sf::Color hoverColor)
{
	m_idleColor = idleColor;
	m_hoverColor = hoverColor;

	m_shape.setSize(sf::Vector2f(width, height));
	m_shape.setPosition(sf::Vector2f(x, y));
	m_shape.setFillColor(sf::Color(128, 128, 128));
	m_shape.setOutlineColor(sf::Color::White);
	m_font = font;
	m_text.setFont(m_font);
	m_text.setFillColor(sf::Color::White);
	m_text.setString(string);
	m_text.setCharacterSize(character_size);
	m_text.setPosition(sf::Vector2f(x + 30.f, y + 5.f));
}

Button::~Button()
{

}

void Button::DrawButton(sf::RenderTarget& renderTarget)
{
	renderTarget.draw(m_shape);
	renderTarget.draw(m_text);
}

void Button::FillColor()
{
	m_shape.setFillColor(sf::Color(30, 144, 255));
}


void Button::GetPressed(sf::Vector2i mousePosition)
{
	sf::Vector2f mousePositionF = sf::Vector2f(mousePosition.x, mousePosition.y);

	if(m_shape.getGlobalBounds().contains(mousePositionF))
	{
		m_IsHover = true;
		m_buttonState = Button_States::HOVER;
		m_shape.setFillColor(sf::Color(30, 144, 255));
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			m_buttonState = PRESSED;
			m_shape.setFillColor(sf::Color(30, 144, 255));
		}
	}
	else
	{
		m_buttonState = Button_States::IDLE;
		m_shape.setFillColor(sf::Color(128, 128, 128));
	}
}

