#include <iostream>
#include <sstream>
#include "Engine/Level.h"
#include "Engine/Camera.h"
#include "Engine/Engine.h"
#include "MainCharacter.h"
#include "GameCharacter.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace std;


int test()
{
	Level *level = new Level();
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
	sf::Texture image;
	sf::Sprite spr;

	//image.loadFromFile("Images/mchip0.bmp");
	//spr.setTexture(image);

	level->LoadFromFile("Maps/test.tmx");



	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//window.clear();
		//window.draw(spr);
		window.display();
	}


	return 0;
}

int main()
{
	//return test();

	Engine *engine = new Engine();
	std::map<int, Level*> levelArchive;
	std::map <int, Entity*> objectArchive;
	std::vector <EntityRecord> entityList;
	EntityRecord record;
	EntityRecord record1;


	sf::Texture spriteImage;
	spriteImage.loadFromFile("Images/Link.png");
	MainCharacter* chara = new MainCharacter(sf::Vector2i(7,6), spriteImage);

	sf::Texture spriteImage1;
	spriteImage1.loadFromFile("Images/rpgsprites1/ninja_m.png");
	GameCharacter* ninja = new GameCharacter(sf::Vector2i(3,4), spriteImage1);


	record.objectID = 0;
	record.position = chara->GetSprite().getPosition();
	entityList.push_back(record);

	record1.objectID = 1;
	record1.position = sf::Vector2f(100,100);
	entityList.push_back(record1);

	Level* level = new Level();
	level->LoadFromFile("Maps/test.tmx");
	level->SetEntityList(entityList);

	levelArchive.insert(std::pair<int, Level*>(0, level));
	objectArchive.insert(std::pair<int, Entity*>(0, chara));
	objectArchive.insert(std::pair<int, Entity*>(1, ninja));

	engine->Init(levelArchive, 0, objectArchive);

	engine->Start();

	//Memory Cleanup
	delete engine;
	delete chara;
	delete ninja;
	delete level;


/*
	Level* level = new Level();
	sf::Texture spriteImage;
	MainCharacter* chara = new MainCharacter();
	Camera* camera = new Camera();
	float frameRate = 10.0;

	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(800, 600, 32), "RPG");
	spriteImage.loadFromFile("Images/Link.png");
	sf::Event Event;
	sf::Clock Clock;

	chara->SetImage(spriteImage);
	level->LoadFromFile("Maps/test.tmx");
	camera->SetMap(level);

	sf::Text Text;
	sf::Font font;
	if ( !font.loadFromFile("Images/OpenSans-Regular.ttf"))
	{
	 std::cout<< "Error loading font file\n";
	}

	Text.setFont(font);
	Text.setPosition(0,0);
	
	window->setFramerateLimit(30);
	//window->useVerticalSync(true);
	//window->setView(camera->cameraView);
	while(1)
	{
		while (window->pollEvent(Event))
		{
			// Close window : exit
			if (Event.type == sf::Event::Closed)
			{
				//window->Close(); Cannot close window due to driver bug
				return 0;
			}

			// Escape key : exit
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
			{
				window->close();
				return 0;
			}

			//Mouse Click
		    if (Event.type == sf::Event::MouseButtonPressed)
			{
				//sf::Mouse mouse;
				//sf::Vector2f mousePos;
				//mousePos = mouse.getPosition();
				//camera->GoToCenter(mousePos);
			}
		}

		stringstream ss (stringstream::in | stringstream::out);
		ss.flush();
		ss << frameRate;
		string test = ss.str();
		Text.setString(test);
		
		

		sf::Time ElapsedTime = Clock.getElapsedTime();
		frameRate = 1/(ElapsedTime.asSeconds());
		Clock.restart();
		
		sf::Vector2f position = chara->GetSprite().getPosition();
		//--------------------------------RENDERING-------------------------------------
		
		window->clear();

		chara->Update( Event);
		chara->getNextPosition();
		chara->SetSpritePosition();
		//camera->Update(window);

		window->draw(chara->GetSprite());
		window->draw(Text);

		window->display();

		camera->GoToCenter(position);

		//--------------------------------------------------------------------------------


	}
*/



}


