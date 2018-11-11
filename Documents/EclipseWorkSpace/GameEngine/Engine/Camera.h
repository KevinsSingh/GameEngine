#ifndef _CAMERA_H
#define _CAMERA_H

#include "EngineMediator.h"
#include <SFML/Graphics.hpp>
#include "Level.h"

class EngineMediator;

class Camera
{
private:
		//Absolute position of camera (number of pixels from origin of level map)
		sf::Vector2f _position;
		//Target position camera is moving towards
		sf::Vector2f _target;
		//Size of camera
		sf::Vector2f _size;
		//Speed of camera, a value between 0.0 and 1.0
		float speed;
		//Zoom of the camera
		float zoom;
		//Level Map that camera will navigate through
		Level* map;
		//BOOL position changed, must update drawing bounds of Map
		bool moved;
		//Pointer to the Mediator
		EngineMediator* engineMediator;

protected:
		sf::Rect<float> getDrawingBounds();

public:
		Camera();
		Camera(EngineMediator* engineMediator, Level* Map);
		~Camera();

		//View object of the camera
		sf::View cameraView;

		//Moves camera immediately to coordinates
		void Move(sf::Vector2f target);
		
		//Centers the Camera around the Target
		void GoToCenter(sf::Vector2f);
		
		//Set the Map Player is currently in
		void SetMap(Level* Map);
		
		//Set Drawing bounds for the map
		void SetDrawingBounds();

		//Return The View object
		sf::View GetView();
		
		//Updates camera position
		void Update(sf::RenderWindow* window);
		
		//Returns absolute position of the camera relative to the origin of the map
		sf::Vector2i GetPosition() { return sf::Vector2i((int)_position.x, (int)_position.y); }	
		
		//Helper function for retreiving camera's offset from nearest tile
		sf::Vector2i GetTileOffset(int tileSize) { return sf::Vector2i((int)(_position.x) % tileSize, (int)(_position.y) % tileSize); }
		
		//Helper function for retreiving a rectangle defining
		//which tiles are visible through camera
		sf::IntRect GetTileBounds(sf::Vector2i tileSize);
};

#endif
