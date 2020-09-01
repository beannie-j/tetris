#include "Game.h"
#include "Layer.h"
#include "Database.h"
#include <iostream>
#include <chrono> 
#include <ctime> 

static void DrawUsername(sf::RenderWindow& window)
{
	sf::Text text;
	text.setFont(*s_Arcade_Font);
	text.setFillColor(sf::Color::White);
	text.setCharacterSize(30);
	text.setPosition(700, 70);
	std::string string = "PLAYER : " + s_Username;
	text.setString(string);
	window.draw(text);
}

static void DrawPoints(sf::RenderWindow& window, int points)
{
	sf::Text text;
	text.setFont(*s_Arcade_Font);
	text.setFillColor(sf::Color::White);
	text.setCharacterSize(30);
	text.setPosition(700, 120);
	std::string string = "POINTS : " + std::to_string(points);
	text.setString(string);
	window.draw(text);

	if (s_GameOver)
	{
		text.setFillColor(sf::Color::Transparent);
	}
}

int GetColorInt(Tetromino tetromino)
{
	if (tetromino.m_type == TetrominoType::I) return 2;
	if (tetromino.m_type == TetrominoType::O) return 3;
	if (tetromino.m_type == TetrominoType::T) return 4;
	if (tetromino.m_type == TetrominoType::S) return 5;
	if (tetromino.m_type == TetrominoType::Z) return 6;
	if (tetromino.m_type == TetrominoType::J) return 7;
	if (tetromino.m_type == TetrominoType::L) return 8;

}

TetrominoType GetTypeFromNumeration(int number)
{
	switch (number) {
	case 0: return TetrominoType::I;
	case 1: return TetrominoType::O;
	case 2: return TetrominoType::T;
	case 3: return TetrominoType::S;
	case 4: return TetrominoType::Z;
	case 5: return TetrominoType::J;
	case 6: return TetrominoType::L;
	}
}

static bool CheckGameOver(Tetromino curr)
{
	for (int y = 0; y < curr.m_size; y++)
	{
		for (int x = 0; x < curr.m_size; x++)
		{
			if (curr.m_arr[y][x] == 0) continue;
			int pos = (x + curr.posX) + (y + curr.posY) * GameBoard::Width;
			if (GameBoard::PlayingArea[pos] && curr.m_landed)
			{
				s_GameOver = true;
			}
		}
	}
	return true;
}

static void DrawGameBoard_GameOver(sf::RenderWindow& window)
{
	sf::RectangleShape rect(sf::Vector2f(Tetromino::block_size, Tetromino::block_size));

	for (int y = 0; y < GameBoard::Height; y++)
	{
		for (int x = 0; x < GameBoard::Width; x++)
		{
			float cx = (x + s_shift) * Tetromino::block_size;
			float cy = (y + s_shift) * Tetromino::block_size;
			int block = GameBoard::PlayingArea[x + y * GameBoard::Width];
			if (block < 2)
			{
				rect.setPosition(sf::Vector2f(cx, cy));
				rect.setFillColor(sf::Color(139, 0, 0));
				rect.setOutlineColor(sf::Color(250, 150, 100));
				window.draw(rect);
			}

		}
	}
}

static void DrawGameBoard(sf::RenderWindow& window)
{
	sf::RectangleShape rect(sf::Vector2f(Tetromino::block_size, Tetromino::block_size));

	sf::Text text;
	text.setFont(*s_Arcade_Font);
	text.setFillColor(sf::Color(255, 255, 255));
	text.setCharacterSize(14);

	for (int y = 0; y < GameBoard::Height; y++)
	{
		for (int x = 0; x < GameBoard::Width; x++)
		{
			float cx = (x + s_shift) * Tetromino::block_size;
			float cy = (y + s_shift) * Tetromino::block_size;
			int block = GameBoard::PlayingArea[x + y * GameBoard::Width];
			if (block >= 2)
			{
				rect.setPosition(sf::Vector2f(cx, cy));
				//rect.setOutlineThickness(3);
				rect.setFillColor(s_Colors[block]);
				rect.setOutlineColor(sf::Color(250, 150, 100));
				window.draw(rect);
			}
			else
			{
				rect.setPosition(sf::Vector2f(cx, cy));
				rect.setOutlineThickness(3);
				rect.setFillColor(sf::Color::Black);
				rect.setOutlineColor(sf::Color::White);

				window.draw(rect);

				// this is for debugging purposes - don't delete
				//text.setPosition(sf::Vector2f(cx, cy));
				//std::string string = std::to_string(x) + ", " + std::to_string(y);
				//text.setString(string);
				//window.draw(text);
			}
		}
	}
}

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
	m_Sound_Stack = GetSoundStack();

	if (event.type == sf::Event::KeyReleased)
	{
		if (event.key.code == sf::Keyboard::Up)
		{
			m_Menu->MoveUp();
			//m_Sound_Stack.push(m_Sound.m_Click_Sound);
			m_Sound.PlayClickSound();
		}
		
		if (event.key.code == sf::Keyboard::Down)
		{
			m_Menu->MoveDown();
			m_Sound.PlayClickSound();
			//m_Sound_Stack.push(m_Sound.m_Click_Sound);
		}

		if (event.key.code == sf::Keyboard::Enter)
		{
			m_Sound.PlaySelectSound();
			m_Sound_Stack.push(m_Sound.m_Select_Sound);
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
				//m_Sound.PlaySelectSound();
				GetWindow().close();
				break;
			}
		}
	}
}

