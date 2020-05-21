#include "Level.hpp"
#include <fstream>
#include <iostream>

Level::Level():cameraView(true)
{
	background.loadFromFile("img/missing.png");
	backgroundFilePath = "img/missing.png";
}
Level::~Level()
{
	for(int i = 0;i<entities.size();i++)
	{
		delete entities.at(i);
	}
	for(int i = 0;i<cameras.size();i++)
	{
		delete cameras.at(i);
	}

}

void Level::paint(sf::RenderWindow &arg)
{
	sf::Sprite bg;
	bg.setTexture(background);

	while(bg.getGlobalBounds().width<arg.getSize().x || bg.getGlobalBounds().height<arg.getSize().y)
	{
		bg.scale(1.1f,1.1f);
	}

	arg.draw(bg);

	if(cameraView){
		
		std::vector<int> separatorsX; 


		for(int i = 0;i<entities.size();i++)
		{
			for(int i1=0;i1<cameras.size();i1++){
					
				cameras.at(i1)->setViewport(sf::FloatRect(i1*1.f/cameras.size(),0.f,1.f/cameras.size(),1.f));
				cameras.at(i1)->setSize(sf::Vector2f(arg.getSize().x/cameras.size(),arg.getSize().y));

				arg.setView(*cameras.at(i1));
				
				int camX (cameras.at(i1)->getCenter().x-cameras.at(i1)->getSize().x/2);
				int camY (cameras.at(i1)->getCenter().y-cameras.at(i1)->getSize().y/2);
				int camWidth (cameras.at(i1)->getSize().x);
				int camHeight (cameras.at(i1)->getSize().y);

				Hitbox hb (entities.at(i)->getRectangle());

				if(entities.at(i)->getClassID().find("hobbs")==std::string::npos){
					if(hb.x+hb.width>camX && hb.x<camX+camWidth && hb.y+hb.height>camY && hb.y<camY+camHeight)
						entities.at(i)->paint(arg);
				}else{
					entities.at(i)->paint(arg);
				}

				arg.setView(arg.getDefaultView());
				
			}
		}

		for(int i = 1;i<cameras.size();i++)
		{
			sf::RectangleShape separator (sf::Vector2f(10,arg.getSize().y));
			separator.setPosition(sf::Vector2f(i*(arg.getSize().x/cameras.size()),0));
			separator.setFillColor(sf::Color::Black);

			arg.draw(separator);
		}
    }else{
    	for(int i = 0;i<entities.size();i++)
		{
			entities.at(i)->paint(arg);
		}
    }

}
void Level::keyPressed(int code)
{
	for(int i = 0;i<entities.size();i++)
	{
		if(entities.at(i)->getClassID().find("hobbs")!=std::string::npos)
		{
			Hobbs* hobbs (0);
			hobbs = (Hobbs*) entities.at(i);
			hobbs->keyPressed(code);
		}	
	}
}
void Level::keyReleased(int code)
{
	for(int i = 0;i<entities.size();i++)
	{
		if(entities.at(i)->getClassID().find("hobbs")!=std::string::npos)
		{
			Hobbs* hobbs (0);
			hobbs = (Hobbs*) entities.at(i);
			hobbs->keyReleased(code);
		}	
	}
}

void Level::update()
{
	for(int i = 0;i<cameras.size();i++)
	{
		cameras.at(i)->update();
	}

	for(int i = 0;i<entities.size();i++)
	{
		
		if(entities.at(i)->getClassID().find("animal")!=std::string::npos){
			Animal* ani (0);
			ani =  (Animal*) entities.at(i);
			ani->testCollisionWith(entities);
		}

		entities.at(i)->update();
	}
}

