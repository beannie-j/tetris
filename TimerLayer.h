#pragma once
#include "Layer.h"
#include <chrono> 
#include <ctime> 

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

