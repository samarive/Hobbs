#include "Alien.hpp"

Alien::Alien(int aX,int aY,int aWidth,int aHeight):x(aX),y(aY),width(aWidth),height(aHeight),classID("alien")
{

}
Alien::~Alien()
{

}
Hitbox Alien::getRectangle()
{
	Hitbox rect = {x,y,width,height};

	return rect;
}
void Alien::setCoords(int cX,int cY)
{
	x = cX;
	y = cY;
}

bool operator==(Hitbox a,Hitbox b)
{
	return (a.x==b.x && a.y==b.y && a.width==b.width && a.height == b.height);
}

std::string Alien::getClassID() const
{
	return classID;
}
void Alien::setClassID(std::string id)
{
	classID+=id;
}