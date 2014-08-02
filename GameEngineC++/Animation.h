#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include "SFML/Graphics.hpp"

class Entity;

class Animation{
private:
	bool START, STOP, PLAYING;
	int animationSpeed, ticks, frame;
	std::vector<sf::IntRect> frames;
	Entity* entity;
public:
	Animation(){};
	Animation(Entity* entity);

	void addFrame(int x, int y, int width, int height);
	void setAnimateSpeed(int speed);
	void update();
	void start();
	void stop();
	bool isPlaying();
};

#endif