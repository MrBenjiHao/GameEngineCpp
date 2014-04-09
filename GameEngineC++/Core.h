#ifndef CORE_H
#define CORE_H
#include "SFML/Graphics.hpp"
#include "Input.h"
class GameState;

class Core{
public:
	GameState* gameState;
	int WIDTH;
	int HEIGHT;
	const sf::RenderWindow* WINDOW;
	Input inputManager;
	int delay;

	Core();
	~Core();

	void start();
	void update();
	void render(sf::RenderWindow* window);
	void initStates();
};

#endif