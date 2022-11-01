#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_

class Obstacle
{
public:
	Obstacle();
	Obstacle(const Obstacle&);
	~Obstacle();
	Obstacle& operator=(const Obstacle& o);

	void addNormal();
	void removeNormal();
	void addDangerous();
	void removeDangerous();
	bool getNormal();
	bool getDangerous();


protected:
	bool normal;
	bool dangerous;
};

#endif