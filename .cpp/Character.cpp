#include "Character.h"


Character::Character() {
	posX = 3;
	posY = 3;
	alive = true;
}



Character::Character(bool alive, int posX, int posY) {
	this->alive = alive;
	this->posX = posX;
	this->posY = posY;
}



Character::~Character() {}



Character& Character::operator=(const Character& obj) {

	if (this != &obj) {
		this->alive = obj.alive;
		this->posX = obj.posX;
		this->posY = obj.posY;
	}

	return *this;
}




int Character::getPosX() {
	return posX;
}



int Character::getPosY() {
	return posY;
}