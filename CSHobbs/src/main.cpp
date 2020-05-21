#include "Hobbs.hpp"
#include "Wall.hpp"
#include "Level.hpp"

#include <iostream>

using namespace sf;


int main()
{

	while(true)
	{

		RenderWindow menu (VideoMode(300,300),"CS:Hobbs",Style::Close);
		menu.setFramerateLimit(10);

		RectangleShape play (Vector2f(300,150));
		RectangleShape quit (Vector2f(300,150));
		play.setFillColor(Color::Green);
		play.setPosition(0,0);
		quit.setFillColor(Color::Red);
		quit.setPosition(0,150);

		menu.draw(play);
		menu.draw(quit);
		menu.display();

		while(menu.isOpen())
		{
			Event event;

			while(menu.pollEvent(event))
			{
				if(event.type==Event::Closed)
				{
					menu.close();
					std::exit(0);
				}
				if(event.type==Event::MouseButtonPressed)
				{
					if(event.mouseButton.y<150){
						menu.close();
					}else
					{
						menu.close();
						std::exit(0);
					}
				}
			}

		}

		RenderWindow window (VideoMode(1920,1080),"Hobbs",Style::Fullscreen);
		window.setFramerateLimit(60);
		window.setVerticalSyncEnabled(true);

		Level lvl;
		lvl.load("lvl/sample.txt");

		while(window.isOpen()  && lvl.isEveryoneAlive())
		{
			Event event;

			while(window.pollEvent(event))
			{
				switch(event.type)
				{
					case Event::Closed:
						window.close();
					break;
					case Event::KeyPressed:
						lvl.keyPressed(event.key.code);
					break;
					case Event::KeyReleased:
						lvl.keyReleased(event.key.code);
					break;
				}
			}

			lvl.update();

			window.clear();
			lvl.paint(window);
			window.display();

		}

		window.close();
	}
	std::system("pause");
	return 0;
}