#include <SFML/Graphics.hpp>
#include "Level.hpp"

using namespace sf;

int main()
{
	RenderWindow win (VideoMode(800,450),"Hobbs motor test",Style::Close);

	win.setFramerateLimit(60);
	win.setVerticalSyncEnabled(true);

	Level lvl;
	lvl.load("lvl/sample.txt");

	while(win.isOpen())
	{
		Event event;

		while(win.pollEvent(event))
		{
			switch(event.type)
			{
				case Event::KeyPressed:
					lvl.keyPressed(event.key.code);
				break;
				case Event::KeyReleased:
					lvl.keyReleased(event.key.code);
				break;
				case Event::Closed:
					win.close();
				break;
			}
		}

		lvl.update();
		win.clear();
		lvl.paint(win);
		win.display();
	}
}