#include "Hobbs.hpp"
#include "Wall.hpp"
#include "Level.hpp"

#include <string>
#include <iostream>
#include <vector>

using namespace sf;

int keyInputBox();
std::string textInputBox();
WallType typeBox();

int main()
{

	bool isCtrlPressed (false);

	int action (0);

	RenderWindow window (VideoMode(1920,1080),"Hobbs",Style::Fullscreen);
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);

	View camera (Vector2f(960,540),Vector2f(1920,1080));
	camera.setViewport(FloatRect(0.f,0.f,1.f,1.f));

	Level lvl;

	lvl.setCameraView(false);

	int lastClick[] = {
		-1,
		-1
	};

	bool wallStarted (false);

	while(window.isOpen())
	{
		Event event;

		window.setView(camera);

		while(window.pollEvent(event))
		{
			switch(event.type)
			{
				case Event::Closed:
					window.close();
				break;
				case Event::KeyPressed:
					if(event.key.code == Keyboard::LControl)
						isCtrlPressed = true;
					if(event.key.code == Keyboard::S && isCtrlPressed)
					{
						lvl.save("lvl/sample.txt");
					}
					if(event.key.code == Keyboard::B && isCtrlPressed)
					{
						lvl.setBackground(textInputBox());
					}
					if(event.key.code == Keyboard::Numpad8)
					{
						camera.move(0,-5);
					}
					if(event.key.code == Keyboard::Numpad2)
					{
						camera.move(0,5);
					}
					if(event.key.code == Keyboard::Numpad4)
					{
						camera.move(-5,0);
					}
					if(event.key.code == Keyboard::Numpad6)
					{
						camera.move(5,0);
					}
					if(event.key.code == Keyboard::Right){	
						action++;
					}
					if(event.key.code == Keyboard::Left){
						action--;
					}
					if(action>1)
					{
						action = 1;
					}
					if(action<0)
					{
						action = 0;
					}
				break;
				case Event::KeyReleased:
					if(event.key.code == Keyboard::LControl)
						isCtrlPressed = false;
				break;
				case Event::MouseButtonPressed:

					int x (window.mapPixelToCoords(Vector2i(event.mouseButton.x,event.mouseButton.y)).x);
					int y (window.mapPixelToCoords(Vector2i(event.mouseButton.x,event.mouseButton.y)).y);

					if(!wallStarted){
						switch(action)
						{
							case 0:{
								Hobbs* hobbs = new Hobbs(x,y);//is deleted in Level.cpp

								int keys[6];

								for(int i = 0;i<6;i++)
								{
									keys[i] = keyInputBox();
								}

								hobbs->setControls(keys[0],keys[1],keys[2],keys[3],keys[4],keys[5]);

								lvl.addAlien(hobbs);
							}
							break;
							case 1:
								lastClick[0] = x;
								lastClick[1] = y;
								wallStarted = true;
							break;
						}
					}else{
						if(x<lastClick[0])
						{
							int b (x);

							x = lastClick[0];

							lastClick[0]  = b;
						}
						if(y<lastClick[1])
						{
							int b (y);

							y = lastClick[1];

							lastClick[1]  = b;
						}

						lvl.addAlien(new Wall(lastClick[0],lastClick[1],x-lastClick[0],y-lastClick[1],typeBox()));
						wallStarted = false;
					}

				break;
			}
		}

		window.clear();

		window.setView(camera);

		lvl.paint(window);
		window.display();

	}

	std::system("pause");
	return 0;
}

