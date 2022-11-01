#include "Surface.h"



Surface::Surface() {

	width = 30; height = 30;
	surface = new Obstacle * [height];

	for (int i = 0; i < height; i++) {
		surface[i] = new Obstacle[width];
	}

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			surface[i][j].removeNormal();
		}
	}
}



Surface::Surface(int width, int height) {

	this->width = width;
	this->height = height;

	surface = new Obstacle * [height];

	for (int i = 0; i < height; i++) {
		surface[i] = new Obstacle[width];
	}

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			surface[i][j].removeNormal();
		}
	}

	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> rand(1, 10);

	int random = rand(rng);
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if ((i == height / 3 && j == width / 3) || (i == height / 6 && j == width / 6))
				continue;
			random = rand(rng);
			if (random == 1)
				surface[i][j].addNormal();
		}
	}
}



Surface::~Surface() {

	if (surface != 0) {
		for (int i = 0; i < height; i++) {
			delete[] surface[i];
		}
		delete[]surface;
	}
}



Surface& Surface::operator=(const Surface& obj) {

	this->width = obj.width;
	this->height = obj.height;

	surface = new Obstacle * [height];

	for (int i = 0; i < height; i++) {
		surface[i] = new Obstacle[width];
	}

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			surface[i][j].removeNormal();
		}
	}


	if (this != &obj) {
		width = obj.width;
		height = obj.height;

		for (int i = 0; i < obj.height; i++) {
			for (int j = 0; j < obj.width; j++) {
				surface[i][j] = obj.surface[i][j];
			}
		}
	}


	return *this;
}