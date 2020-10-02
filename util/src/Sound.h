#pragma once
#include <SFML/Audio.hpp>
#include <map>

class Sound
{
public:
	sf::SoundBuffer m_Click_SoundBuffer;
	sf::Sound m_Click_Sound;

	sf::SoundBuffer m_Select_SoundBuffer;
	sf::Sound m_Select_Sound;

	sf::SoundBuffer m_GameOver_SoundBuffer;
	sf::Sound m_GameOver_Sound;

	sf::SoundBuffer m_Landed_SoundBuffer;
	sf::Sound m_Landed_Sound;

	sf::SoundBuffer m_GameStart_SoundBuffer;
	sf::Sound m_GameStart_Sound;

	sf::SoundBuffer m_Break_SoundBuffer;
	sf::Sound m_Break_Sound;

	std::map<std::string, sf::Sound> m_SoundMap;

	void Init();
	void Play(std::string name);
};

