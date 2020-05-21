#ifndef FIREBALL_HPP_INCLUDED
#define FIREBALL_HPP_INCLUDED

/*
	Fired by Hobbs !
*/

#include "Animal.hpp"

class Fireball:public Animal
{
private:


public:
	Fireball(int x,int y,int dirX,int dirY);
	~Fireball();

	virtual bool testCollisionWith(std::vector<Alien*> &arg);
	virtual void update();
	virtual void loadTextures();
};

#endif