#ifndef _CHARACTER_H_
#define _CHARACTER_H_
#include "Bomb.h"

class Character
{
	friend class Engine;
	friend class Console;
public:
	Character();
	Character(bool alive, int posX, int posY);
	Character(const Character&) = delete;
	~Character();
	Character& operator=(const Character& o);

	int getPosX();
	int getPosY();

protected:
	int posX, posY;
	bool alive;
	Bomb bomb;
};

#endif
