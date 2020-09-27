#include "MainMenuLayer.h"

void MainMenuLayer::OnInit()
{
	// load resources
	m_Menu = std::make_unique<Menu>(Window_Width, Window_Height - 200.f, *s_Arcade_Font);
}

void MainMenuLayer::OnShutdown()
{
	// release resources
}

void MainMenuLayer::OnUpdate()
{
	sf::RenderWindow& window = GetWindow();

	sf::Vector2i mouse_position = sf::Mouse::getPosition(window);

	sf::Text arcade_game_title_text;
	arcade_game_title_text.setFont(*s_Arcade_Font);
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
	if (event.type == sf::Event::KeyReleased)
	{
		if (event.key.code == sf::Keyboard::Up)
		{
			m_Menu->MoveUp();
			m_Sound.PlayClickSound();
		}

		if (event.key.code == sf::Keyboard::Down)
		{
			m_Menu->MoveDown();
			m_Sound.PlayClickSound();
		}

		if (event.key.code == sf::Keyboard::Enter)
		{
			m_Sound.PlaySelectSound();
			std::cout << "[Key] Enter\n";
			switch (m_Menu->GetPressedItem())
			{
			default:
				break;
			case 0:
				std::cout << "[Key] Play Button pressed\n";
				m_Sound.PlaySelectSound();
				SetLayer(new PreGameLayer());
				break;
			case 1:
				std::cout << "[Key] Scores Button pressed\n";
				m_Sound.PlaySelectSound();
				SetLayer(new ScoreBoardLayer());
				break;
			case 2:
				std::cout << "[Key] Exit Button pressed\n";
				GetWindow().close();
				break;
			}
		}
	}
}