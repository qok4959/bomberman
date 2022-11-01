#include "Engine.h"


Engine::Engine() {

	int width = 31, height = 15;

	Surface p1(width, height);
	plane = p1;
	characters[0] = Character(true, width / 3, height / 3);
	characters[1] = Character(true, width / 6, height / 6);
	key[0] = 0;
	key[1] = 0;
}



Engine::~Engine() {}



Engine& Engine::operator=(const Engine& obj) {

	if (this != &obj) {
		characters[0] = obj.characters[0];
		characters[1] = obj.characters[1];
		plane = obj.plane;
	}

	return *this;
}



int Engine::getInputKey() {

	key[1] = 0;
	while (true) {
		if (GetAsyncKeyState(LEFT_ARROW))
			key[1] = LEFT_ARROW;
		else if (GetAsyncKeyState(RIGHT_ARROW))
			key[1] = RIGHT_ARROW;
		else if (GetAsyncKeyState(DOWN_ARROW))
			key[1] = DOWN_ARROW;
		else if (GetAsyncKeyState(UP_ARROW))
			key[1] = UP_ARROW;
		else if (GetAsyncKeyState(SPACEBAR))
			key[1] = SPACEBAR;

		if (key[1] != 0)
			break;
	}

	return *key;
};




void Engine::moveCharacter() {


	if (key[1] == UP_ARROW) {
		if (characters[1].posY > 1)
			if (characters[0].posY != characters[1].posY - 1 || characters[0].posX != characters[1].posX) // uniemozliwia nakladanie sie na siebie postaci
				if (!plane.surface[characters[1].posY - 1][characters[1].posX].getNormal())				  // uniemozliwia wejscie na przeszkode
					--characters[1].posY;
	}
	else if (key[1] == LEFT_ARROW) {
		if (characters[1].posX > 1)
			if (characters[0].posX != characters[1].posX - 1 || characters[0].posY != characters[1].posY)
				if (!plane.surface[characters[1].posY][characters[1].posX - 1].getNormal())
					--characters[1].posX;
	}

	else if (key[1] == DOWN_ARROW) {
		if (characters[1].posY < plane.height - 2)
			if (characters[0].posY != characters[1].posY + 1 || characters[0].posX != characters[1].posX)
				if (!plane.surface[characters[1].posY + 1][characters[1].posX].getNormal())
					++characters[1].posY;
	}

	else if (key[1] == RIGHT_ARROW) {
		if (characters[1].posX < plane.width - 2)
			if (characters[0].posX != characters[1].posX + 1 || characters[0].posY != characters[1].posY)
				if (!plane.surface[characters[1].posY][characters[1].posX + 1].getNormal())
					++characters[1].posX;
	}

	// bomba
	else if (key[1] == SPACEBAR) {
		if (characters[1].posY > 1)
			if (characters[1].bomb.haveBomb)
				if (!plane.surface[characters[1].posY - 1][characters[1].posX].getNormal() &&
					(characters[0].posX != characters[1].posX && characters[0].posY != characters[1].posY - 1))
					if (!characters[0].bomb.haveBomb && (characters[1].bomb.posX != characters[0].posX ||
						characters[1].posY - 1 != characters[0].posY)) {

						characters[1].bomb.posX = characters[1].posX;
						characters[1].bomb.posY = characters[1].posY - 1;
						characters[1].bomb.remove();
					}
					else {
						characters[1].bomb.posX = characters[1].posX;
						characters[1].bomb.posY = characters[1].posY - 1;
						characters[1].bomb.remove();

					}
	}
};



void Engine::randomMoves() {

	int random = getRandomNumber(1, 5);

	// case 1-4 poruszanie postaci
	// case 5 podkladanie bomby
	switch (random) {

	case 1:
		if (characters[0].posY > 1)
			if (characters[0].posY - 1 != characters[1].posY || characters[0].posX != characters[1].posX) // uniemozliwia nakladanie sie na siebie postaci
				if (!plane.surface[characters[0].posY - 1][characters[0].posX].getNormal() &&			  // uniemozliwia wejscie na przeszkode
					!plane.surface[characters[0].posY - 1][characters[0].posX].getDangerous() &&		  // unikanie promieni razenia bomb
					(characters[0].bomb.posX != characters[0].posX && characters[0].bomb.posY != characters[0].posY - 1))
					--characters[0].posY;
		break;

	case 2:
		if (characters[0].posX > 1)
			if (characters[0].posX - 1 != characters[1].posX || characters[0].posY != characters[1].posY)
				if (!plane.surface[characters[0].posY][characters[0].posX - 1].getNormal() &&
					!plane.surface[characters[0].posY][characters[0].posX - 1].getDangerous() &&
					(characters[0].bomb.posX != characters[0].posX - 1 && characters[0].bomb.posY != characters[0].posY))
					--characters[0].posX;
		break;

	case 3:
		if (characters[0].posY < plane.height - 2)
			if (characters[0].posY + 1 != characters[1].posY || characters[0].posX != characters[1].posX)
				if (!plane.surface[characters[0].posY + 1][characters[0].posX].getNormal() &&
					!plane.surface[characters[0].posY + 1][characters[0].posX].getDangerous() &&
					(characters[0].bomb.posX != characters[0].posX && characters[0].bomb.posY != characters[0].posY + 1))
					++characters[0].posY;
		break;
	case 4:
		if (characters[0].posX < plane.width - 2)
			if (characters[0].posX + 1 != characters[1].posX || characters[0].posY != characters[1].posY)
				if (!plane.surface[characters[0].posY][characters[0].posX + 1].getNormal() &&
					!plane.surface[characters[0].posY][characters[0].posX + 1].getDangerous() &&
					(characters[0].bomb.posX != characters[0].posX + 1 && characters[0].bomb.posY != characters[0].posY))
					++characters[0].posX;
		break;

	case 5:
		if (characters[0].posY > 1)
			if (characters[0].bomb.haveBomb)
				if (!plane.surface[characters[0].posY - 1][characters[0].posX].getNormal() &&
					(characters[1].posX != characters[0].posX && characters[1].posY != characters[0].posY - 1))
					if (!characters[1].bomb.haveBomb && (characters[0].bomb.posX != characters[1].posX ||
						characters[0].posY - 1 != characters[1].posY)) {

						characters[0].bomb.posX = characters[0].posX;
						characters[0].bomb.posY = characters[0].posY - 1;
						characters[0].bomb.remove();
					}
					else {
						characters[0].bomb.posX = characters[0].posX;
						characters[0].bomb.posY = characters[0].posY - 1;
						characters[0].bomb.remove();

					}
	}
}



