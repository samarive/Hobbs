#ifndef LEVEL_HPP_INCLUDED
#define LEVEL_HPP_INCLUDED

/*
	Level (translate crude text files to Alien* vector and the opposite)
*/

#include "Camera.hpp"
#include "Hobbs.hpp"
#include "Wall.hpp"
#include <vector>
#include <string>

class Level
{
private:

	sf::Texture background;
	std::string backgroundFilePath;

	std::vector<Alien*> entities;

	std::vector<Camera*> cameras;

public:
	Level();
	~Level();


	void paint(sf::RenderWindow &arg);
	void update();
	bool load(std::string fileName);
	bool save(std::string fileName);
	void keyPressed(int code);
	void keyReleased(int code);

	void addAlien(Alien* alien);
	bool setBackground(std::string fileName);

	bool isEveryoneAlive();

	std::string toString();
};

std::ostream& operator<<(std::ostream &str,Level &lvl);

std::string getStringFromTo(char beg,char end,std::string const& arg,int startAt);

#endif