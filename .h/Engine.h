#ifndef _ENGINE_H_
#define _ENGINE_H_
#include "Character.h"
#include "Surface.h"
#include <windows.h>
#include <random>
#include <thread>
#include "Bomb.h"

class Engine
{
public:
	Engine();
	Engine(const Engine&) = delete;
	virtual ~Engine();
	Engine& operator=(const Engine& o);


	virtual void display() = 0;

	void play();
	void threads();

	void playerMove();
	void moveCharacter();
	void playerTimer();
	int getInputKey();

	void botMove();
	void randomMoves();
	void botTimer();


	void explode(int pos_X, int pos_Y);
	void checkCollisionWithRay();
	int getRandomNumber(int a, int b);



protected:
	Character characters[2];
	Surface plane;

	//sterowanie
	// SPACEBAR - bomba	    
	// LEFT_ARROW - lewo | RIGHT_ARROW - prawo itp.
	const int
		LEFT_ARROW = 0x25, UP_ARROW = 0x26,
		DOWN_ARROW = 0x28, RIGHT_ARROW = 0x27,
		SPACEBAR = 0x20;
	int key[2];
};

#endif