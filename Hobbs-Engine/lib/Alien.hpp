#ifndef ALIEN_HPP_INCLUDED
#define ALIEN_HPP_INCLUDED

/*
	All that is in game
*/
#include <SFML/Graphics.hpp>
#include <string>

typedef struct Hitbox Hitbox;
struct Hitbox
{
	int x;
	int y;
	int width;
	int height;
};

class Alien
{
private:
	int x;
	int y;
	int width;
	int height;
	std::string classID;

protected:
	void setClassID(std::string id);

public:
	Alien(int aX,int aY,int aWidth,int aHeight);
	~Alien();

	virtual void update() = 0;
	virtual void paint(sf::RenderWindow &window) = 0;

	Hitbox getRectangle();

	void setCoords(int cX,int cY);

	std::string getClassID() const;
};

bool operator==(Hitbox a,Hitbox b);

#endif