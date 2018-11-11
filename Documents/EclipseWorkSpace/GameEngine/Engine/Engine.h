#ifndef _ENGINE_H  
#define _ENGINE_H      

#include <SFML/Graphics.hpp>
#include "Camera.h"
#include "AudioManager.h"
#include "LevelManager.h"
#include "ObjectManager.h"
#include "AccessoriesManager.h"
#include "EngineMediator.h"
#include <map>

class Engine  
{

private:

	//TEST FUNCTIONS
	void LoadImages();
	void LoadLevel();

	//Flags
	bool initialized;

	//Engine Managers
	AudioManager* audioManager;
	LevelManager* levelManager;
	ObjectManager* objectManager;
	AccessoriesManager* accessoriesManager;
	EngineMediator* engineMediator;

	Level* currentLevel;
	Camera* camera;

	//SFML Render Window
	sf::RenderWindow* window;
	sf::Event windowEvent;

	//Main Game Loop
	void MainLoop();

	//Renders one frame
	void RenderFrame();

	//Processes user input
	void ProcessInput();
	
	//Updates all Engine internals
	void Update();

public:  

	Engine();

	//Initializes the engine
	bool Init(std::map<int, Level*> levelArchive, int initLevelID, std::map <int, Entity*> objectArchive);

	//Setup Game Window
	void SetWindowResolution(int width, int height, int bitsPerPixel, string name);
	void SetWindowFrameRate(int frameRateLimit);

	//Starts the engine
	void Start();

	~Engine();
};

#endif 


