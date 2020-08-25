#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class TextBox
{
private:
	sf::Font m_Font;
	sf::RectangleShape m_Rect;
	float m_x;
	float m_y;
	float m_Width;
	float m_Height;
	std::string m_String = "";
	sf::Text m_Text;

public:
	TextBox(sf::Font font, float x, float y, float width, float height);
	std::string EnterText(sf::Uint16 character);
	void DrawTextBox(sf::RenderTarget& renderTarget);
	void setDimensions(float x, float y, float width, float height);
	void setString(std::string str);
	const std::string getString();

};

