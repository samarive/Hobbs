#include "Wall.hpp"
#include <string>

Wall::Wall(int x,int y,int width,int height,WallType aType):Alien::Alien(x,y,width,height)
{

	setClassID("wall");

	type = aType;

	std::string filename ("");
	switch(aType)
	{
		case WallType::MERCURY:
			filename = "img/mercuryblock.png";
		break;
		case WallType::VENUS:
			filename = "img/venusblock.png";
		break;
		case WallType::EARTH:
			filename = "img/earthblock.png";
		break;
		case WallType::MARS:
			filename = "img/marsblock.png";
		break;
		case WallType::JUPITER:
			filename = "img/jupiterblock.png";
		break;
		case WallType::SATURN:
			filename = "img/saturnblock.png";
		break;
		case WallType::URANUS:
			filename = "img/uranusblock.png";
		break;
		case WallType::NEPTUNE:
			filename = "img/neptuneblock.png";
		break;
		case WallType::GRASS:
			filename = "img/grass.png";
		break;
		case WallType::DIRT:
			filename = "img/dirt.png";
		break;
		default:
			filename = "img/missing.png";
		break;
	}

	texture.loadFromFile(filename);
	texture.setRepeated(true);

}
Wall::~Wall()
{

}

void Wall::paint(sf::RenderWindow &window)
{
	int x = getRectangle().x;
	int y = getRectangle().y;
	int width = getRectangle().width;
	int height = getRectangle().height;

	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setTextureRect({0,0,width,height});
	sprite.setPosition(sf::Vector2f(x,y));

	window.draw(sprite);

}
void Wall::update()
{

}
WallType Wall::getType()
{
	return type;
}