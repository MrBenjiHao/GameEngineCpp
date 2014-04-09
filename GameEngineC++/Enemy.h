#ifndef ENEMY_H
#define ENEMY_H
#include "Entity.h"

class Animation;
class Player;

class Enemy : public Entity{
public:
	Enemy(float x, float y, int width, int height, GameState* gameState);
	~Enemy();

	Animation* move;
	Animation* down, *up, *left, *right;
	float xVel, yVel, speed, angle;
	bool attacking, dashing;
	float dx, dy, distanceTraveled, dashDistance;
	float attackDelay, chargeDelay;

	void update();
	void render(sf::RenderWindow* window);
	void movement();
	void setSpeed(float speed);
	void setAnimations();
	void setAnimationDirection(float newAngle);
	void attack(Player* player, float newAngle);
};

#endif