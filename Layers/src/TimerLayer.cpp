#include "TimerLayer.h"
#include "GameLayer.h"

#include "../../Tetris/src/Application.h"

void TimerLayer::OnShutdown()
{

}

void TimerLayer::OnUpdate()
{
	auto& app = Application::GetApplication();
	sf::RenderWindow& window = app.GetWindow();
	std::chrono::time_point<std::chrono::system_clock> begin = std::chrono::system_clock::now();
	auto time_difference = (std::chrono::duration_cast<std::chrono::microseconds>(begin - m_SecondsSinceStart).count()) / 1000000.0;
	auto timer = m_timer - (int)time_difference;

	m_timer_text.setString(std::to_string(timer));

	window.draw(m_timer_text);
	window.draw(m_game_start_text);

	if (timer < 0)
	{
		app.SetLayer(new GameLayer());
	}
}

void TimerLayer::OnEvent(sf::Event& event)
{

}

void TimerLayer::OnInit()
{
	auto& app = Application::GetApplication();
	app.GetSound().Play("select");
	sf::Font& font = app.GetFont();
	m_game_start_text.setFont(font);
	m_game_start_text.setFillColor(sf::Color(107, 133, 255));
	m_game_start_text.setCharacterSize(50);
	m_game_start_text.setPosition(200.f, 200.f);
	m_game_start_text.setString("GAME STARTS IN...");

	m_timer_text.setFont(font);
	m_timer_text.setFillColor(sf::Color(107, 133, 255));
	m_timer_text.setCharacterSize(150);
	m_timer_text.setPosition(500.f, 500.f);
}