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
#include "Database.h"

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