void Engine::play() {
	threads();
};



void Engine::threads() {

	std::thread bot(&Engine::botMove, this);
	std::thread botT(&Engine::botTimer, this);
	std::thread character(&Engine::playerMove, this);
	std::thread characterT(&Engine::playerTimer, this);

	bot.join();
	botT.join();
	character.join();
	characterT.join();
}



void Engine::botMove() {
	while (characters[0].alive && characters[1].alive) {
		randomMoves();
		display();
		Sleep(200);
	}
}



void Engine::playerMove() {
	int move = 0;
	while (characters[0].alive && characters[1].alive) {
		move = 0;
		move = getInputKey();
		if (key[1] != 0) {
			moveCharacter();
			display();
			Sleep(100);
		}
	}
}



int Engine::getRandomNumber(int a, int b) {
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> rand(a, b);

	return rand(rng);
}



void Engine::botTimer() {
	while (characters[0].alive && characters[1].alive) {
		if (!characters[0].bomb.haveBomb) {
			characters[0].bomb.startBombTimer();
			explode(characters[0].bomb.getPosX(), characters[0].bomb.getPosY());
		}
	}
}



void Engine::playerTimer() {
	while (characters[0].alive && characters[1].alive) {
		if (!characters[1].bomb.haveBomb) {
			characters[1].bomb.startBombTimer();
			explode(characters[1].bomb.getPosX(), characters[1].bomb.getPosY());
		}
	}
}


void Engine::explode(int pos_X, int pos_Y) {

	//za przeszkodza nie moze byc promienia razenia bomby
	bool westObstacle = false, eastObstacle = false, northObstacle = false, southObstacle = false;

	// dodawanie promienii razenia bomby
	for (int i = 0; i <= 3; i++) {

		if (pos_X + i < plane.width - 1 && !eastObstacle)
			if (!plane.surface[pos_Y][pos_X + i].getNormal())
				plane.surface[pos_Y][pos_X + i].addDangerous();
			else
				eastObstacle = true;

		if (pos_X - i > 0 && !westObstacle)
			if (!plane.surface[pos_Y][pos_X - i].getNormal())
				plane.surface[pos_Y][pos_X - i].addDangerous();
			else
				westObstacle = true;


		if (pos_Y + i < plane.height - 1 && !southObstacle)
			if (!plane.surface[pos_Y + i][pos_X].getNormal())
				plane.surface[pos_Y + i][pos_X].addDangerous();
			else
				southObstacle = true;

		if (pos_Y - i > 0 && !northObstacle)
			if (!plane.surface[pos_Y - i][pos_X].getNormal())
				plane.surface[pos_Y - i][pos_X].addDangerous();
			else
				northObstacle = true;

	}
	display();
	double timerStart = std::clock();

	while (((double(std::clock()) - timerStart) / (double)CLOCKS_PER_SEC) <= 0.5) {
		checkCollisionWithRay();
	}


	// usuwanie promienii razenia bomby
	for (int i = 0; i <= 3; i++) {

		if (pos_X + i < plane.width)
			plane.surface[pos_Y][pos_X + i].removeDangerous();
		if (pos_X - i > 0)
			plane.surface[pos_Y][pos_X - i].removeDangerous();
		if (pos_Y + i < plane.height)
			plane.surface[pos_Y + i][pos_X].removeDangerous();
		if (pos_Y - i > 0)
			plane.surface[pos_Y - i][pos_X].removeDangerous();
	}
	display();
}


void Engine::checkCollisionWithRay() {

	// czy jakas postac znajduje sie na promieni bomby
	for (int i = 0; i < plane.height; i++) {
		for (int j = 0; j < plane.width; j++) {
			if (plane.surface[i][j].getDangerous()) {
				if (characters[0].posX == j && characters[0].posY == i) {
					characters[0].alive = false;
				}

				if (characters[1].posX == j && characters[1].posY == i) {
					characters[1].alive = false;
				}
			}
		}
	}
}