bool Level::load(std::string fileName)
{
	std::ifstream input (fileName);

	if(!input)
	{
		return false;
	}

	std::string temp;

	getline(input,temp);

	backgroundFilePath = temp;
	if(!background.loadFromFile(temp))
	{	
		background.loadFromFile("img/missing.png");
		backgroundFilePath =  "img/missing.png";
	}
	background.setRepeated(false);

	while(getline(input,temp))
	{
		std::vector<std::string> sProps;

		int i_ (0);
		do
		{
			sProps.push_back(getStringFromTo(',',',',temp,i_));

			i_++;
		}while(sProps.at(sProps.size()-1)!="");

		sProps.pop_back();

		std::vector<int> iProps;

		for(int i = 0;i<sProps.size();i++)
		{

			iProps.push_back(std::stoi(sProps.at(i)));
		}

		switch(iProps.at(0))
		{
			case 0:{
				entities.push_back(new Hobbs(iProps.at(1),iProps.at(2)));
				Hobbs* hobbs ((Hobbs*) entities.at(entities.size()-1));
				hobbs->setControls(iProps.at(3),iProps.at(4),iProps.at(5),iProps.at(6),iProps.at(7),iProps.at(8));
				cameras.push_back(new Camera(*hobbs));
			}
			break;
			case 1:
				entities.push_back(new Wall(iProps.at(1),iProps.at(2),iProps.at(3),iProps.at(4),(WallType) iProps.at(5)));
			break;
		}
	}


	input.close();

	return true;
}
bool Level::save(std::string fileName)
{
	std::ofstream output (fileName);

	if(!output)return false;

	std::string toSave (backgroundFilePath+"\n");

	for(int i = 0;i<entities.size();i++)
	{

		Alien* entity (entities.at(i));

		if(entity->getClassID().find("hobbs")!=std::string::npos)
		{
			Hobbs* hobbs = ((Hobbs*) entity);
			toSave += ",0,"+std::to_string(hobbs->getRectangle().x)+","+std::to_string(hobbs->getRectangle().y)+","+std::to_string(hobbs->getUp())+","+std::to_string(hobbs->getLeft())+","+std::to_string(hobbs->getDown())+","+std::to_string(hobbs->getRight())+","+std::to_string(hobbs->getFire())+","+std::to_string(hobbs->getDash())+",\n";
		}else if(entity->getClassID().find("wall")!=std::string::npos)
		{	
			Wall* wall = ((Wall*) entity);
			toSave += ",1,"+std::to_string(wall->getRectangle().x)+","+std::to_string(wall->getRectangle().y)+","+std::to_string(wall->getRectangle().width)+","+std::to_string(wall->getRectangle().height)+","+std::to_string((int) wall->getType())+",\n";
		}	
	}

	output << toSave;

	return true;
}
std::string Level::toString()
{

	std::string toReturn ("");

	for(int i = 0;i<entities.size();i++)
	{
		toReturn+=entities.at(i)->getClassID()+"\n";
	}
	toReturn+="("+std::to_string(entities.size())+" entities)"+"\n______________\n";

	return toReturn;
}

std::string getStringFromTo(char beg,char end,std::string const& arg,int startAt)
{
	std::string toReturn ("");

	int occurenceNbr (0);

	bool saving (false);

	for(int i = 0;i<arg.size();i++)
	{
		if(arg.at(i)==beg && !saving)
		{
			if(occurenceNbr==startAt)
			{
				saving = true;
				continue;
			}else
			{
				occurenceNbr++;
			}
		}
		if(saving && arg.at(i)==end)
		{
			break;
		}

		if(saving)toReturn+=arg.at(i);
	}

	return toReturn;
}

std::ostream& operator<<(std::ostream &str,Level &lvl)
{
	str << lvl.toString();

	return str;
}

void Level::addAlien(Alien* alien)
{
	entities.push_back(alien);

	if(alien->getClassID().find("hobbs")!=std::string::npos)
	{
		cameras.push_back(new Camera(*((Hobbs*) alien)));
	}
}
bool Level::setBackground(std::string fileName)
{
	backgroundFilePath = fileName;
	if(!background.loadFromFile(fileName))
	{
		backgroundFilePath = "img/missing.png";
		return false;
	}
	return true;
}
bool Level::isEveryoneAlive()
{

	for(int i = 0;i<entities.size();i++)
	{

		if(entities.at(i)->getClassID().find("animal")!=std::string::npos){
			
			Animal* ani  ((Animal*) entities.at(i));

			if(!(ani->isAlive()))
			{
				return false;
			}
		}
	}

	return true;
}

void Level::setCameraView(bool arg)
{
	cameraView = arg;
}