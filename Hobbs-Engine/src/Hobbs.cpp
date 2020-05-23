#include "Hobbs.hpp"

Hobbs::Hobbs(int x,int y):Animal::Animal(x,y,32,32),fireball(0),dashFuel(0),dashing(false),speed(5),dashLoad(100),dashLenght (10)
{
	setClassID("hobbs");

	loadTextures();

	for(int i = 0;i < 6;i++)
	{
		bindings[i] = 0;
	}
}

Hobbs::~Hobbs()
{
	delete fireball;
}

void Hobbs::loadTextures()
{
	sf::Texture temp;

	textures = new AnimalVisual;
	textures->rightWalk = new std::vector<sf::Texture>;
		temp.loadFromFile("img/hobbsrightwalk1.png");
		textures->rightWalk->push_back(temp);
		temp.loadFromFile("img/hobbsrightwalk2.png");
		textures->rightWalk->push_back(temp);
	textures->leftWalk = new std::vector<sf::Texture>;
		temp.loadFromFile("img/hobbsleftwalk1.png");
		textures->leftWalk->push_back(temp);
		temp.loadFromFile("img/hobbsleftwalk2.png");
		textures->leftWalk->push_back(temp);
	textures->inAirRight = new std::vector<sf::Texture>;
		temp.loadFromFile("img/hobbsrightjump.png");
		textures->inAirRight->push_back(temp);
	textures->inAirLeft = new std::vector<sf::Texture>;
		temp.loadFromFile("img/hobbsleftjump.png");
		textures->inAirLeft->push_back(temp);
	textures->rightAttack = new std::vector<sf::Texture>;
		temp.loadFromFile("img/hobbsrightattack.png");
		textures->rightAttack->push_back(temp);
	textures->leftAttack = new std::vector<sf::Texture>;
		temp.loadFromFile("img/hobbsleftattack.png");
		textures->leftAttack->push_back(temp);
	textures->rightStop = new std::vector<sf::Texture>;
		temp.loadFromFile("img/hobbsrightstop.png");
		textures->rightStop->push_back(temp);
	textures->leftStop = new std::vector<sf::Texture>;
		temp.loadFromFile("img/hobbsleftstop.png");
		textures->leftStop->push_back(temp);
	

}

void Hobbs::update()
{
	if(dashing)inMidAir= false;

	Animal::update();
	

	if(dashing)
	{
		dashFuel --;
		if(dashFuel<1)
		{
			dashing = false;
			if(getDirX()>0)setDirection(speed,0);
			else if(getDirX()<0){setDirection(-speed,0);}
		}

		
	}else if(dashFuel<dashLoad)dashFuel++;

	if(fireball!=0)
	{
		fireball->update();

		if(fireball->getRectangle().x-getRectangle().x > 1000 || fireball->getRectangle().x-getRectangle().x < -1000)
		{
			reload();
		}
	}
}
void Hobbs::paint(sf::RenderWindow &arg)
{
	Animal::paint(arg);
	if(fireball!=0)fireball->paint(arg);

	sf::CircleShape dashBar (5);
	dashBar.setPosition(sf::Vector2f(getRectangle().x+getRectangle().width/2,getRectangle().y-20));


	dashBar.setFillColor(sf::Color(0,(float) (dashFuel)/(float) (dashLoad)*255,0,150));	

	arg.draw(dashBar);
}
bool Hobbs::testCollisionWith(std::vector<Alien*> &arg)
{
	bool toReturn (false);

	toReturn = Animal::testCollisionWith(arg);
	if(fireball!=0)
		if(fireball->testCollisionWith(arg))
			reload();
	return toReturn;
}

void Hobbs::keyPressed(int keycode)
{
	int up (bindings[0]);
	int left (bindings[1]);
	int down (bindings[2]);
	int right (bindings[3]);
	int fire (bindings[4]);
	int dash (bindings[5]);

	if(keycode==up && !inMidAir){
		
		setDirection(getDirX(),getDirY()-20);
		setCoords(getRectangle().x,getRectangle().y-1);

		inMidAir = true;
	}
	if(keycode==left){
		setDirection(-speed,getDirY());
	}
	if(keycode==down){
		setDirection(getDirX(),getDirY()+10);
	}
	if(keycode==right){
		setDirection(speed,getDirY());
	}
	if(keycode==fire){
		shoot();
	}
	if(keycode==dash){
		Hobbs::dash();
	}
}

void Hobbs::keyReleased(int keycode)
{
	if(keycode==bindings[1] || keycode==bindings[3])setDirection(0,getDirY());
}
void Hobbs::setDirection(int dX,int dY)
{
	
	Animal::setDirection(dX,dY);

	if(dX>0)
	{
		movement = Movement::RIGHT_WALK;
		if(dY!=0)
		{
			movement = Movement::IN_AIR_RIGHT;
		}
	}else if(dX<0)
	{
		movement = Movement::LEFT_WALK;
		if(dY!=0)
		{
			movement = Movement::IN_AIR_LEFT;
		}	
	}else
	{
		if(movement == Movement::IN_AIR_RIGHT || movement == Movement::RIGHT_WALK)
		{
			movement = Movement::RIGHT_STOP;
		}else if(movement==Movement::IN_AIR_LEFT || movement == Movement::LEFT_WALK)
		{
			movement = Movement::LEFT_STOP;
		}
	}
}
void Hobbs::setControls(int up,int left,int down,int right,int fire,int dash)
{
	bindings[0] = up;
	bindings[1] = left;
	bindings[2] = down;
	bindings[3] = right;
	bindings[4] = fire;
	bindings[5] = dash;
}

void Hobbs::dash()
{
	if(dashFuel>=dashLoad)
	{
		dashFuel = dashLenght;
		dashing = true;
		setDirection(getDirX()*3,0);
	}

}

void Hobbs::shoot()
{

	if(fireball==0){

		if(movement==Movement::RIGHT_STOP || movement==Movement::RIGHT_WALK || movement==Movement::IN_AIR_RIGHT)
		{
			fireball = new Fireball(getRectangle().x+getRectangle().width+10,getRectangle().y,10,0);
			movement=Movement::RIGHT_ATTACK;
		}else{
			fireball = new Fireball(getRectangle().x-33,getRectangle().y,-10,0);
			movement=Movement::LEFT_ATTACK;
		}
	}
}
void Hobbs::reload()
{
	delete fireball;
	fireball = 0;

	if(movement==Movement::RIGHT_ATTACK)
		movement=Movement::RIGHT_STOP;
	else if (movement==Movement::LEFT_ATTACK)
		movement=Movement::LEFT_STOP;
}

int Hobbs::getUp()
{
	return bindings[0];
}
int Hobbs::getLeft()
{
	return bindings[1];
}
int Hobbs::getDown()
{
	return bindings[2];
}
int Hobbs::getRight()
{
	return bindings[3];
}
int Hobbs::getFire()
{
	return bindings[4];
}
int Hobbs::getDash()
{
	return bindings[5];
}