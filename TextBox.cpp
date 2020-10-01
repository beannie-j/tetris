#include "TextBox.h"
#include <iostream>

TextBox::TextBox(sf::Font font, float x, float y, float width, float height)
{
	m_Font = font;
	m_x = x;
	m_y = y;
	m_Width = width;
	m_Height = height;
}

std::string TextBox::EnterText(sf::Uint16 character)
{
	if (character == 8) // delete
	{
		// Making sure that string is not empty before poping.
		if (!m_String.empty())
		{
			m_String.pop_back();
		}
	} 

	else if (character == 13) // enter key
	{
		std::cout << "[INFO] Username : " << m_String << std::endl;
		return m_String;
	}

	else
	{
		m_String += toupper((char)character);
	}

	return m_String;
}
void TextBox::DrawTextBox(sf::RenderTarget& renderTarget)
{
	renderTarget.draw(m_Rect);
	renderTarget.draw(m_Text);
}

void TextBox::setDimensions(float x, float y, float width, float height)
{
	m_Rect.setPosition(x, y);
	m_Rect.setFillColor(sf::Color::Black);
	m_Rect.setOutlineColor(sf::Color::White);
	m_Rect.setSize(sf::Vector2f(width, height));
	m_Rect.setOutlineThickness(2);

	m_Text.setCharacterSize(30);
	m_Text.setPosition(x + 100.f, y + 10.f);
	m_Text.setFont(m_Font);
	m_Text.setString(m_String);
	m_Text.setFillColor(sf::Color::White);
}

void TextBox::setString(std::string str)
{
	m_Text.setString(str);
}

const std::string TextBox::getString()
{
	return m_String;
}