int keyInputBox()
{
	RenderWindow box (VideoMode(500,480),"Press a key",Style::Titlebar);
	box.setFramerateLimit(30);

	RectangleShape ok (Vector2f(300,100));
	ok.setFillColor(Color(0,0,0));
	ok.setPosition(100,350);

	int key (-1);

	while(box.isOpen())
	{
		Event event;

		while(box.pollEvent(event))
		{
			switch(event.type)
			{
				case Event::MouseButtonPressed:
					if(event.mouseButton.x>100 && event.mouseButton.x<400 && event.mouseButton.y > 350 && event.mouseButton.y < 450)
					{
						box.close();
					}
				break;
				case Event::KeyPressed:
					key = event.key.code;
					ok.setFillColor(Color::Green);
				break;
			}
		}

		box.clear(Color::White);
		box.draw(ok);
		box.display();
	}

	return key;
}
WallType typeBox()
{
	RenderWindow box (VideoMode(500,500),"Choose block",Style::Titlebar);
	box.setFramerateLimit(1);

	WallType type (NONE);

	std::vector<std::string> imgFiles;
	imgFiles.push_back("img/wall.png");
	imgFiles.push_back("img/mercuryblock.png");
	imgFiles.push_back("img/venusblock.png");
	imgFiles.push_back("img/earthblock.png");
	imgFiles.push_back("img/marsblock.png");
	imgFiles.push_back("img/jupiterblock.png");
	imgFiles.push_back("img/saturnblock.png");
	imgFiles.push_back("img/uranusblock.png");
	imgFiles.push_back("img/neptuneblock.png");
	imgFiles.push_back("img/grass.png");
	imgFiles.push_back("img/dirt.png");

	box.clear(Color::White);

	int abs (-32);
	int ord (0);

	for(int i = 0;i<imgFiles.size();i++)
	{
		abs += 32;

		if(abs>468)
		{
			abs = 0;
			ord+=32;
		}

		Texture texture;
		texture.loadFromFile(imgFiles.at(i));
		Sprite sprite;
		sprite.setTexture(texture);
		sprite.setPosition(abs,ord);
		box.draw(sprite);
	}

	box.display();

	while(box.isOpen())
	{
		Event event;

		while(box.pollEvent(event))
		{
			if(event.type==Event::MouseButtonPressed)
			{
				switch(keyInputBox())
				{
					case Keyboard::A:
						type = WallType::NONE;
					break;
					case Keyboard::Z:
						type = WallType::MERCURY;
					break;
					case Keyboard::E:
						type = WallType::VENUS;
					break;
					case Keyboard::R:
						type = WallType::EARTH;
					break;
					case Keyboard::T:
						type = WallType::MARS;
					break;
					case Keyboard::Y:
						type = WallType::JUPITER;
					break;
					case Keyboard::U:
						type = WallType::SATURN;
					break;
					case Keyboard::I:
						type = WallType::URANUS;
					break;
					case Keyboard::O:
						type = WallType::NEPTUNE;
					break;
					case Keyboard::P:
						type = WallType::GRASS;
					break;
					case Keyboard::Q:
						type = WallType::DIRT;
					break;
				}

				box.close();
			}
		}
	}

	return type;
}
std::string textInputBox()
{
	RenderWindow popup (VideoMode(300,300),"Type text",Style::Titlebar);
	popup.setFramerateLimit(30);

	RectangleShape okButton (Vector2f(100,50));
	okButton.setPosition(Vector2f(150,200));
	okButton.setFillColor(Color::Green);

	Text question;
	Font font;
	font.loadFromFile("arial.ttf");
	question.setString("Type text :");
	question.setFont(font);
	question.setCharacterSize(18);
	question.setPosition(Vector2f(10,20));
	question.setFillColor(Color::Black);

	Text written;
	written.setString("");
	written.setFillColor(Color::Black);
	written.setPosition(Vector2f(10,50));
	written.setFont(font);
	written.setCharacterSize(14);


	while(popup.isOpen()){

		Event event;

		while(popup.pollEvent(event)){

			switch(event.type){
				case Event::TextEntered:
					if(event.text.unicode<128 && event.text.unicode!=8){
						written.setString(written.getString()+event.text.unicode);
					}else if(event.text.unicode==8 && written.getString() != ""){

						std::string temp ("");
						std::string old (written.getString());

						for(int i=0;i<old.size()-1;i++){
							temp+=old.at(i);
						}

						written.setString(temp);

					}

				break;
				case Event::MouseButtonPressed:
					if(event.mouseButton.button == Mouse::Left){
						
						int x(event.mouseButton.x);
						int y(event.mouseButton.y);
						
						if(x>150 && x<250 && y>200 && y<250)
							popup.close();
					}
				break;
			}

		}

		popup.clear(Color::White);
		popup.draw(okButton);
		popup.draw(question);
		popup.draw(written);
		popup.display();

	}

	return written.getString();
}