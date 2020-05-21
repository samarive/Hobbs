#ifndef HOBBS_HPP_INCLUDED
#define HOBBS_HPP_INCLUDED

/*
	Hobbs !
*/

#include "Fireball.hpp"

class Hobbs:public Animal
{
private:

	const int dashLoad;
	const int dashLenght;
	const int speed;

	int bindings[6];

	Fireball *fireball;

	int dashFuel;
	bool dashing;

public:
	Hobbs(int x,int y);
	virtual ~Hobbs();

	virtual void loadTextures();
	virtual void setDirection(int dX,int dY);
	virtual void update();
	virtual void paint(sf::RenderWindow &arg);
	virtual bool testCollisionWith(std::vector<Alien*> &arg);
	
	int getUp();
	int getLeft();
	int getDown();
	int getRight();
	int getFire();
	int getDash();
	
	void keyPressed(int keyCode);
	void keyReleased(int keyCode);
	void setControls(int up,int left,int down,int right,int fire,int dash);
	void shoot();
	void reload();
	void dash();

};

#endif