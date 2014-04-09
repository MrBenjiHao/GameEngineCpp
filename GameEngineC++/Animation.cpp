#include "Animation.h"
#include "Entity.h"

Animation::Animation(Entity* entity) : entity(entity), START(false), STOP(false), PLAYING(false), animationSpeed(1), ticks(0), frame(0){}

void Animation::addFrame(int x, int y, int width, int height){
	sf::IntRect frame(x, y, width, height);
	frames.push_back(frame);
}

void Animation::update(){
	ticks++;
	if(START){
		if(ticks % (60 / animationSpeed) == 0){
			if(frame <= (frames.size() - 1)){
				entity->sprite.setTextureRect(frames[frame]);
				frame++;
			}
			else stop();
		}
	}
	if(STOP){
		entity->sprite.setTextureRect(frames[frame]);
		frame++;
		STOP = false;
	}
}

void Animation::setAnimateSpeed(int speed){
	// Frames per second
	if(speed > 60) speed = 60;
	this->animationSpeed = speed;
}

void Animation::start(){
	this->START = true;
}

void Animation::stop(){
	frame = 0;
	this->START = false;
	this->STOP = true;
}

bool Animation::isPlaying(){
	return PLAYING;
}
