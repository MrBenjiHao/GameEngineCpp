#ifndef MAP_H
#define MAP_H

#include <vector>
#include "SFML\Graphics.hpp"

class GameState;

class Map{
public:
	Map(GameState* gameState);

	GameState* gameState;
	std::vector<sf::RectangleShape> tiles;

	void loadMap(int width, int height);
	void update();
	void render(sf::RenderWindow *window);

	static void doSomething(); // only name it static in the interface
};

#endif