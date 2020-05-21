#ifndef WALL_HPP_INCLUDED
#define WALL_HPP_INCLUDED

/*
	Walls
*/


enum WallType
{
	NONE=-1,MERCURY,VENUS,EARTH,MARS,JUPITER,SATURN,URANUS,NEPTUNE,GRASS,DIRT
};

#include "Alien.hpp"


class Wall:public Alien
{
private:

	sf::Texture texture;
	WallType type;

public:

	Wall(int x,int y,int width,int height,WallType aType);
	~Wall();

	WallType getType();

	virtual void paint(sf::RenderWindow &window);
	virtual void update();

};


#endif