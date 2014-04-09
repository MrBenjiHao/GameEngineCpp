#include "Core.h"
#include "GameState.h"
#include <iostream>

Core::Core(){
	WIDTH = 900;
	HEIGHT = (WIDTH / 16) * 9;
	initStates();
	delay = 0;
	start();
}

Core::~Core(){
	delete gameState;
}

int fps = 0, ticks = 0;

void Core::start(){
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "GameEngine");
	WINDOW = &window;

	sf::Event event;
	sf::Clock clock;
	
	double FPS_TIME = (double) clock.getElapsedTime().asMilliseconds();
	double prevTime = (double) clock.getElapsedTime().asMilliseconds();
	double currTime;
	double delta = (1.0 / 60.0) * 1000.0;
	double maxTimeDiff = 0.5 * 1000.0;

	while(window.isOpen()){
		currTime = (double) clock.getElapsedTime().asMilliseconds();
		if(currTime - prevTime > maxTimeDiff) prevTime = currTime;
		if(currTime >= prevTime){
			update();
			prevTime += delta;
			if(currTime < prevTime) render(&window);
		}
		else sf::sleep(sf::milliseconds((prevTime - currTime)));

		if(clock.getElapsedTime().asMilliseconds() - FPS_TIME >= 1000){
			std::cout << "UPS: " << ticks << " FPS: " << fps << std::endl;
			FPS_TIME += 1000;
			fps = 0;
			ticks = 0;
		}

		 while (window.pollEvent(event)){
            switch(event.type){
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::KeyPressed: case sf::Event::MouseButtonPressed:
					inputManager.toggle(event.key.code, true);
					break;
				case sf::Event::KeyReleased: case sf::Event::MouseButtonReleased:
					inputManager.toggle(event.key.code, false);
					break;
			}
        }
	}
}

void Core::initStates(){
	gameState = new GameState(this);
}

void Core::update(){
	if(delay <= 0){
	inputManager.update();
	gameState->update();
	ticks++;
	}
	else delay--;
}

void Core::render(sf::RenderWindow* window){
	if(delay <= 0){
	//window->clear(sf::Color(87, 101, 127, 255));
	window->clear(sf::Color::Black);
	gameState->render(window);
	window->display();
	fps++;
	}
	else delay--;
}

int main(){
	system("COLOR 2");

	Core core;
	return 0;
}
