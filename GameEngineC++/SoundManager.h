#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include "SFML\Audio.hpp"

class SoundManager{
public:
	sf::SoundBuffer DASH_01;
	sf::SoundBuffer DASH_02;
	sf::SoundBuffer SLASH_01;
	sf::SoundBuffer SLASH_02;
	sf::SoundBuffer SLASH_03;
	sf::SoundBuffer SLASH_04;
	sf::SoundBuffer HIT_01;
	sf::Sound dash_01;
	sf::Sound dash_02;
	sf::Sound slash_01;
	sf::Sound slash_02;
	sf::Sound slash_03;
	sf::Sound slash_04;
	sf::Sound hit_01;

	sf::Sound dashes[2];
	sf::Sound slashes[4];

	SoundManager();
private:
	void initSounds();
};

#endif