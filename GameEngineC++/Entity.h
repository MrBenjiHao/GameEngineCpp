#ifndef ENTITY_H
#define ENTITY_H
#include "GameObject.h"

#define PI 3.14159265358979323846
#define radians (PI / 180)
#define degrees (180 / PI)

class GameState;

class Entity : public GameObject{
protected:
	enum EntityType{PLAYER, ENEMY, ARROW, TILE};

	sf::Texture* texture;
	GameState* gameState;
	EntityType entityType;
	int ticks;

	void loadSprite(int x, int y, int width, int height);
	void setEntityType(EntityType type);
public:
	float x, y;
	float scale;
	int width, height;
	bool textureLoaded;
	bool isRemoved;
	sf::Sprite sprite;

	Entity(){};
	Entity(float x, float y, int width, int height, GameState* gameState);
	virtual ~Entity(); // Virtual so derived classes can define own destruction when deleted

	virtual void update() = 0;
	virtual void render(sf::RenderWindow* window) = 0;
	bool collidesWith(Entity* e2, bool globalPos = true);
	void remove();
	EntityType getEntityType();
	bool onScreen();
};

#endif