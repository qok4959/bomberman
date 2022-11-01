#ifndef _BOMB_H_
#define _BOMB_H_
#include "ctime"


class Bomb
{
	friend class Engine;
public:
	Bomb();
	Bomb(const Bomb&) = delete;
	~Bomb();
	Bomb& operator=(const Bomb&);

	void add();
	void remove();
	int getPosX();
	int getPosY();
	bool getHaveBomb();
	void startBombTimer();


protected:
	bool haveBomb;
	int posX, posY, rangeOfExplosion;
};

#endif