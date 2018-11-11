#include <SFML/Graphics.hpp>
#include <math.h>
#include "Camera.h"

Camera::Camera()
{
	_size.x = 800;
	_size.y = 600;	

	_position.x = 400;
	_position.y = 300;

	_target.x = _position.x;
	_target.y = _position.y;

	speed = 0.5;
	zoom = 0.75;

	moved = false;

	cameraView = sf::View(_position, _size);

	cameraView.zoom(zoom);

	this->map = NULL;
	this->engineMediator = NULL;
}

Camera::Camera(EngineMediator* engineMediator, Level* Map)
{
	_size.x = 800;
	_size.y = 600;

	_position.x = 400;
	_position.y = 300;

	_target.x = _position.x;
	_target.y = _position.y;

	speed = 0.5;
	zoom = 0.75;

	moved = false;

	cameraView = sf::View(_position, _size);

	cameraView.zoom(zoom);

	this->map = Map;

	this->engineMediator = engineMediator;
}

Camera::~Camera()
{
}

void Camera::SetMap(Level* Map)
{
	this->map = Map;

	if (map != NULL)
		map->SetDrawingBounds(getDrawingBounds());

}

void Camera::SetDrawingBounds()
{
	if (map != NULL)
		map->SetDrawingBounds(getDrawingBounds());
}

//Moves camera based on an offset given in 'target'
void Camera::Move(sf::Vector2f target)
{
	_position.x += target.x;
	_position.y += target.y;

	cameraView.move(target);
}

//Centers target at coordinates
void Camera::GoToCenter(sf::Vector2f position)
{
	_position = position;
	cameraView.setCenter(position);
	moved = true;
}

sf::View Camera::GetView()
{
	return this->cameraView;
}

sf::Rect<float> Camera::getDrawingBounds()
{
	sf::Vector2f position;
	sf::Rect<float> drawingBounds;

	position = cameraView.getCenter();

	drawingBounds.left = position.x - _size.x/2;
	drawingBounds.top = position.y - _size.y/2;
	drawingBounds.height = _size.y + 64;
	drawingBounds.width = _size.x + 64;

	return drawingBounds;
}

void Camera::Update(sf::RenderWindow* window)
{
	this->GoToCenter(this->engineMediator->GetPositionOfMainChar());
		
	if(moved)
	{	
		map->SetDrawingBounds(getDrawingBounds());
		moved = false;
	}

	window->setView(this->cameraView);
}

sf::IntRect Camera::GetTileBounds(sf::Vector2i tileSize)
{
	int x = (int)(_position.x / tileSize.x);
	int y = (int)(_position.y / tileSize.y);

	//+1 in case camera size isn't divisible by tileSize
	//And +1 again because these values start at 0, and
	//we want them to start at one
	int w = (int)(_size.x / tileSize.x + 2);
	int h = (int)(_size.y / tileSize.y + 2);

	//And +1 again if we're offset from the tile
	if(x % tileSize.x != 0)
		w++;
	if(y % tileSize.y != 0)
		h++;

	return sf::IntRect(x, y, w, h);
}
