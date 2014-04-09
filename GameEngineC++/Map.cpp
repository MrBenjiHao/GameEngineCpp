#include "Map.h"
#include "GameState.h"
#include <iostream>

Map::Map(GameState* gameState) : gameState(gameState){
}

void Map::loadMap(int width, int height){
	sf::RectangleShape tile;
	tile.setSize(sf::Vector2f(32, 32));
	tile.setScale(3, 3);
	tile.setTexture(&gameState->mainSheet);
	tile.setTextureRect(sf::IntRect(0, 128, 32, 32));
	for(int x = 0; x < width; x++){
		for(int y = 0; y < height; y++){
			//if(x % 4 == 0 || y % 4 == 0) tile.setTextureRect(sf::IntRect(0, 128, 32, 32));
			//else tile.setTextureRect(sf::IntRect(32, 128, 32, 32));
			tile.setPosition(x * (32 * 3), y * (32 * 3));
			tiles.push_back(tile);
		}
	}
}

void Map::update(){
}

void Map::render(sf::RenderWindow* window){
	for(int i = 0; i < tiles.size(); i++){
		window->draw(tiles[i]);
	}
}

void Map::doSomething(){
	std::cout << "Map class says hello" << std::endl;
}