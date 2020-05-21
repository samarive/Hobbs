#ifndef ANIMAL_HPP_INCLUDED
#define ANIMAL_HPP_INCLUDED

/*
	Basically : walll that moves
*/

#include "Alien.hpp"
#include <vector>

typedef struct AnimalVisual AnimalVisual;
struct AnimalVisual
{
	std::vector<sf::Texture> *rightWalk;
	std::vector<sf::Texture> *leftWalk;
	std::vector<sf::Texture> *inAirRight;
	std::vector<sf::Texture> *inAirLeft;
	std::vector<sf::Texture> *rightAttack;
	std::vector<sf::Texture> *leftAttack;
	std::vector<sf::Texture> *rightStop;
	std::vector<sf::Texture> *leftStop;
};

enum Movement
{
	RIGHT_WALK,LEFT_WALK,IN_AIR_RIGHT,IN_AIR_LEFT,RIGHT_ATTACK,LEFT_ATTACK,LEFT_STOP,RIGHT_STOP
};


class Animal:public Alien
{
private:

	float animationFrame;
	int dirX;
	int dirY;

	void move();

	int prevX;
	int prevY;

	bool alive;


protected:

	bool inMidAir;

	Movement movement;
	AnimalVisual* textures;

public:

	Animal(int x,int y,int width,int height);
	virtual ~Animal();

	virtual void setDirection(int dX,int dY);
	virtual bool testCollisionWith(std::vector<Alien*> &arg);
	virtual void update();
	virtual void paint(sf::RenderWindow &window);
	virtual void loadTextures() = 0;
	void setVisual(AnimalVisual &visual);

	void die();
	bool isAlive() const;

	int getDirX() const;
	int getDirY() const;
};

#endif