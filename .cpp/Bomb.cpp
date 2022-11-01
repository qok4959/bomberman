#include "Bomb.h"

Bomb::Bomb() {
	haveBomb = true;
	posX = 3;
	posY = 3;
	rangeOfExplosion = 3;
}

Bomb::~Bomb() {}
Bomb& Bomb::operator=(const Bomb& o) {

	if (this != &o) {
		this->haveBomb = o.haveBomb;
		this->posX = o.posX;
		this->posY = o.posY;
		this->rangeOfExplosion = o.rangeOfExplosion;
	}

	return *this;
}

void Bomb::add() { haveBomb = true; }
void Bomb::remove() { haveBomb = false; }

int Bomb::getPosX() {
	return posX;
}

int Bomb::getPosY() {
	return posY;
}

bool Bomb::getHaveBomb() {
	return haveBomb;
}

void Bomb::startBombTimer() {
	double timerStart = std::clock();
	while (true) {
		if (((std::clock() - timerStart) / (double)CLOCKS_PER_SEC) >= 3)
			break;
	}
	haveBomb = true;
}