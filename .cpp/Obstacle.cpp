#include "Obstacle.h"

Obstacle::Obstacle() {
	normal = false;
	dangerous = false;
}



Obstacle::~Obstacle() {}



Obstacle& Obstacle::operator=(const Obstacle& obj) {

	if (this != &obj) {
		this->normal = obj.normal;
		this->dangerous = obj.dangerous;
	}

	return *this;
}



Obstacle::Obstacle(const Obstacle& obj) {
	this->normal = obj.normal;
	this->dangerous = obj.dangerous;
}


void Obstacle::addNormal() {
	normal = true;
}



void Obstacle::removeNormal() {
	normal = false;
}



bool Obstacle::getNormal() {
	return normal;
}


bool Obstacle::getDangerous() {
	return dangerous;
}


void Obstacle::addDangerous() {
	dangerous = true;
}

void Obstacle::removeDangerous() {
	dangerous = false;
}

