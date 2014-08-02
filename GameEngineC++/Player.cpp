#include "Player.h"
#include "GameState.h"
#include "Core.h"
#include <iostream>
#include "Animation.h"

Player::Player(float x, float y, int width, int height, GameState* gameState)
	: Entity(x, y, width, height, gameState), angle(0.0), xVel(0.0), yVel(0.0), fireRate(0), dashing(false), distanceTraveled(0), dashDistance(90), dx(0), dy(0), delay(0){
	setEntityType(PLAYER);

	// Setting up player sprite
	this->scale = 1.2;
	sprite.setOrigin((width) / 2, (height) / 2);
	loadSprite(1 * 32, 0 * 32, 32, 32);

	// Setting up the sword sprite
	setAnimations();
	sword.setTexture(gameState->mainSheet);
	sword.setTextureRect(sf::IntRect(129, 128, 23, 80));
	sword.setOrigin(23 / 2, 80 / 2);
	sword.setScale(.5, .5);
}

void Player::update(){
	Entity::update();

	movement();
	move->update();

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
		x = gameState->core->WIDTH / 2;
		y = gameState->core->HEIGHT / 2;
		sprite.setPosition(this->x, this->y);
	}
}

void Player::render(sf::RenderWindow* window){
	Entity::render(window);
	if(dashing || delay > 0) window->draw(sword);
}

void Player::setAnimations(){
	int frameSpeed = 8;

	up = Animation(this);
	up.setAnimateSpeed(frameSpeed);
	up.addFrame(1 * 32, 3 * 32, 32, 32);
	up.addFrame(0 * 32, 3 * 32, 32, 32);
	up.addFrame(1 * 32, 3 * 32, 32, 32);
	up.addFrame(2 * 32, 3 * 32, 32, 32);

	down = Animation(this);
	down.setAnimateSpeed(frameSpeed);
	down.addFrame(1 * 32, 0 * 32, 32, 32);
	down.addFrame(0 * 32, 0 * 32, 32, 32);
	down.addFrame(1 * 32, 0 * 32, 32, 32);
	down.addFrame(2 * 32, 0 * 32, 32, 32);

	left = Animation(this);
	left.setAnimateSpeed(frameSpeed);
	left.addFrame(1 * 32, 1 * 32, 32, 32);
	left.addFrame(0 * 32, 1 * 32, 32, 32);
	left.addFrame(1 * 32, 1 * 32, 32, 32);
	left.addFrame(2 * 32, 1 * 32, 32, 32);

	right = Animation(this);
	right.setAnimateSpeed(frameSpeed);
	right.addFrame(1 * 32, 2 * 32, 32, 32);
	right.addFrame(0 * 32, 2 * 32, 32, 32);
	right.addFrame(1 * 32, 2 * 32, 32, 32);
	right.addFrame(2 * 32, 2 * 32, 32, 32);

	move = &down;
}

void Player::movement(){
	float speed = 3.0;

	// Getting position of the mouse relative to the window
	// Calulating the angle between player and mouse position
	position = sf::Mouse::getPosition(*gameState->core->WINDOW);
	float newAngle = atan2(position.y - this->y, position.x - this->x);

	if(delay <= 0){
		if(!dashing){
			float distance = sqrt(pow(position.x - x, 2) + pow(position.y - y, 2));
			if(distance > 50.0){
				move->start();
				xVel = speed * cos(newAngle);
				yVel = speed * sin(newAngle);
				x += xVel;
				y += yVel;
			}
			else move->stop();
		}
		dash(newAngle);
	}
	else delay--;

	enemyCollision(newAngle);

	setAnimationDirection(newAngle);

	sprite.setPosition(this->x, this->y);
}

void Player::dash(float angle){
	Input inputManager = gameState->core->inputManager;

	if(inputManager.LEFT_CLICK.isClicked() && !dashing){
		dashing = true;
		float dashSpeed = 15.0;
		distanceTraveled = 0.0;
		dx = dashSpeed * cos(angle);
		dy = dashSpeed * sin(angle);
		gameState->sounds.dashes[rand() % 2].play();
	}
	if(dashing){
		x += dx;
		y += dy;
		distanceTraveled += (abs(dx) + abs(dy)) / 2;
		if(distanceTraveled >= dashDistance){
			dashing = false;
			distanceTraveled = 0.0;
			dx = 0.0;
			dy = 0.0;
			delay = 12;
		}
		setSwordPos();
	}
}

void Player::setAnimationDirection(float newAngle){
	if(delay <= 0){
		if(!dashing){
			newAngle *= degrees;
			if(newAngle < 0) newAngle += 360;
			if(newAngle < 135 && newAngle > 45) move = &down;
			else if(newAngle  < 315 && newAngle > 225) move = &up;
			else if((newAngle < 360 && newAngle > 315) || (newAngle > 0 && newAngle < 45)) move = &right;
			else if(newAngle > 135 && newAngle < 225) move = &left;
		}
	}
}

void Player::setSwordPos(){
	if(move == &down){
		sword.setPosition(this->x, this->y + 20);
		sword.setRotation(180);
	}
	else if(move == &up){
		sword.setPosition(this->x, this->y - 20);
		sword.setRotation(0);
	}
	else if(move == &right){
		sword.setPosition(this->x + 20, this->y);
		sword.setRotation(90);
	}
	else if(move == &left){
		sword.setPosition(this->x - 20, this->y);
		sword.setRotation(270);
	}
}

void Player::enemyCollision(float angleTrajectory){
	if(dashing){
		float range = 90.0;
		for(int i = 0; i < gameState->entities.size(); i++){
			Entity* enemy = gameState->entities.at(i);
			if(collidesWith(enemy, true)){
				angleTrajectory *= degrees;
				float temp = atan2(enemy->y - this->y, enemy->x - this->x) * degrees;
				if(temp < (angleTrajectory) + (range) && temp > (angleTrajectory) - (range)){
					//gameState->spawnParticle(enemy->sprite.getPosition().x, enemy->sprite.getPosition().y, angleTrajectory);
					enemy->remove();
					gameState->sounds.slashes[rand() % 2].play();
				}
			}
		}
	}
}
