#include "SoundManager.h"

SoundManager::SoundManager(){
	DASH_01.loadFromFile("Resources/dash03.wav");
	DASH_02.loadFromFile("Resources/dash04.wav");
	SLASH_01.loadFromFile("Resources/slash01.wav");
	SLASH_02.loadFromFile("Resources/slash02.wav");
	SLASH_03.loadFromFile("Resources/slash03.wav");
	SLASH_04.loadFromFile("Resources/slash04.wav");
	HIT_01.loadFromFile("Resources/hit02.wav");

	dash_01.setBuffer(DASH_01);
	dash_01.setVolume(25);
	dash_02.setBuffer(DASH_02);
	dash_02.setVolume(25);
	slash_01.setBuffer(SLASH_01);
	slash_01.setVolume(50);
	slash_02.setBuffer(SLASH_02);
	slash_02.setVolume(50);
	slash_03.setBuffer(SLASH_03);
	slash_03.setVolume(50);
	slash_04.setBuffer(SLASH_04);
	slash_04.setVolume(50);
	hit_01.setBuffer(HIT_01);

	dashes[0] = dash_01;
	dashes[1] = dash_02;
	slashes[0] = slash_01;
	slashes[1] = slash_02;
	slashes[2] = slash_03;
	slashes[3] = slash_04;
}