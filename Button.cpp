#include "Button.h"
Button::Button(float x, float y, float width, float height, sf::Font font, std::string string, int character_size, sf::Color idleColor, sf::Color hoverColor)
{
	m_idleColor = idleColor;
	m_hoverColor = hoverColor;

	m_shape.setSize(sf::Vector2f(width, height));
	m_shape.setPosition(sf::Vector2f(x, y));
	m_shape.setFillColor(sf::Color(169, 169, 169));
	m_shape.setOutlineColor(sf::Color::White);
	m_font = font;
	m_text.setFont(m_font);
	m_text.setFillColor(sf::Color::White);
	m_text.setString(string);
	m_text.setCharacterSize(character_size);
	m_text.setPosition(sf::Vector2f(x + 10.f, y + 5.f));

	//m_text.setPosition(m_shape.getPosition().x / 2.f - m_text.getGlobalBounds().width, m_shape.getPosition().y / 2.f - m_text.getGlobalBounds().height);
}

Button::~Button()
{

}

void Button::DrawButton(sf::RenderTarget& renderTarget)
{
	renderTarget.draw(m_shape);
	renderTarget.draw(m_text);
}

void Button::GetPressed(sf::Vector2i mousePosition)
{
	// howver
	sf::Vector2f mousePositionF = sf::Vector2f(mousePosition.x, mousePosition.y);

	if(m_shape.getGlobalBounds().contains(mousePositionF))
	{
		std::cout << "BUTTON HOVER" << std::endl;
		m_IsHover = true;
		m_buttonState = Button_States::HOVER;
		m_shape.setFillColor(sf::Color(105, 105, 105));
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			m_buttonState = PRESSED;
			m_shape.setFillColor(sf::Color(30, 144, 255));
			std::cout << "BUTTON CLICK" << std::endl;
		}
	}
	else
	{
		std::cout << "BUTTON IDLE" << std::endl;
		m_buttonState = Button_States::IDLE;
		m_shape.setFillColor(sf::Color(169, 169, 169));
	}
}

