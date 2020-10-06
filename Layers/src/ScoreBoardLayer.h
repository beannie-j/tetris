#pragma once

#include "Layer.h"
#include "Button.h"


#include <SFML/Graphics.hpp>
#include <memory>

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


