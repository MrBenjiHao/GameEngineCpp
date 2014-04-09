#ifndef GAMESTATE_H
#define GAMESTATE_H
#include <vector>
#include "SFML/Graphics.hpp"
#include "SoundManager.h"

class Core;
class Player;
class Entity;
class Map;

class GameState{
private:
	void loadTextures();
	void init();
	Player* player;
public:
	sf::RectangleShape slash;
	sf::Texture mainSheet;
	std::vector<Entity*> entities;
	std::vector<sf::RectangleShape> slashes;
	SoundManager sounds;
	Core* core;
	Map* map;
	int ticks;
	bool gameOver;

	GameState(Core* core);
	virtual ~GameState();

	void update();
	void render(sf::RenderWindow* window);
	void removeEntities();
	void spawnEnemies(int rate);
	void spawnParticle(int x, int y, float angle);
	Player getPlayer();
};

#endif