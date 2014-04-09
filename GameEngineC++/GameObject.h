#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "SFML\Graphics.hpp"

class GameObject{
public:
	virtual void update() = 0;
	virtual void render(sf::RenderWindow* window) = 0;
};

#endif