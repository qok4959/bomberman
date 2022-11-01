#ifndef _SURFACE_H_
#define _SURFACE_H_
#include "Obstacle.h"
#include <random>

class Surface
{
	friend class Engine;
	friend class Console;
public:
	Surface();
	Surface(int width, int height);
	Surface(const Surface&) = delete;
	~Surface();
	Surface &operator=(const Surface& o);
	
protected:
	int width, height;
	Obstacle** surface;
};

#endif