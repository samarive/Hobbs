#include "Fireball.hpp"
#include <iostream>

Fireball::Fireball(int x,int y,int dirX,int dirY):Animal::Animal(x,y,32,16)
{
	setClassID("fireball");

	setDirection(dirX,dirY);

	if(dirX>0)
	{
		movement = Movement::IN_AIR_RIGHT;
	}else
	{
		movement = Movement::IN_AIR_LEFT;
	}


	loadTextures();
}
Fireball::~Fireball()
{

}
void Fireball::update()
{
	setCoords(getRectangle().x+getDirX(),getRectangle().y);
}

void Fireball::loadTextures()
{

	sf::Texture temp;
	temp.loadFromFile("img/fireballright.png");
	sf::Texture temp1;
	temp1.loadFromFile("img/fireballleft.png");

	textures = new AnimalVisual;
	textures->rightWalk = new std::vector<sf::Texture>;
		textures->rightWalk->push_back(temp);
	textures->leftWalk = new std::vector<sf::Texture>;
		textures->leftWalk->push_back(temp1);
	textures->inAirRight = new std::vector<sf::Texture>;
		textures->inAirRight->push_back(temp);
	textures->inAirLeft = new std::vector<sf::Texture>;
		textures->inAirLeft->push_back(temp1);
	textures->rightAttack = new std::vector<sf::Texture>;
		textures->rightAttack->push_back(temp);
	textures->leftAttack = new std::vector<sf::Texture>;
		textures->leftAttack->push_back(temp1);
	textures->rightStop = new std::vector<sf::Texture>;
		textures->rightStop->push_back(temp);
	textures->leftStop = new std::vector<sf::Texture>;
		textures->leftStop->push_back(temp1);

}

bool Fireball::testCollisionWith(std::vector<Alien*> &arg)
{

	for(int i = 0;i<arg.size();i++)
	{
		Hitbox self = getRectangle();
		Hitbox test = arg.at(i)->getRectangle();

		if(self==test)
			continue;

		if(self.x>test.x+test.width || self.x+self.width<test.x || self.y>test.y+test.height || self.y+self.height<test.y)
		{

		}else{
			
			if(arg.at(i)->getClassID().find("animal")!=std::string::npos){

				Animal* ani = (Animal*) arg.at(i);

				ani->die();

				return true;
			}
		}
	}

	return Animal::testCollisionWith(arg);
}