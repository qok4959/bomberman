#ifndef _CONSOLE_H_
#define _CONSOLE_H_
#include "Engine.h"
#include <iostream>

class Console : public Engine
{
public:
	Console();
	Console(const Console&) = delete;
	virtual ~Console();
	Console& operator=(const Console&);

	virtual void display();
	void hideCursor();
};

#endif