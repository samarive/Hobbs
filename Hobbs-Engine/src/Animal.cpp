#include "Animal.hpp"

Animal::Animal(int x,int y,int width,int height):Alien::Alien(x,y,width,height),animationFrame (1),textures(0),inMidAir(true),prevX(0),prevY(0),alive(true)
{
	setClassID("animal");

	dirX = 0;
	dirY = 0;

	movement = Movement::RIGHT_STOP;

}
Animal::~Animal()
{
	delete textures;
}
void Animal::update()
{	

	if(inMidAir){
		setDirection(getDirX(),getDirY()+1);
	}else{
		setDirection(getDirX(),0);
	}


	move();
}

void Animal::move()
{

	int x = getRectangle().x;
	int y = getRectangle().y;

	prevX = x;
	prevY = y;

	setCoords(x+dirX,y+dirY);
}

bool Animal::testCollisionWith(std::vector<Alien*> &arg)
{

	bool physicallyCollided (false);
	bool magneticlyCollided (false);
	
	for(int i = 0;i<arg.size();i++)
	{
		Hitbox self = getRectangle();
		Hitbox test = arg.at(i)->getRectangle();

		if(self==test)
			continue;

		if(self.x>test.x+test.width || self.x+self.width<test.x || self.y>test.y+test.height || self.y+self.height<test.y)
		{

			if(self.x+self.width>test.x && self.x < test.x+test.width && test.y-(self.y+self.height)==1)
			{
				magneticlyCollided = true;
			}

		}else{

			physicallyCollided = true;

			setCoords(prevX,prevY);
		}
	}

	if(physicallyCollided || magneticlyCollided)
	{
		inMidAir = false;
	}else
	{
		inMidAir = true;
	}

	return physicallyCollided;
	
}

void Animal::paint(sf::RenderWindow &window)
{
	sf::Sprite sprite;
	
	animationFrame+=0.1f;

	switch(movement)
	{
		case RIGHT_WALK:
			if((int) animationFrame>=textures->rightWalk->size())
			{
				animationFrame = 0;
			}
			sprite.setTexture(textures->rightWalk->at((int) animationFrame));
		break;
		case LEFT_WALK:
		if((int) animationFrame>=textures->leftWalk->size())
			{
				animationFrame = 0;
			}
			sprite.setTexture(textures->leftWalk->at((int) animationFrame));
		break;
		case IN_AIR_RIGHT:
			if((int) animationFrame>=textures->inAirRight->size())
			{
				animationFrame = 0;
			}
			sprite.setTexture(textures->inAirRight->at((int) animationFrame));
		break;
		case IN_AIR_LEFT:
			if((int) animationFrame>=textures->inAirLeft->size())
			{
				animationFrame = 0;
			}
			sprite.setTexture(textures->inAirLeft->at((int) animationFrame));
		break;
		case RIGHT_STOP:
			if((int) animationFrame>=textures->rightStop->size())
			{
				animationFrame = 0;
			}
			sprite.setTexture(textures->rightStop->at((int) animationFrame));
		break;
		case LEFT_STOP:
			if((int) animationFrame>=textures->leftStop->size())
			{
				animationFrame = 0;
			}
			sprite.setTexture(textures->leftStop->at((int) animationFrame));
		break;
		case RIGHT_ATTACK:
			if((int) animationFrame>=textures->rightAttack->size())
			{
				animationFrame = 0;
			}
			sprite.setTexture(textures->rightAttack->at((int) animationFrame));
		break;
		case LEFT_ATTACK:
			if((int) animationFrame>=textures->leftAttack->size())
			{
				animationFrame = 0;
			}
			sprite.setTexture(textures->leftAttack->at((int) animationFrame));
		break;
	}

	Hitbox hitbox = getRectangle();
	sprite.setPosition(sf::Vector2f(hitbox.x,hitbox.y));

	window.draw(sprite);
}
void Animal::setDirection(int dX,int dY)
{
	dirX = dX;
	dirY = dY;
}
void Animal::setVisual(AnimalVisual &visual)
{
	textures = &visual;
}
int Animal::getDirX() const
{
	return dirX;
}
int Animal::getDirY() const
{
	return dirY;
}
void Animal::die()
{
	alive = false;
}
bool Animal::isAlive() const
{
	return alive;
}