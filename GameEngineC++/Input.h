#ifndef INPUT_H
#define INPUT_H
#include <vector>
#include "SFML/Graphics.hpp"

class Inputs{
	private:
		bool clicked, down;
	public:
		Inputs();
		int presses, absorbs;
		void toggle(bool pressed);
		void update();
		bool isClicked();
		bool isDown();
};

class Input{
public:
	std::vector<Inputs*> inputs;
	Inputs SPACE;
	Inputs LEFT_CLICK;
	Inputs E, S, D, F;

	Input();
	~Input();

	void update();
	void initInputs();
	void toggle(sf::Keyboard::Key, bool toggle);
};

#endif INPUT_H

