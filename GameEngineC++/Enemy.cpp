#include "Enemy.h"
#include "GameState.h"
#include "Player.h"
#include <iostream>
#include "Animation.h"

Enemy::Enemy(float x, float y, int width, int height, GameState* gameState)
	: Entity(x, y, width, height, gameState), xVel(0.0), yVel(0.0), speed(0.0), angle(0.0){
	setEntityType(ENEMY);

	this->scale = 1.2;
	sprite.setOrigin(width / 2, height / 2);

	loadSprite(3 * width, 0 * height, width, height);
	setSpeed(1.5);

	setAnimations();

	attacking = false;
	dashing = false;
	dx = 0.0;
	dy = 0.0;
	distanceTraveled = 0.0;
	dashDistance = 90.0;
}

Enemy::~Enemy(){
	delete up;
	delete down;
	delete left;
	delete right;
}

void Enemy::update(){
	Entity::update();
	move->update();

	movement();
}

void Enemy::render(sf::RenderWindow* window){
	Entity::render(window);
}

void Enemy::setAnimations(){
	int frameSpeed = 8;

	up = new Animation(this);
	up->setAnimateSpeed(frameSpeed);
	up->addFrame(4 * 32, 3 * 32, 32, 32);
	up->addFrame(3 * 32, 3 * 32, 32, 32);
	up->addFrame(4 * 32, 3 * 32, 32, 32);
	up->addFrame(5 * 32, 3 * 32, 32, 32);

	down = new Animation(this);
	down->setAnimateSpeed(frameSpeed);
	down->addFrame(4 * 32, 0 * 32, 32, 32);
	down->addFrame(3 * 32, 0 * 32, 32, 32);
	down->addFrame(4 * 32, 0 * 32, 32, 32);
	down->addFrame(5 * 32, 0 * 32, 32, 32);

	left = new Animation(this);
	left->setAnimateSpeed(frameSpeed);
	left->addFrame(4 * 32, 1 * 32, 32, 32);
	left->addFrame(3 * 32, 1 * 32, 32, 32);
	left->addFrame(4 * 32, 1 * 32, 32, 32);
	left->addFrame(5 * 32, 1 * 32, 32, 32);

	right = new Animation(this);
	right->setAnimateSpeed(frameSpeed);
	right->addFrame(4 * 32, 2 * 32, 32, 32);
	right->addFrame(3 * 32, 2 * 32, 32, 32);
	right->addFrame(4 * 32, 2 * 32, 32, 32);
	right->addFrame(5 * 32, 2 * 32, 32, 32);

	move = down;
}

void Enemy::movement(){
	Player player = gameState->getPlayer();

	float distance = sqrt(pow(player.x - x, 2) + pow(player.y - y, 2));
	float newAngle = atan2(player.y - y, player.x - x);

	if(attackDelay <= 0.0){
		if(!attacking){
			if(distance >= 100){
				move->start();

				xVel = speed * cos(newAngle);
				yVel = speed * sin(newAngle);

				x += xVel;
				y += yVel;

				sprite.setColor(sf::Color::White);
			}
			else{
				attacking = true;
				move->stop();
			}
		}
		else attack(&player, newAngle);
	}
	else attackDelay--;

	setAnimationDirection(newAngle);

	sprite.setPosition(x, y);
}

void Enemy::attack(Player* player, float newAngle){
	float dashSpeed = 10.0;
	if(!dashing){
		dashing = true;
		distanceTraveled = 0.0;
		dx = dashSpeed * cos(newAngle);
		dy = dashSpeed * sin(newAngle);
		chargeDelay = 75.0;
	}
	else{
		if(chargeDelay <= 0.0){
			move->stop();
			x += dx;
			y += dy;
			distanceTraveled += (abs(dx) + abs(dy)) / 2;
			if(distanceTraveled >= dashDistance){
				dashing = false;
				attacking = false;
				distanceTraveled = 0.0;
				dx = 0.0;
				dy = 0.0;
				attackDelay = 30.0;
			}
			if(collidesWith(player, true)){
				if(!player->dashing){
					gameState->gameOver = true;
					gameState->sounds.hit_01.play();
				}
			}
		}
		else {
			dx = dashSpeed * cos(newAngle);
			dy = dashSpeed * sin(newAngle);
			chargeDelay--;
			// Flashing red to indicate an attack
			if(ticks % 25 == 0) sprite.setColor(sf::Color::Red);
			else if(ticks % 26 == 0) sprite.setColor(sf::Color::White);
		}
	}
}

void Enemy::setAnimationDirection(float newAngle){
	newAngle *= degrees;
	if(newAngle < 0) newAngle += 360;
	if(newAngle < 135 && newAngle > 45) move = down;
	else if(newAngle  < 315 && newAngle > 225) move = up;
	else if((newAngle < 360 && newAngle > 315) || (newAngle > 0 && newAngle < 45)) move = right;
	else if(newAngle > 135 && newAngle < 225) move = left;
}

void Enemy::setSpeed(float speed){
	this->speed = speed;
}
