#ifndef GAMESTATE_H
#define GAMESTATE_H
#include <vector>
#include "SFML/Graphics.hpp"
#include "SoundManager.h"
#include "Map.h"
#include "Player.h"

class Core;
class Player;
class Entity;

class GameState{
private:
	void loadTextures();
	void init();
	Player player;
public:
	sf::RectangleShape slash;
	sf::Texture mainSheet;
	std::vector<Entity*> entities;
	std::vector<sf::RectangleShape> slashes;
	SoundManager sounds;
	Core* core;
	Map map;
	int ticks;
	bool gameOver;

	GameState(Core* core);
	virtual ~GameState();

	void update();
	void render(sf::RenderWindow* window);
	void removeEntities();
	void spawnEnemies(int rate, int perSec);
	void spawnParticle(int x, int y, float angle);
	void initSlash();
	Player getPlayer();
};

#endif