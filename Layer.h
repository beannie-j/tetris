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

class Layer
{
public:
	Layer() = default;
	virtual ~Layer() = default;
	Database m_database;

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
private:
	Tetromino m_CurrentTetromino;
	sf::Clock clock;
	float m_LastTime = 0.0f;
	int points = 0;
	std::unique_ptr<Button> m_PlayAgainButton;
	bool m_db_updated = false;
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
	sf::Text m_timer_text;
	std::chrono::time_point<std::chrono::system_clock> m_SecondsSinceStart = std::chrono::system_clock::now();
	bool m_timer_is_up = false;
	bool m_1second_mark = false;
	bool m_2second_mark = false;
	bool m_3second_mark = false;
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

	sf::Text m_title;

	sf::Text m_entry1;
	sf::Text m_score1;

	sf::Text m_entry2;
	sf::Text m_score2;

	sf::Text m_entry3;
	sf::Text m_score3;

	sf::Text m_entry4;
	sf::Text m_score4;
	
	sf::Text m_entry5;
	
	sf::Text m_entry6;
	
	sf::Text m_entry7;
	
	sf::Text m_entry8;
	
	sf::Text m_entry9;
	
	sf::Text m_entry10;
};


