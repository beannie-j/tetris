#include "PreGameLayer.h"
#include "MainMenuLayer.h"
#include "TimerLayer.h"

#include "Game.h"
#include "Application.h"

void PreGameLayer::OnInit()
{
	m_TextBox = std::make_unique<TextBox>(*s_Arcade_Font, (float)(Window_Width / 4), 150.f, 500.f, 65.f);
	m_PlayButton = std::make_unique<Button>((float)(Window_Width / 4 + 150), 300.f, 200.f, 50.f, *s_Arcade_Font, "START", 30, sf::Color::Blue, sf::Color::Green);
	m_BackButton = std::make_unique<Button>(30.f, 30.f, 200.f, 50.f, *s_Arcade_Font, "BACK", 30, sf::Color::Blue, sf::Color::Green);
}

void PreGameLayer::OnShutdown()
{

}

void PreGameLayer::OnUpdate()
{
	auto& app = Application::GetApplication();
	sf::RenderWindow& window = app.GetWindow();
	sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
	// Draw some graphical entities
	sf::Text askNameText;
	askNameText.setFont(*s_Arcade_Font);
	askNameText.setFillColor(sf::Color::White);
	askNameText.setCharacterSize(30);
	askNameText.setPosition(Window_Width / 4, 100);
	std::string string = "ENTER YOUR NAME :";
	askNameText.setString(string);
	window.draw(askNameText);

	m_TextBox->setDimensions(Window_Width / 4, 150.f, 500.f, 65.f);

	m_PlayButton->DrawButton(window);
	//playButton.GetPressed(mouse_position);
	m_TextBox->DrawTextBox(window);

	m_BackButton->DrawButton(window);
	m_BackButton->GetPressed(mouse_position);

	if (m_BackButton->m_buttonState == PRESSED)
	{
		std::cout << "[INFO] Back Button pressed" << std::endl;
		app.GetSound().Play("select");
		app.SetLayer(new MainMenuLayer());
	}
}

void PreGameLayer::OnEvent(sf::Event& event)
{
	if (event.type == sf::Event::TextEntered)
	{
		m_TextBox->EnterText(event.text.unicode);
	}

	if (event.key.code == sf::Keyboard::Enter)
	{
		std::cout << "[Key] Enter, Username : " << m_TextBox->getString() << std::endl;
		s_Username = m_TextBox->getString();
		m_PlayButton->FillColor();
		auto& app = Application::GetApplication();
		app.SetLayer(new TimerLayer());
	}
}
