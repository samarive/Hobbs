#include "Camera.hpp"

Camera::Camera(Hobbs &arg):sf::View(sf::Vector2f(arg.getRectangle().x,arg.getRectangle().y),sf::Vector2f(cameraWidth =800,cameraHeight=450)),following(&arg)
{}
Camera::~Camera()
{}

void Camera::update()
{
	setCenter(sf::Vector2f(following->getRectangle().x,following->getRectangle().y));
}