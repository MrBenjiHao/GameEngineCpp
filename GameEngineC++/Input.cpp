#include "Input.h"
#include <iostream>

Input::Input(){
	initInputs();
}

Input::~Input(){
}

void Input::initInputs(){
	inputs.push_back(&SPACE);
	inputs.push_back(&LEFT_CLICK);
	inputs.push_back(&E);
	inputs.push_back(&S);
	inputs.push_back(&D);
	inputs.push_back(&F);
}

void Input::toggle(sf::Keyboard::Key key, bool toggle){
	switch(key){
	case(sf::Keyboard::Space):
		SPACE.toggle(toggle);
		break;
	case(sf::Mouse::Left):
		LEFT_CLICK.toggle(toggle);
		break;
	case(sf::Keyboard::E):
		E.toggle(toggle);
		break;
	case(sf::Keyboard::S):
		S.toggle(toggle);
		break;
	case(sf::Keyboard::D):
		D.toggle(toggle);
		break;
	case(sf::Keyboard::F):
		F.toggle(toggle);
		break;

	}
}

void Input::update(){
	for(int i = 0; i < inputs.size(); i++){
		inputs[i]->update();
	}
}

// Inputs Class implementation

Inputs::Inputs() : clicked(false), down(false), absorbs(0), presses(0){
}

void Inputs::toggle(bool pressed){
	if(pressed != down) down = pressed;
	if(pressed) presses++;
}

void Inputs::update(){
	if(absorbs < presses){
		absorbs++;
		clicked = true;
	}
	else clicked = false;
}

bool Inputs::isClicked(){
	return clicked;
}

bool Inputs::isDown(){
	return down;
}