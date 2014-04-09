#include "Entity.h"
#include "GameState.h"
#include "Core.h"
#include <iostream>

Entity::Entity(float x, float y, int width, int height, GameState* gameState)
	: texture(&gameState->mainSheet), x(x), y(y),width(width), height(height), gameState(gameState), textureLoaded(false), scale(0.0), isRemoved(false), ticks(0){
}

Entity::~Entity(){
}

void Entity::update(){
	ticks++;
}

void Entity::render(sf::RenderWindow* window){
	if(onScreen()) window->draw(sprite);
}

bool Entity::collidesWith(Entity* e2, bool globalPos){
	if(globalPos) return sprite.getGlobalBounds().intersects(e2->sprite.getGlobalBounds());

	if(x > e2->x + (e2->width * scale)) return false;
	if(x + (width * scale) < e2->x) return false;
	if(y > e2->y + (e2->height * scale)) return false;
	if(y + (height * scale) < e2->y) return false;
	return true;
}

void Entity::loadSprite(int x, int y, int width, int height){
	if(!textureLoaded){
		sprite.setTexture(*texture);
		textureLoaded = true;
		sprite.setPosition(this->x, this->y);
		sprite.setScale(scale, scale);
	}
	sprite.setTextureRect(sf::IntRect(x, y, width , height));
}

void Entity::setEntityType(EntityType type){
	this->entityType = type;
}

Entity::EntityType Entity::getEntityType(){
	return entityType;
}

void Entity::remove(){
	isRemoved = true;
}

bool Entity::onScreen(){
	if(x + (width * scale) < 0) return false;
	if(x > gameState->core->WIDTH) return false;
	if(y + (height * scale) < 0) return false;
	if(y > gameState->core->HEIGHT) return false;
	return true;
}