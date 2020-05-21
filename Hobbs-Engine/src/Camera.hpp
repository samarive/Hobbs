#ifndef CAMERA_HPP_INCLUDED
#define CAMERA_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "Hobbs.hpp"


class Camera:public sf::View
{

private:
	int cameraWidth;
	int cameraHeight;

	Hobbs* following;

public:

	Camera(Hobbs &arg);
	~Camera();

	void update();

};

#endif