void PreGameLayer::OnInit()
{
	//m_Sound.PlaySelectSound();
	m_TextBox = std::make_unique<TextBox>(*s_Arcade_Font, Window_Width / 4, 150.f, 500.f, 65.f);
	m_PlayButton = std::make_unique<Button>(Window_Width / 4 + 150, 300.f, 200.f, 50.f, *s_Arcade_Font, "START", 30, sf::Color::Blue, sf::Color::Green);
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

static Tetromino CreateTetromino()
{
	int random = rand() % 7;
	TetrominoType type = GetTypeFromNumeration(random);
	Tetromino tetromino(type);
	return tetromino;
}

static void CommitBlock(const Tetromino& tetromino)
{
	int txc = tetromino.posX;
	int tyc = tetromino.posY + 1;

	for (int y = 0; y < tetromino.m_size; y++)
	{
		for (int x = 0; x < tetromino.m_size; x++)
		{
			if (tetromino.m_arr[y][x])
			{
				int xc = txc + x;
				int yc = tyc + y;
				int pos = xc + yc * GameBoard::Width;

				if (yc + 1 > GameBoard::Height)
				{
					std::cout << "[WARNING] : GameBoard height out of bounds" << std::endl;
					continue;
				}
				GameBoard::PlayingArea[pos] = GetColorInt(tetromino);
			}
		}
	}
}

static void ClearRow(sf::RenderWindow& window)
{
	for (int y = 0; y < GameBoard::Height; y++)
	{
		int count = 0;
		for (int x = 0; x < GameBoard::Width; x++)
		{
			int block = GameBoard::PlayingArea[x + y * GameBoard::Width];
			if (block) count += 1;
			if (count == GameBoard::Width)
			{
				std::cout << "row match" << std::endl;
				GetSound().PlayBreakSound();
				for (int x = 0; x < GameBoard::Width; x++) {
					int i = y;
					int j = 0;
					while (j < i)
					{
						GameBoard::PlayingArea[x + (y - j) * GameBoard::Width] = GameBoard::PlayingArea[x + (y - j - 1) * GameBoard::Width];
						j++;

					}
				}
			}
		}
	}
}

void GameLayer::OnInit()
{
	m_Sound.PlayGameStartSound();
	memset(GameBoard::PlayingArea.data(), 0, sizeof(GameBoard::PlayingArea));

	m_CurrentTetromino = CreateTetromino();
	m_PlayAgainButton = std::make_unique<Button>(770.f, 400.f, 350.f, 50.f, *s_Arcade_Font, "PLAY AGAIN", 30, sf::Color::Blue, sf::Color::Green);
	m_LastTime = clock.getElapsedTime().asSeconds();
}

void GameLayer::OnShutdown()
{

}

void GameLayer::OnUpdate()
{
	sf::RenderWindow& window = GetWindow();
	Database& database = GetDatabase();
	DrawGameBoard(window);
	m_CurrentTetromino.Draw(window);
	ClearRow(window);
	if (!s_GameOver)
	{
		DrawPoints(window, points);
		DrawUsername(window);
	}
	CheckGameOver(m_CurrentTetromino);

	sf::Vector2i mouse_position = sf::Mouse::getPosition(window);

	float now = clock.getElapsedTime().asSeconds();

	if (now - m_LastTime >= 0.7f)
	{
		m_CurrentTetromino.MoveDown(cell_size);
		m_LastTime = now;
	}

	if (m_CurrentTetromino.m_landed && !s_GameOver)
	{
		++points;
		CommitBlock(m_CurrentTetromino);
		m_Sound.PlayLandedSound();
		if (m_CurrentTetromino.posY <= 0 && m_CurrentTetromino.m_landed)
			s_GameOver = true;
		if (!s_GameOver)
			m_CurrentTetromino = CreateTetromino();
	}

	if (s_GameOver)
	{
		if (!m_db_updated)
		{
			m_Sound.PlayGameOverSound();
			database.InsertToScoreTable(s_Username, points);
			database.GetScoreList();
			m_db_updated = true;
		}

		sf::Text text;
		text.setFont(*s_Arcade_Font);
		text.setFillColor(sf::Color(254, 0, 2));
		text.setCharacterSize(60);
		text.setPosition(450, 50);
		std::string string = "GAME OVER";
		text.setString(string);
		window.draw(text);
		m_CurrentTetromino.m_color = sf::Color::Transparent;

		DrawGameBoard_GameOver(window);

		sf::Text score_text;
		score_text.setFont(*s_Arcade_Font);
		score_text.setFillColor(sf::Color::Yellow);
		score_text.setCharacterSize(60);
		score_text.setPosition(450, 150);
		std::string score_str = "SCORE : " + std::to_string(points);
		score_text.setString(score_str);
		window.draw(score_text);

		m_PlayAgainButton->DrawButton(window);
		m_PlayAgainButton->GetPressed(mouse_position);

		if (m_PlayAgainButton->m_buttonState == PRESSED)
		{
			s_GameOver = false;
			SetLayer(new TimerLayer());
		}
	}
}

void GameLayer::OnEvent(sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Left)
		{
			m_CurrentTetromino.posX -= cell_size;

			if (!m_CurrentTetromino.CheckBounds())
				m_CurrentTetromino.posX += cell_size;
		}

		if (event.key.code == sf::Keyboard::Right)
		{
			m_CurrentTetromino.posX += cell_size;

			if (!m_CurrentTetromino.CheckBounds())
				m_CurrentTetromino.posX -= cell_size;
		}

		if (event.key.code == sf::Keyboard::Down)
		{
			m_CurrentTetromino.MoveDown(cell_size);
		}

		if (event.key.code == sf::Keyboard::Up)
		{
			m_CurrentTetromino.Rotate_HardCoded(m_CurrentTetromino.m_rotation_state);
		}

		if (event.key.code == sf::Keyboard::Space)
		{

		}
	}
}

