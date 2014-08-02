#include "GameState.h"
#include <iostream>
#include "Player.h"
#include "Enemy.h"
#include "Core.h"
#include "Map.h"

GameState::GameState(Core* core) 
	: core(core), ticks(0), gameOver(false){

	loadTextures();
	init();

	srand(time(NULL));
}

GameState::~GameState(){
	delete player;
}	

void GameState::init(){
	initSlash();

	player = new Player(core->WIDTH / 2, core->HEIGHT / 2, 32, 32, this);

	map = Map(this);

	map.loadMap(10, 6);
}

void GameState::update(){
	ticks++;
	if(!gameOver){
		player->update();
		for(int i = 0; i < entities.size(); i++){
			entities[i]->update();
		}
		spawnEnemies(2);
		removeEntities();
	}
}

void GameState::render(sf::RenderWindow* window){
	map.render(window);
	player->render(window);
	for(int i = 0; i < entities.size(); i++){
		entities[i]->render(window);
	}
	for(int i = 0; i < slashes.size(); i++){
		window->draw(slashes[i]);
	}
}

void GameState::removeEntities(){
	for(int i = 0; i < entities.size(); i++){
		if(entities[i]->isRemoved){
			delete entities[i];
			entities[i] = NULL;
			entities.erase(entities.begin() + i);
			i--;
		}
	}
}

void GameState::loadTextures(){
	mainSheet.loadFromFile("Resources/SpriteSheet.png");
}

void GameState::spawnEnemies(int rate){
	if(rate > 180) rate = 180;
	if(ticks % (180 / rate) == 0){
		entities.push_back(new Enemy((rand() % core->WIDTH), (rand() % core->HEIGHT), 32, 32, this));
	}
}

void GameState::spawnParticle(int x, int y, float angle){
	slash.setPosition(x, y);
	slash.setRotation(angle);
	slashes.push_back(slash);
}

void GameState::initSlash(){
	slash.setTexture(&mainSheet);
	slash.setTextureRect(sf::IntRect(0, 160, 127, 16));
	slash.setOrigin(127 / 2, 16 / 2);
	slash.setSize(sf::Vector2f(127, 16));
}

Player GameState::getPlayer(){
	return *player;
}