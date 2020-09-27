#include "Game.h"
#include "Layer.h"
#include "Database.h"
#include <iostream>
#include <chrono> 
#include <ctime> 
#include "GameLayer.h"
#include "MainMenuLayer.h"


void PreGameLayer::OnInit()
{
	m_TextBox = std::make_unique<TextBox>(*s_Arcade_Font, Window_Width / 4, 150.f, 500.f, 65.f);
	m_PlayButton = std::make_unique<Button>(Window_Width / 4 + 150, 300.f, 200.f, 50.f, *s_Arcade_Font, "START", 30, sf::Color::Blue, sf::Color::Green);
	m_BackButton = std::make_unique<Button>(30.f, 30.f, 200.f, 50.f, *s_Arcade_Font, "BACK", 30, sf::Color::Blue, sf::Color::Green);
}

void PreGameLayer::OnShutdown()
{

}

void PreGameLayer::OnUpdate()
{
	sf::RenderWindow& window = GetWindow();
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
		m_Sound.PlaySelectSound();
		SetLayer(new MainMenuLayer());
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
		SetLayer(new TimerLayer());
	}
}


void ScoreBoardLayer::OnInit()
{
	//Database& database = GetDatabase();
	m_Database.GetScoreList();
	m_BackButton = std::make_unique<Button>(30.f, 30.f, 200.f, 50.f, *s_Arcade_Font, "BACK", 30, sf::Color::Blue, sf::Color::Green);

	int i = 2;
	int spacing = 150;
	int x = 350.f;

	m_title.setFont(*s_Arcade_Font);
	m_title.setCharacterSize(50);
	m_title.setFillColor(sf::Color::White);
	m_title.setPosition(300.f, 80.f);
	m_title.setString("HIGH SCORES");

	m_Gold_Texture.loadFromFile("resources/first.png");
	m_Gold_Sprite.setTexture(m_Gold_Texture);
	m_Gold_Sprite.setScale(0.2f, 0.2f);
	m_Gold_Sprite.setPosition(x - 150.f, spacing * i - 20.f);

	m_score1.setFont(*s_Arcade_Font);
	m_score1.setFillColor(sf::Color::White);
	m_score1.setPosition(x + 300 , spacing * i);
	m_entry1.setFont(*s_Arcade_Font);
	m_entry1.setFillColor(sf::Color::White);
	m_entry1.setPosition(x, spacing * i++);

	m_Silver_Texture.loadFromFile("resources/second.png");
	m_Silver_Sprite.setTexture(m_Silver_Texture);
	m_Silver_Sprite.setScale(0.2f, 0.2f);
	m_Silver_Sprite.setPosition(x - 150.f, spacing * i - 20.f);

	m_score2.setFont(*s_Arcade_Font);
	m_score2.setFillColor(sf::Color::White);
	m_score2.setPosition(x + 300, spacing * i);
	m_entry2.setFont(*s_Arcade_Font);
	m_entry2.setFillColor(sf::Color::White);
	m_entry2.setPosition(x, spacing * i++);

	m_Bronze_Texture.loadFromFile("resources/third.png");
	m_Bronze_Sprite.setTexture(m_Bronze_Texture);
	m_Bronze_Sprite.setScale(0.2f, 0.2f);
	m_Bronze_Sprite.setPosition(x - 150.f, spacing * i - 20.f);

	m_score3.setFont(*s_Arcade_Font);
	m_score3.setFillColor(sf::Color::White);
	m_score3.setPosition(x + 300, spacing * i);
	m_entry3.setFont(*s_Arcade_Font);
	m_entry3.setFillColor(sf::Color::White);
	m_entry3.setPosition(x, spacing * i++);

	auto score_list = m_Database.GetScoreList();
	for (const auto& score : score_list)
	{
		std::string str = score.first + "  " + std::to_string(score.second);
	}

	m_entry1.setString(score_list[0].first);
	m_score1.setString(std::to_string(score_list[0].second));

	m_entry2.setString(score_list[1].first);
	m_score2.setString(std::to_string(score_list[1].second));

	m_entry3.setString(score_list[2].first);
	m_score3.setString(std::to_string(score_list[2].second));
}

void ScoreBoardLayer::OnShutdown()
{
}

void ScoreBoardLayer::OnUpdate()
{
	sf::RenderWindow& window = GetWindow();
	Database& database = GetDatabase();

	sf::Vector2i mouse_position = sf::Mouse::getPosition(window);

	m_BackButton->DrawButton(window);
	m_BackButton->GetPressed(mouse_position);

	window.draw(m_title);
	window.draw(m_entry1);
	window.draw(m_entry2);
	window.draw(m_entry3);

	window.draw(m_score1);
	window.draw(m_score2);
	window.draw(m_score3);

	window.draw(m_Gold_Sprite);
	window.draw(m_Silver_Sprite);
	window.draw(m_Bronze_Sprite);

	if (m_BackButton->m_buttonState == PRESSED)
	{
		std::cout << "Back Button pressed" << std::endl;
		m_Sound.PlaySelectSound();
		SetLayer(new MainMenuLayer());
	}
}

void ScoreBoardLayer::OnEvent(sf::Event& event)
{
	if (event.key.code == sf::Keyboard::Escape)
	{
		m_Sound.PlaySelectSound();
		SetLayer(new MainMenuLayer());
	}
}

void TimerLayer::OnInit()
{
	m_Sound.PlaySelectSound();
	m_game_start_text.setFont(*s_Arcade_Font);
	m_game_start_text.setFillColor(sf::Color(107, 133, 255));
	m_game_start_text.setCharacterSize(50);
	m_game_start_text.setPosition(200.f, 200.f);
	m_game_start_text.setString("GAME STARTS IN...");

	m_timer_text.setFont(*s_Arcade_Font);
	m_timer_text.setFillColor(sf::Color(107, 133, 255));
	m_timer_text.setCharacterSize(150);
	m_timer_text.setPosition(500.f, 500.f);
}

void TimerLayer::OnShutdown()
{

}

void TimerLayer::OnUpdate()
{
	sf::RenderWindow& window = GetWindow();	
	std::chrono::time_point<std::chrono::system_clock> begin = std::chrono::system_clock::now();
	auto time_difference = (std::chrono::duration_cast<std::chrono::microseconds>(begin - m_SecondsSinceStart).count()) / 1000000.0;
	auto timer = m_timer - (int)time_difference;

	m_timer_text.setString(std::to_string(timer));

	window.draw(m_timer_text);
	window.draw(m_game_start_text);

	if (timer < 0)
	{
		SetLayer(new GameLayer());
	}
}

void TimerLayer::OnEvent(sf::Event& event)
{

}
