#pragma once

#include <SFML/Window/Event.hpp>

class Layer
{
public:
	Layer() = default;
	virtual ~Layer() = default;

	virtual void OnInit() {}
	virtual void OnShutdown() {}

	virtual void OnUpdate() {}
	virtual void OnEvent(sf::Event& event) {}
};