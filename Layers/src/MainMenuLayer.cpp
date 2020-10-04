#include "MainMenuLayer.h"
#include "ScoreBoardLayer.h"
#include "PreGameLayer.h"

#include "../../Tetris/src/Game.h"
#include "../../Tetris/src/Application.h"

void MainMenuLayer::OnInit()
{
	// load resources
	auto& app = Application::GetApplication();
	sf::Font& font = app.GetFont();
	m_Menu = std::make_unique<Menu>((float)Application::Window_Width, (float)Application::Window_Height - 200.f, font);
}

void MainMenuLayer::OnShutdown()
{
	// release resources
}

void MainMenuLayer::OnUpdate()
{
	auto& app = Application::GetApplication();
	sf::RenderWindow& window = app.GetWindow();
	sf::Font& font = app.GetFont();

	sf::Vector2i mouse_position = sf::Mouse::getPosition(window);

	sf::Text arcade_game_title_text;
	arcade_game_title_text.setFont(font);
	arcade_game_title_text.setFillColor(sf::Color(255, 165, 0));
	arcade_game_title_text.setCharacterSize(70);
	arcade_game_title_text.setPosition(160, 50);
	std::string str = "ARCADE GAMES";
	arcade_game_title_text.setString(str);
	window.draw(arcade_game_title_text);

	m_Menu->DrawMenu(window);
}

void MainMenuLayer::OnEvent(sf::Event& event)
{
	auto& app = Application::GetApplication();
	auto& sound = app.GetSound();
	if (event.type == sf::Event::KeyReleased)
	{
		if (event.key.code == sf::Keyboard::Up)
		{
			m_Menu->MoveUp();
			sound.Play("click");
		}

		if (event.key.code == sf::Keyboard::Down)
		{
			m_Menu->MoveDown();
			sound.Play("click");
		}

		if (event.key.code == sf::Keyboard::Enter)
		{
			sound.Play("select");
			std::cout << "[Key] Enter\n";
			switch (m_Menu->GetPressedItem())
			{
			default:
				break;
			case 0:
				std::cout << "[Key] Play Button pressed\n";
				sound.Play("select");
				app.SetLayer(new PreGameLayer());
				break;
			case 1:
				std::cout << "[Key] Scores Button pressed\n";
				sound.Play("select");
				app.SetLayer(new ScoreBoardLayer());
				break;
			case 2:
				std::cout << "[Key] Exit Button pressed\n";
				app.GetWindow().close();
				break;
			}
		}
	}
}