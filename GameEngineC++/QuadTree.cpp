#include "QuadTree.h"
#include "Entity.h"

QuadTree::QuadTree(sf::RectangleShape bounds, int level)
	: MAX_LEVELS(4), MAX_OBJECTS(2), LEVEL(level), bounds(bounds){
}

void QuadTree::clear(){
	// Clearing the entity list
	entities.clear();
	// Going through each node and clearing their entity list
	// Then clearing this tree's list of nodes
	for(int i = 0; i < nodes.size(); i++){
		nodes[i].clear();
	}
	nodes.clear();
}

void QuadTree::split(){
	float subWidth = bounds.getGlobalBounds().width / 2;
	float subHeight = bounds.getGlobalBounds().height / 2;
	float x = bounds.getPosition().x;
	float y = bounds.getPosition().y;

	sf::RectangleShape rectBound(sf::Vector2f(subWidth, subHeight));
	rectBound.setFillColor(sf::Color(87, 101, 127, 255));
	rectBound.setOutlineColor(sf::Color::White);
	rectBound.setOutlineThickness(1.0);
	rectBound.setPosition(x, y);
	nodes.push_back(QuadTree(rectBound, LEVEL + 1));
	rectBound.setPosition(x + subWidth, y);
	nodes.push_back(QuadTree(rectBound, LEVEL + 1));
	rectBound.setPosition(x, y + subHeight);
	nodes.push_back(QuadTree(rectBound, LEVEL + 1));
	rectBound.setPosition(x + subWidth, y + subHeight);
	nodes.push_back(QuadTree(rectBound, LEVEL + 1));
}

// Figures out which QuadTree in nodes that the entity belongs to
int QuadTree::getIndex(Entity* entity){

	sf::Vector2f position(entity->sprite.getPosition());
	sf::Vector2f size(entity->sprite.getGlobalBounds().width, entity->sprite.getGlobalBounds().height);

	// Checking which node the entity fits inside
	for(int i = 0; i < nodes.size(); i++){
		if(position.x >= nodes[i].bounds.getPosition().x &&
		position.x + size.x <= nodes[i].bounds.getPosition().x + nodes[i].bounds.getGlobalBounds().width){
			if(position.y >= nodes[i].bounds.getPosition().y &&
			position.y + size.y <= nodes[i].bounds.getPosition().y + nodes[i].bounds.getGlobalBounds().height){
				return i;
			}
		}
	}
	// Returning -1 if it doesn't fit completely in a node
	return -1;
}

//void QuadTree::insert(Entity* entity){
//	int index = getIndex(entity);
//
//	// QuadTree has no children
//	if(nodes.size() == 0){
//		// If the list isn't full
//		if(entities.size() <= MAX_OBJECTS) entities.push_back(entity);
//		// If the list is full
//		else{
//			// Split only if the max tree height hasn't been reached
//			// Then insert entity into node with corresponding index
//			if(LEVEL <= MAX_LEVELS && index != -1){
//				split();
//				nodes[index].insert(entity);
//			}
//			// If the height has been maxed, add entity to current list, regardless of max capacity
//			// Also if index equal to -1, just add entity to current list
//			else entities.push_back(entity);
//		}
//	}
//	// QuadTree has children
//	// Insert entity into node with corresponding index
//	else nodes[index].insert(entity); // Recursively does the whole process until it gets added to a node
//}

void QuadTree::insert(Entity* entity){
	int index;
	if(nodes.size() != 0){
		index = getIndex(entity);

		if(index != -1){
			nodes[index].insert(entity);
			return;
		}
	}

	entities.push_back(entity);

	if(entities.size() >= MAX_OBJECTS && LEVEL <= MAX_LEVELS){
		if(nodes.size() == 0) split();
		int i = 0;
		while(i < entities.size()){
			index = getIndex(entities[i]);
			if(index != -1){
				nodes[index].insert(entities[i]);
				entities.erase(entities.begin() + i);
				i--;
			}
			else i++;
		}
	}
}

//std::vector<Entity*> QuadTree::retrieve(Entity* entity){
//	// Check which node the entity belongs to
//	int index = getIndex(entity);
//	// vector pointer to current node list
//	std::vector<QuadTree>* nodesPointer = &nodes;
//
//	if(index == -1) return entities;
//	else{
//		// While the node still has children
//		// Set the list pointer equal to the current node list
//		while(nodesPointer->size() != 0 && index != -1){
//			// getting the nodes at the current index
//			nodesPointer = &nodesPointer->at(index).nodes;
//			index = nodesPointer->at(index).getIndex(entity);
//		}
//	}
//
//	// Then return the node's entity list
//	return nodesPointer->at(index).entities;
//}

std::vector<Entity*> QuadTree::retrieve(Entity* entity){
	std::vector<Entity*> returnObjects = entities;
	int index = getIndex(entity);
	if(index != -1 && nodes.size() != 0){
		returnObjects = nodes[index].retrieve(entity);
	}

	return returnObjects;
}

void QuadTree::render(sf::RenderWindow* window){
	window->draw(bounds);
	for(int i = 0; i < nodes.size(); i++){
		nodes[i].render(window);
	}
}