void ScoreBoardLayer::OnInit()
{
	Database& database = GetDatabase();
	database.GetScoreList();
	m_BackButton = std::make_unique<Button>(30.f, 30.f, 200.f, 50.f, *s_Arcade_Font, "BACK", 30, sf::Color::Blue, sf::Color::Green);

	int i = 2;
	int spacing = 150;
	int x = 350.f;

	m_title.setFont(*s_Arcade_Font);
	m_title.setCharacterSize(50);
	m_title.setFillColor(sf::Color::White);
	m_title.setPosition(300.f, 80.f);
	m_title.setString("HIGH SCORES");

	m_Gold_Texture.loadFromFile("first.png");
	m_Gold_Sprite.setTexture(m_Gold_Texture);
	m_Gold_Sprite.setScale(0.2f, 0.2f);
	m_Gold_Sprite.setPosition(x - 150.f, spacing * i - 20.f);

	m_score1.setFont(*s_Arcade_Font);
	m_score1.setFillColor(sf::Color::White);
	m_score1.setPosition(x + 300 , spacing * i);
	m_entry1.setFont(*s_Arcade_Font);
	m_entry1.setFillColor(sf::Color::White);
	m_entry1.setPosition(x, spacing * i++);

	m_Silver_Texture.loadFromFile("second.png");
	m_Silver_Sprite.setTexture(m_Silver_Texture);
	m_Silver_Sprite.setScale(0.2f, 0.2f);
	m_Silver_Sprite.setPosition(x - 150.f, spacing * i - 20.f);

	m_score2.setFont(*s_Arcade_Font);
	m_score2.setFillColor(sf::Color::White);
	m_score2.setPosition(x + 300, spacing * i);
	m_entry2.setFont(*s_Arcade_Font);
	m_entry2.setFillColor(sf::Color::White);
	m_entry2.setPosition(x, spacing * i++);

	m_Bronze_Texture.loadFromFile("third.png");
	m_Bronze_Sprite.setTexture(m_Bronze_Texture);
	m_Bronze_Sprite.setScale(0.2f, 0.2f);
	m_Bronze_Sprite.setPosition(x - 150.f, spacing * i - 20.f);

	m_score3.setFont(*s_Arcade_Font);
	m_score3.setFillColor(sf::Color::White);
	m_score3.setPosition(x + 300, spacing * i);
	m_entry3.setFont(*s_Arcade_Font);
	m_entry3.setFillColor(sf::Color::White);
	m_entry3.setPosition(x, spacing * i++);

	auto score_list = database.GetScoreList();
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
