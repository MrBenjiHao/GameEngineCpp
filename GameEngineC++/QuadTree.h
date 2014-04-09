#ifndef QUADTREE_H
#define QUADTREE_H

#include <vector>
#include "SFML\Graphics.hpp"

class Entity;

class QuadTree{
private:
	int MAX_OBJECTS;
	int MAX_LEVELS;
	int LEVEL;

	sf::RectangleShape bounds;
	std::vector<Entity*> entities;
	std::vector<QuadTree> nodes;
public:
	QuadTree(sf::RectangleShape bounds, int level = 0);

	void clear();
	void split();
	int getIndex(Entity* entity);
	void insert(Entity* entity);
	std::vector<Entity*> retrieve(Entity* entity);
	void render(sf::RenderWindow* window);
};

#endif