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
#include "Application.h"

class Application;
Application& GetApplication();

class Layer
{
public:
	Layer() = default;
	virtual ~Layer() = default;

	Application& m_Application = GetApplication();
	Database& m_Database = m_Application.GetDatabase();
	Sound& m_Sound = m_Application.GetSound();

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

	// why can't I do this in the header file?
	//TetrominoType type = TetrominoType::I;
	//Tetromino m_NextTetromino(type);

	sf::Clock clock;
	float m_LastTime = 0.0f;
	int points = 0;
	std::unique_ptr<Button> m_PlayAgainButton;
	bool m_db_updated = false;
	std::unique_ptr<Button> m_BackButton;
	sf::Text m_NextTetrominoText;
	sf::RectangleShape m_NextTetrominoBox;
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


