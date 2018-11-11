#include "Engine.h"
#include <SFML/Graphics.hpp>

Engine::Engine()
{
	this->audioManager = NULL;
	this->levelManager = NULL;
	this->objectManager = NULL;
	this->accessoriesManager = NULL;
	this->engineMediator = NULL;
	this->window = NULL;
	this->camera = NULL;
	this->currentLevel = NULL;
	this->initialized = false;
}

Engine::~Engine()
{
	if (this->window) delete this->window;
	if (this->engineMediator) delete this->engineMediator;
	if (this->audioManager) delete this->audioManager;
	if (this->objectManager) delete this->objectManager;
	if (this->levelManager) delete this->levelManager;
	if (this->accessoriesManager) delete this->accessoriesManager;
	if (this->camera) delete this->camera;
}

bool Engine::Init(std::map<int, Level*> levelArchive, int initLevelID, std::map <int, Entity*> objectArchive)
{
	if ( this->window == NULL )
		this->window = new sf::RenderWindow(sf::VideoMode(800, 600, 32), "RPG");

	this->window->setFramerateLimit(30);

	this->engineMediator = new EngineMediator();
	this->audioManager = new AudioManager();
	this->levelManager = new LevelManager(levelArchive, this->camera, this->engineMediator, initLevelID);
	this->objectManager = new ObjectManager(objectArchive, this->engineMediator);
	this->camera = new Camera(this->engineMediator, this->levelManager->GetCurrentLevel());
	this->accessoriesManager = new AccessoriesManager();

	this->engineMediator->Init(this->levelManager, this->objectManager, this->camera, this->audioManager);

	this->initialized = true;

	return this->initialized;
}

void Engine::SetWindowResolution(int width, int height, int bitsPerPixel, string name)
{
	if ( this->window != NULL)
	{
		delete this->window;
		this->window = new sf::RenderWindow(sf::VideoMode(width, height, bitsPerPixel), name);
	}
	else
	{
		this->window = new sf::RenderWindow(sf::VideoMode(width, height, bitsPerPixel), name);
	}
}

void Engine::SetWindowFrameRate(int frameRateLimit)
{
	this->window->setFramerateLimit(frameRateLimit);
}

void Engine::LoadImages()
{
	sf::Image sprite;
	sf::Image sprite2;
	sprite.loadFromFile("Images/tile1.png");
	sprite2.loadFromFile("Images/tile2.png");
	
}

void Engine::RenderFrame()
{
	this->window->clear();

	this->levelManager->Render(this->window);
	this->objectManager->Render(this->window);

	window->display();
}

void Engine::ProcessInput()
{
	sf::Event evt;
	bool mouseDown = false;

	//Loop through all window events
	while(window->pollEvent(evt))
	{
		this->windowEvent = evt;

		if(evt.type == sf::Event::Closed)
			window->close();
		
		if((evt.type == sf::Event::MouseButtonPressed) && (mouseDown == false))
		{
			sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
			sf::Vector2f camPosition;
			camPosition.x = camera->GetPosition().x + mousePosition.x;
			camPosition.y = camera->GetPosition().y + mousePosition.y;
			camera->GoToCenter(camPosition);
			mouseDown = true;
		}

		// Escape key : exit
		if ((evt.type == sf::Event::KeyPressed) && (evt.key.code == sf::Keyboard::Escape))
		{
			window->close();
			return;
		}

		if(evt.type == sf::Event::MouseButtonReleased)
			mouseDown = false;
	}
}

void Engine::Update()
{
	this->levelManager->updateCurrentLevel();
	this->objectManager->Update(this->windowEvent);
	this->camera->Update(this->window);
}


void Engine::MainLoop()
{
	if (!this->initialized)
	{
		//log Error
		return;
	}

	//Loop until our window is closed
	while(window->isOpen())
	{
		ProcessInput();
		Update();
		RenderFrame();
	}
}

void Engine::LoadLevel()
{
	
}

void Engine::Start()
{
	MainLoop();
}
