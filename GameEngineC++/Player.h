#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Animation;

class Player : public Entity{
private:
	float xVel, yVel;
	int fireRate;
	float distanceTraveled, dashDistance;
	float dx;
	float dy;
	float angle;
	sf::Vector2i position;
	sf::Sprite sword;
	Animation* move;
	Animation* down, *up, *left, *right;

	void movement();
	void setAnimations();
	void setAnimationDirection(float newAngle);
	void dash(float angle);
	void setSwordPos();
	void enemyCollision(float angleTrajectory);
public:
	Player(){};
	Player(float x, float y, int width, int height, GameState* gameState);

	bool dashing;
	int delay;

	void update();
	void render(sf::RenderWindow* window);
};

#endif