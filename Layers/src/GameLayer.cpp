#include "GameLayer.h"
#include "MainMenuLayer.h"
#include "TimerLayer.h"
#include "../../Tetris/src/Application.h"
#include "../../util/src/Timestep.h"

bool GameLayer::s_GameOver = false;


void GameLayer::DrawUsername(sf::RenderWindow& window)
{
	auto& app = Application::GetApplication();
	sf::Font& font = app.GetFont();
	sf::Text text;
	text.setFont(font);
	text.setFillColor(sf::Color::White);
	text.setCharacterSize(30);
	text.setPosition(700, 70);
	std::string string = "PLAYER : " + Application::s_Username;
	text.setString(string);
	window.draw(text);
}

void GameLayer::DrawPoints(sf::RenderWindow& window, int points)
{
	auto& app = Application::GetApplication();
	sf::Font& font = app.GetFont();
	sf::Text text;
	text.setFont(font);
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

int GameLayer::GetColorInt(Tetromino tetromino)
{
	if (tetromino.m_type == TetrominoType::I) return 2;
	if (tetromino.m_type == TetrominoType::O) return 3;
	if (tetromino.m_type == TetrominoType::T) return 4;
	if (tetromino.m_type == TetrominoType::S) return 5;
	if (tetromino.m_type == TetrominoType::Z) return 6;
	if (tetromino.m_type == TetrominoType::J) return 7;
	if (tetromino.m_type == TetrominoType::L) return 8;
	// assert()
	return 0;
}

TetrominoType GameLayer::GetTypeFromNumeration(int number)
{
	switch (number)
	{
		case 0: return TetrominoType::I;
		case 1: return TetrominoType::O;
		case 2: return TetrominoType::T;
		case 3: return TetrominoType::S;
		case 4: return TetrominoType::Z;
		case 5: return TetrominoType::J;
		case 6: return TetrominoType::L;
	}
	//asert()
	return TetrominoType::I;
}

bool GameLayer::CheckGameOver(Tetromino curr)
{
	// still broken..
	// check Tetromino fits
	for (int y = 0; y < curr.m_size; y++)
	{
		for (int x = 0; x < curr.m_size; x++)
		{
			if (curr.m_arr[y][x] == 0) continue;
			if (curr.CollisionWithBlocks(0, 0) && curr.TopBoundsCollision())
			{
				s_GameOver = true;
			}
		}
	}
	return true;
}

void GameLayer::PaintGameBoardRed(sf::RenderWindow& window)
{
	sf::RectangleShape rect(sf::Vector2f(Tetromino::block_size, Tetromino::block_size));

	for (int y = 0; y < GameBoard::Height; y++)
	{
		for (int x = 0; x < GameBoard::Width; x++)
		{
			float cx = (x + Application::s_shift) * Tetromino::block_size;
			float cy = (y + Application::s_shift) * Tetromino::block_size;
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

void GameLayer::DrawGameBoard(sf::RenderWindow& window)
{
	sf::RectangleShape rect(sf::Vector2f(Tetromino::block_size, Tetromino::block_size));
	// this is for debugging purposes - don't delete
	/*
	sf::Text text;
	sf::Font font;
	font.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf");
	text.setFont(font);

	text.setFillColor(sf::Color(255, 255, 255));
	text.setCharacterSize(14);
	*/

	for (int y = 0; y < GameBoard::Height; y++)
	{
		for (int x = 0; x < GameBoard::Width; x++)
		{
			float cx = (x + Application::s_shift) * Tetromino::block_size;
			float cy = (y + Application::s_shift) * Tetromino::block_size;
			int block = GameBoard::PlayingArea[x + y * GameBoard::Width];
			if (block >= 2)
			{
				rect.setPosition(sf::Vector2f(cx, cy));
				//rect.setOutlineThickness(3);
				rect.setFillColor(Tetromino::s_Colors[block]);
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

				//this is for debugging purposes - don't delete
				/*
				text.setPosition(sf::Vector2f(cx, cy));
				std::string string = std::to_string(x) + ", " + std::to_string(y);
				text.setString(string);
				window.draw(text);
				*/
			}
		}
	}
}

void GameLayer::CheckAndFillQueue(std::deque<int>& deque)
{
	if (deque.size() < 2)
	{
		for (int i = 0; i < 15; i++)
		{
			int random = rand() % 7;
			deque.push_back(random);
			//std::cout << random << " ,";
		}
	}
}

Tetromino GameLayer::CreateTetromino(std::deque<int>& deque)
{
	TetrominoType type = GetTypeFromNumeration(deque.front());
	Tetromino tetromino(type);

	deque.pop_front();

	for (size_t i = 0; i < deque.size(); i++)
	{
		//std::cout << deque[i] << " ,";
	}
	//std::cout << "\n";
	CheckAndFillQueue(deque);

	return tetromino;
}

void GameLayer::CommitBlock(const Tetromino& tetromino)
{
	int txc = (int)tetromino.posX;
	int tyc = (int)tetromino.posY;

	for (int y = 0; y < tetromino.m_size; y++)
	{
		for (int x = 0; x < tetromino.m_size; x++)
		{
			if (tetromino.m_arr[y][x])
			{
				int xc = txc + x;
				int yc = tyc + y;
				int pos = xc + yc * GameBoard::Width;
				/*if (yc + 1 > GameBoard::Height)
				{
					std::cout << "[WARNING] : GameBoard height out of bounds" << std::endl;
					continue;
				}*/
				GameBoard::PlayingArea[pos] = GetColorInt(tetromino);
			}
		}
	}
}

void GameLayer::ClearRow(sf::RenderWindow& window)
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
				auto& app = Application::GetApplication();
				app.GetSound().Play("break");
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
	auto& app = Application::GetApplication();
	app.GetSound().Play("start");
	sf::Font& font = app.GetFont();
	memset(GameBoard::PlayingArea.data(), 0, sizeof(GameBoard::PlayingArea));

	CheckAndFillQueue(m_Tetromino_queue);

	TetrominoType type = GetTypeFromNumeration(m_Tetromino_queue[1]);
	Tetromino tetromino(type);
	m_NextTetromino = tetromino;
	m_CurrentTetromino = CreateTetromino(m_Tetromino_queue);
	m_NextTetromino.posX = 14.0;
	m_NextTetromino.posY = 4.0;

	m_BackButton = std::make_unique<Button>(30.f, 30.f, 200.f, 50.f, font, "BACK", 30, sf::Color::Blue, sf::Color::Green);
	m_PlayAgainButton = std::make_unique<Button>(750.f, 700.f, 350.f, 50.f, font, "PLAY AGAIN", 30, sf::Color::Blue, sf::Color::Green);

	m_LastTime = clock.getElapsedTime().asSeconds();

	m_NextTetrominoText.setFont(font);
	m_NextTetrominoText.setFillColor(sf::Color::White);
	m_NextTetrominoText.setCharacterSize(30);
	m_NextTetrominoText.setPosition(830, 350);
	m_NextTetrominoText.setString("NEXT");

	m_NextTetrominoBox.setSize(sf::Vector2f(300, 200));
	m_NextTetrominoBox.setPosition(sf::Vector2f(750, 400));
	m_NextTetrominoBox.setFillColor(sf::Color(128, 128, 128));
}

void GameLayer::OnShutdown()
{

}

void GameLayer::SpawnNextBlock()
{
	if (!s_GameOver)
	{
		TetrominoType type = GetTypeFromNumeration(m_Tetromino_queue[1]);
		Tetromino tetromino(type);
		m_NextTetromino = tetromino;
		m_NextTetromino.posX = 14.0;
		m_NextTetromino.posY = 4.0;
		m_CurrentTetromino = CreateTetromino(m_Tetromino_queue);
	}
}

float delay = 0.0f;

void GameLayer::OnUpdate()
{
	auto& app = Application::GetApplication();
	sf::RenderWindow& window = app.GetWindow();
	sf::Font& font = app.GetFont();
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

	if (now - m_LastTime >= 0.6f)
	{
		// if no collision
		if (!m_CurrentTetromino.CollisionWithBlocks(0, 1))
		{
			// inside this 0.6f block because cell size increases every 0.6 seconds.
			m_CurrentTetromino.posY += m_CurrentTetromino.cell_size;
		}
		// if there is collision
		else
		{
			if (!s_GameOver)
			{
				++points;
				CommitBlock(m_CurrentTetromino);
				app.GetSound().Play("landed");
				SpawnNextBlock();
			}
		}
		m_LastTime = now;
	}

	float time = (float)clock.getElapsedTime().asSeconds();
	Timestep ts = time - m_LastFrameTime;// delta time
	m_LastFrameTime = time;

	m_Delay += ts.GetSeconds();

	//std::cout << "Delat time: {0}s ({1}ms) " << ts.GetSeconds() << std::endl;

	if (m_CurrentTetromino.YBoundsCollision())
	{
		if (!s_GameOver)
		{
			++points;
			CommitBlock(m_CurrentTetromino);
			app.GetSound().Play("landed");
			// need to delay spawning next block.
			SpawnNextBlock();		
		}
	}

	if (m_CurrentTetromino.XLeftBoundsCollision())
	{
		m_CurrentTetromino.posX += m_CurrentTetromino.cell_size;
	}

	if (m_CurrentTetromino.XRightBoundsCollision())
	{
		m_CurrentTetromino.posX -= m_CurrentTetromino.cell_size;
	}

	m_BackButton->DrawButton(window);
	m_BackButton->GetPressed(mouse_position);

	window.draw(m_NextTetrominoBox);
	window.draw(m_NextTetrominoText);
	m_NextTetromino.Draw(window);

	if (m_BackButton->m_buttonState == PRESSED)
	{
		std::cout << "[INFO] Back Button pressed" << std::endl;
		app.GetSound().Play("select");
		s_GameOver = false;
		app.SetLayer(new MainMenuLayer());
	}

	if (s_GameOver)
	{
		if (!m_db_updated)
		{
			app.GetSound().Play("game over");
			app.GetDatabase().InsertToScoreTable(Application::s_Username, points);
			app.GetDatabase().GetScoreList();
			m_db_updated = true;
		}

		// draw game over
		sf::Text text;
		text.setFont(font);
		text.setFillColor(sf::Color(254, 0, 2));
		text.setCharacterSize(60);
		text.setPosition(450, 50);
		std::string string = "GAME OVER";
		text.setString(string);
		window.draw(text);

		m_CurrentTetromino.m_color = sf::Color::Transparent;
		PaintGameBoardRed(window);

		// draw score
		sf::Text score_text;
		score_text.setFont(font);
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
			app.SetLayer(new TimerLayer());
		}
	}
}

void GameLayer::OnEvent(sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Left)
		{
			m_CurrentTetromino.posX -= m_CurrentTetromino.cell_size;

			if (m_CurrentTetromino.XLeftBoundsCollision())
			{
				m_CurrentTetromino.posX += m_CurrentTetromino.cell_size;
			}

			if (m_CurrentTetromino.CollisionWithBlocks(0, 0))
			{
				m_CurrentTetromino.posX += m_CurrentTetromino.cell_size;
			}
		}

		if (event.key.code == sf::Keyboard::Right)
		{
			m_CurrentTetromino.posX += m_CurrentTetromino.cell_size;

			if (m_CurrentTetromino.XRightBoundsCollision())
			{
				m_CurrentTetromino.posX -= m_CurrentTetromino.cell_size;
			}

			if (m_CurrentTetromino.CollisionWithBlocks(0, 0))
			{
				m_CurrentTetromino.posX -= m_CurrentTetromino.cell_size;
			}
		}

		if (event.key.code == sf::Keyboard::Down)
		{
			m_CurrentTetromino.posY += m_CurrentTetromino.cell_size;

			if (m_CurrentTetromino.YBoundsCollision())
			{
				m_CurrentTetromino.posY -= m_CurrentTetromino.cell_size;
			}

			if (m_CurrentTetromino.CollisionWithBlocks(0, 0))
			{
				m_CurrentTetromino.posY -= m_CurrentTetromino.cell_size;
			}
		}

		if (event.key.code == sf::Keyboard::Up)
		{
			// if rotation will go outside the game board - what needs to be done??

			m_CurrentTetromino.Rotate_HardCoded(m_CurrentTetromino.m_rotation_state);

			if (m_CurrentTetromino.XLeftBoundsCollision())
			{
				m_CurrentTetromino.posX += m_CurrentTetromino.cell_size;
				std::cout <<"x : " << m_CurrentTetromino.posX << std::endl;
			}

			if (m_CurrentTetromino.XRightBoundsCollision())
			{
				m_CurrentTetromino.posX -= m_CurrentTetromino.cell_size;
				std::cout << "x : " << m_CurrentTetromino.posX << std::endl;

			}
		}

		if (event.key.code == sf::Keyboard::Space)
		{

		}
	}
}