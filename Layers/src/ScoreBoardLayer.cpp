#include "ScoreBoardLayer.h"
#include "MainMenuLayer.h"
#include "../../Tetris/src/Application.h"

#include "../../Tetris/src/Game.h"

void ScoreBoardLayer::OnInit()
{
	auto& app = Application::GetApplication();

	m_BackButton = std::make_unique<Button>(30.f, 30.f, 200.f, 50.f, *s_Arcade_Font, "BACK", 30, sf::Color::Blue, sf::Color::Green);

	int i = 2;
	int spacing = 150;
	int x = 350;

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
	m_score1.setPosition((float)(x + 300), (float)(spacing * i));
	m_entry1.setFont(*s_Arcade_Font);
	m_entry1.setFillColor(sf::Color::White);
	m_entry1.setPosition((float)x, (float)(spacing * i++));

	// int -> int32_t -> 32-bit (4-byte) integer
	// float          -> 32-bit (4-byte) floating-point 

	m_Silver_Texture.loadFromFile("resources/second.png");
	m_Silver_Sprite.setTexture(m_Silver_Texture);
	m_Silver_Sprite.setScale(0.2f, 0.2f);
	m_Silver_Sprite.setPosition(x - 150.f, spacing * i - 20.f);

	m_score2.setFont(*s_Arcade_Font);
	m_score2.setFillColor(sf::Color::White);
	m_score2.setPosition((float)(x + 300), (float)(spacing * i));
	m_entry2.setFont(*s_Arcade_Font);
	m_entry2.setFillColor(sf::Color::White);
	m_entry2.setPosition((float)x, (float)(spacing * i++));

	m_Bronze_Texture.loadFromFile("resources/third.png");
	m_Bronze_Sprite.setTexture(m_Bronze_Texture);
	m_Bronze_Sprite.setScale(0.2f, 0.2f);
	m_Bronze_Sprite.setPosition(x - 150.f, spacing * i - 20.f);

	m_score3.setFont(*s_Arcade_Font);
	m_score3.setFillColor(sf::Color::White);
	m_score3.setPosition((float)(x + 300), (float)(spacing * i));
	m_entry3.setFont(*s_Arcade_Font);
	m_entry3.setFillColor(sf::Color::White);
	m_entry3.setPosition((float)x, (float)(spacing * i++));

	auto score_list = app.GetDatabase().GetScoreList();
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
	Application& app = Application::GetApplication();
	sf::RenderWindow& window = app.GetWindow();
	Database& database = app.GetDatabase();

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
		app.GetSound().Play("select");
		app.SetLayer(new MainMenuLayer());
	}
}

void ScoreBoardLayer::OnEvent(sf::Event& event)
{
	if (event.key.code == sf::Keyboard::Escape)
	{
		auto& app = Application::GetApplication();
		app.GetSound().Play("select");
		app.SetLayer(new MainMenuLayer());
	}
}



