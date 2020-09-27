#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "Menu.h"
#include "Button.h"
#include "TextBox.h"
#include "Tetromino.h"
#include "Database.h"
#include <vector>
#include <string>
#include <chrono>
#include "Sound.h"
#include <stack>
#include <deque>

class Layer
{
public:
	Layer() = default;
	virtual ~Layer() = default;
	Database& m_Database = GetDatabase();
	// make sure &m_sound not m_Sound
	Sound& m_Sound = GetSound();
	// Sound m_Sound = GetSound();- this just copies
	//basically calls Sound(const Sound&)
	//Sound* m_Sound = GetSound();

	virtual void OnInit() {}
	virtual void OnShutdown() {}

	virtual void OnUpdate() {}
	virtual void OnEvent(sf::Event& event) {}
};

class GameLayer : public Layer
{
public:
	virtual void OnInit() override;
	virtual void OnShutdown() override;

	virtual void OnUpdate() override;
	virtual void OnEvent(sf::Event& event) override;
	void SpawnNextBlock();
private:
	Tetromino m_CurrentTetromino;
	Tetromino m_NextTetromino;
	std::deque<int> m_Tetromino_queue;

	sf::Clock clock;
	float m_LastTime = 0.0f;
	int points = 0;
	std::unique_ptr<Button> m_PlayAgainButton;
	bool m_db_updated = false;
	std::unique_ptr<Button> m_BackButton;
	sf::Text m_NextTetrominoText;
	sf::RectangleShape m_NextTetrominoBox;

	void DrawUsername(sf::RenderWindow& window);
	void DrawPoints(sf::RenderWindow& window, int points);
	int GetColorInt(Tetromino tetromino);
	TetrominoType GetTypeFromNumeration(int number);
	bool CheckGameOver(Tetromino curr);
	void PaintGameBoardRed(sf::RenderWindow& window);
	void DrawGameBoard(sf::RenderWindow& window);
	void CheckAndFillQueue(std::deque<int>& deque);
	Tetromino CreateTetromino(std::deque<int>& deque);
	void CommitBlock(const Tetromino& tetromino);
	void ClearRow(sf::RenderWindow& window);








};

class MainMenuLayer : public Layer
{
public:
	virtual void OnInit() override;
	virtual void OnShutdown() override;

	virtual void OnUpdate() override;
	virtual void OnEvent(sf::Event& event) override;
private:
	std::unique_ptr<Menu> m_Menu;
};

class TimerLayer : public Layer
{
public:
	virtual void OnInit() override;
	virtual void OnShutdown() override;

	virtual void OnUpdate() override;
	virtual void OnEvent(sf::Event& event) override;
private:
	sf::Text m_game_start_text;
	sf::Text m_timer_text;
	std::chrono::time_point<std::chrono::system_clock> m_SecondsSinceStart = std::chrono::system_clock::now();
	int m_timer = 3;
};

class PreGameLayer : public Layer
{
public:
	virtual void OnInit() override;
	virtual void OnShutdown() override;

	virtual void OnUpdate() override;
	virtual void OnEvent(sf::Event& event) override;
private:
	std::unique_ptr<TextBox> m_TextBox;
	std::unique_ptr<Button> m_PlayButton;
	std::unique_ptr<Button> m_BackButton;
};

class ScoreBoardLayer : public Layer
{
public:
	virtual void OnInit() override;
	virtual void OnShutdown() override;

	virtual void OnUpdate() override;
	virtual void OnEvent(sf::Event& event) override;
private:
	std::unique_ptr<Button> m_BackButton;

	sf::Texture m_Gold_Texture;
	sf::Sprite m_Gold_Sprite;

	sf::Texture m_Silver_Texture;
	sf::Sprite m_Silver_Sprite;

	sf::Texture m_Bronze_Texture;
	sf::Sprite m_Bronze_Sprite;

	sf::Text m_title;

	sf::Text m_entry1;
	sf::Text m_score1;

	sf::Text m_entry2;
	sf::Text m_score2;

	sf::Text m_entry3;
	sf::Text m_score3;
};
