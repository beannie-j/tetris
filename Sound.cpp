#include "Sound.h"
#include <iostream>

void Sound::Init()
{
	m_Click_SoundBuffer.loadFromFile("resources/click.ogg");
	m_Click_Sound.setBuffer(m_Click_SoundBuffer);

	m_Select_SoundBuffer.loadFromFile("resources/select.ogg");
	m_Select_Sound.setBuffer(m_Select_SoundBuffer);

	m_GameOver_SoundBuffer.loadFromFile("resources/gameOver.wav");
	m_GameOver_Sound.setBuffer(m_GameOver_SoundBuffer);

	m_Landed_SoundBuffer.loadFromFile("resources/landed.wav");
	m_Landed_Sound.setBuffer(m_Landed_SoundBuffer);

	m_GameStart_SoundBuffer.loadFromFile("resources/gameStart.wav");
	m_GameStart_Sound.setBuffer(m_GameStart_SoundBuffer);

	m_Break_SoundBuffer.loadFromFile("resources/break.wav");
	m_Break_Sound.setBuffer(m_Break_SoundBuffer);

	m_SoundMap.emplace(std::pair<std::string, sf::Sound>("click", m_Click_Sound));
	m_SoundMap.emplace(std::pair<std::string, sf::Sound>("select", m_Select_Sound));
	m_SoundMap.emplace(std::pair<std::string, sf::Sound>("game over", m_GameOver_Sound));
	m_SoundMap.emplace(std::pair<std::string, sf::Sound>("landed", m_Landed_Sound));
	m_SoundMap.emplace(std::pair<std::string, sf::Sound>("start", m_GameStart_Sound));
	m_SoundMap.emplace(std::pair<std::string, sf::Sound>("break", m_Break_Sound));

}

void Sound::Play(std::string name)
{
	auto it = m_SoundMap.find(name);
	if (it == m_SoundMap.end())
	{	// not found
		m_Click_Sound.play();
	}
	else it->second.play();
}