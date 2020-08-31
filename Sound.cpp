#include "Sound.h"
#include <iostream>

void Sound::Init()
{
	m_Click_SoundBuffer.loadFromFile("click.ogg");
	m_Click_Sound.setBuffer(m_Click_SoundBuffer);

	m_Select_SoundBuffer.loadFromFile("select.ogg");
	m_Select_Sound.setBuffer(m_Select_SoundBuffer);

	m_GameOver_SoundBuffer.loadFromFile("gameOver.wav");
	m_GameOver_Sound.setBuffer(m_GameOver_SoundBuffer);

	m_Landed_SoundBuffer.loadFromFile("landed.wav");
	m_Landed_Sound.setBuffer(m_Landed_SoundBuffer);

	m_GameStart_SoundBuffer.loadFromFile("gameStart.wav");
	m_GameStart_Sound.setBuffer(m_GameStart_SoundBuffer);

	m_Break_SoundBuffer.loadFromFile("break.wav");
	m_Break_Sound.setBuffer(m_Break_SoundBuffer);
}



void Sound::PlaySelectSound()
{
	m_Select_Sound.play();
}

void Sound::PlayClickSound()
{
	m_Click_Sound.play();
}

void Sound::PlayGameOverSound()
{
	m_GameOver_Sound.play();
}

void Sound::PlayLandedSound()
{
	m_Landed_Sound.play();
}

void Sound::PlayGameStartSound()
{
	m_GameStart_Sound.play();
}

void Sound::PlayBreakSound()
{
	m_Break_Sound.play();
}
