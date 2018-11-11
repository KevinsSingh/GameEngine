/*********************************************************************
SFML Tiled Map Loader


*********************************************************************/

#include "Level.h"

#include <iostream>
#include "../EngineLib/tinyxml.h"

int Object::GetPropertyInt(std::string name)
{
    int i;
    i = atoi(properties[name].c_str());

    return i;
}

float Object::GetPropertyFloat(std::string name)
{
    float f;
    f = strtod(properties[name].c_str(), NULL);

    return f;
}

std::string Object::GetPropertyString(std::string name)
{
    return properties[name];
}

Level::Level()
{
	width = 0;
	height = 0;
	tileWidth = 0;
	tileHeight = 0;

	//Used to offset the tile number.
	firstTileID = 0;

	//Used to clip anything off screen.
	drawingBounds = sf::Rect<float>();

	//The tileset image.
	tilesetImage = sf::Texture();

	//This stores all the solid areas (objects with type 'solid'). This gets checked by the IsSolid function.
	solidObjects = std::vector <sf::Rect <int> >();

	//This stores all objects (including 'solid' types)
	objects = std::vector <Object>();

	//This stores each layer of sprites/tiles so they can be drawn in order.
	layers = std::vector <Layer>();

	//This stores the entities that should be loaded by the Object manager
	entityList = std::vector <EntityRecord>();
}

Level::~Level()
{
    //dtor
}

bool Level::LoadFromFile(std::string filename)
{
    TiXmlDocument levelFile(filename.c_str());

    if (!levelFile.LoadFile())
    {
        std::cout << "Loading level \"" << filename << "\" failed." << std::endl;
        return false;
    }

    //Map element. This is the root element for the whole file.
    TiXmlElement *map;
    map = levelFile.FirstChildElement("map");

    //Set up misc map properties.
    width = atoi(map->Attribute("width"));
    height = atoi(map->Attribute("height"));
    tileWidth = atoi(map->Attribute("tilewidth"));
    tileHeight = atoi(map->Attribute("tileheight"));

    //Tileset stuff
    TiXmlElement *tilesetElement;
    tilesetElement = map->FirstChildElement("tileset");
    firstTileID = atoi(tilesetElement->Attribute("firstgid"));

    //Tileset image
    TiXmlElement *image;
    image = tilesetElement->FirstChildElement("image");
    std::string imagepath = image->Attribute("source");

    if (!tilesetImage.loadFromFile(imagepath))//Load the tileset image
    {
        std::cout << "Failed to load tile sheet." << std::endl;
        return false;
    }

    //tilesetImage.createMaskFromColor(sf::Color(255, 0, 255));
    tilesetImage.setSmooth(false);

    //Columns and rows (of tileset image)
    sf::Vector2u size;
    size = tilesetImage.getSize();
    int columns = size.x/ tileWidth;
    int rows = size.y/ tileHeight;

    std::vector <sf::Rect<int> > subRects;//container of subrects (to divide the tilesheet image up)

    //tiles/subrects are counted from 0, left to right, top to bottom
    for (int y = 0; y < rows; y++)
    {
        for (int x = 0; x < columns; x++)
        {
            sf::Rect <int> rect;
            rect.left = x * tileWidth;
            rect.top = y * tileHeight;
            rect.width = tileWidth;
            rect.height = tileHeight;

            subRects.push_back(rect);
        }
    }


    //TileSet properties
    TiXmlElement *tileSetElement = map->FirstChildElement("tileset");

    //	Validate TileSet section for tile properties
	TiXmlElement *imageElement = tileSetElement->FirstChildElement("image");

	//Tile Property map used to populate Tile Record later on.
	std::map<int, bool> tilePropMap;

	if (imageElement == NULL)
	{
		std::cout << "Bad map. No image file found." << std::endl;
		return false;
	}

	TiXmlElement *tileProp = tileSetElement->FirstChildElement("tile");

	if (tileProp == NULL)
	{
		std::cout << "No Tile Properties defined." << std::endl;
	}

	int tileID = 0;

	while( tileProp )
	{
		if (tileProp->Attribute("id") != NULL)
		{
			tileID = atoi(tileProp->Attribute("id"));
		}

		TiXmlElement *properties = tileProp->FirstChildElement("properties");
		if (properties != NULL)
		{
			TiXmlElement *property = properties->FirstChildElement("property");

			if (property != NULL)
			{
				int value = atoi(property->Attribute("value"));
				bool isSolid = (bool)value;

				//Set property of Tile
				tilePropMap[tileID] = isSolid;
			}
		}

		tileProp = tileProp->NextSiblingElement("tile");
	}


    //Layers
    TiXmlElement *layerElement = map->FirstChildElement("layer");

    while (layerElement)
    {
        Layer layer;
        if (layerElement->Attribute("opacity") != NULL)//check if opacity attribute exists
        {
            float opacity = strtod(layerElement->Attribute("opacity"), NULL);//convert the (string) opacity element to float
            layer.opacity = 255 * opacity;
        }
        else
        {
            layer.opacity = 255;//if the attribute doesnt exist, default to full opacity
        }

        //	Validate Layer section Contains Map Data.
		TiXmlElement *layerDataElement;
		layerDataElement = layerElement->FirstChildElement("data");

		if (layerDataElement == NULL)
		{
			std::cout << "Bad map. No layer information found." << std::endl;
		}

		TiXmlElement *tileElement;
		tileElement = layerDataElement->FirstChildElement("tile");

		if (tileElement == NULL)
		{
			std::cout << "Bad map. No tile information found." << std::endl;
			return false;
		}

        int x = 0;
        int y = 0;

        while (tileElement)
        {
            int tileGID = atoi(tileElement->Attribute("gid"));
            int subRectToUse = tileGID - firstTileID;//Work out the subrect ID to 'chop up' the tilesheet image.
            if (subRectToUse >= 0)//we only need to (and only can) create a sprite/tile if there is one to display
            {
            	TileRecord tileRecord;
                sf::Sprite sprite;//sprite for the tile

                sprite.setTexture(tilesetImage);
                sprite.setTextureRect(subRects[subRectToUse]);
                sprite.setPosition(x * tileWidth, y * tileHeight);

                sprite.setColor(sf::Color(255, 255, 255, layer.opacity));//Set opacity of the tile.

                tileRecord.sprite = sprite;
                tileRecord.isSolid = tilePropMap[tileGID - 1];

                //add tile to layer
                layer.tiles.push_back(tileRecord);
            }

            tileElement = tileElement->NextSiblingElement("tile");

            //increment x, y
            x++;
            if (x >= width)//if x has "hit" the end (right) of the map, reset it to the start (left)
            {
                x = 0;
                y++;
                if (y >= height)
                {
                    y = 0;
                }
            }
        }

        layers.push_back(layer);

        layerElement = layerElement->NextSiblingElement("layer");
    }

    //Objects
    TiXmlElement *objectGroupElement;
    if (map->FirstChildElement("objectgroup") != NULL)//Check that there is atleast one object layer
    {
        objectGroupElement = map->FirstChildElement("objectgroup");
        while (objectGroupElement)//loop through object layers
        {
            TiXmlElement *objectElement;
            objectElement = objectGroupElement->FirstChildElement("object");
            while (objectElement)//loop through objects
            {
                std::string objectType;
                if (objectElement->Attribute("type") != NULL)
                {
                    objectType = objectElement->Attribute("type");
                }
                std::string objectName;
                if (objectElement->Attribute("name") != NULL)
                {
                    objectName = objectElement->Attribute("name");
                }
                int x = atoi(objectElement->Attribute("x"));
                int y = atoi(objectElement->Attribute("y"));
                int width = atoi(objectElement->Attribute("width"));
                int height = atoi(objectElement->Attribute("height"));

                Object object;
                object.name = objectName;
                object.type = objectType;

                sf::Rect <int> objectRect;
                objectRect.top = y;
                objectRect.left = x;
                objectRect.height = height;
                objectRect.width = width;

                if (objectType == "solid")
                {
                    solidObjects.push_back(objectRect);
                }

                object.rect = objectRect;

                TiXmlElement *properties;
                properties = objectElement->FirstChildElement("properties");
                if (properties != NULL)
                {
                    TiXmlElement *prop;
                    prop = properties->FirstChildElement("property");
                    if (prop != NULL)
                    {
                        while(prop)
                        {
                            std::string propertyName = prop->Attribute("name");
                            std::string propertyValue = prop->Attribute("value");

                            object.properties[propertyName] = propertyValue;

                            prop = prop->NextSiblingElement("property");
                        }
                    }
                }

                objects.push_back(object);

                objectElement = objectElement->NextSiblingElement("object");
            }
            objectGroupElement = objectGroupElement->NextSiblingElement("objectgroup");
        }
    }
    else
    {
        std::cout << "No object layers found..." << std::endl;
    }

    return true;
}

Object Level::GetObject(std::string name)
{
	Object obj;

    for ( unsigned int i = 0; i < objects.size(); i++)
    {
        if (objects[i].name == name)
        {
            obj = objects[i];
        }
    }

    return obj;
}

void Level::SetDrawingBounds(sf::Rect<float> bounds)
{
    drawingBounds = bounds;

    //Adjust the rect so that tiles are drawn just off screen, so you don't see them disappearing.
	//Explanation: when drawing a rectangle, it will be drawn from the top left and subtracting the bounds
	//using -= will expand the bounds. 
    drawingBounds.top -= tileHeight;
    drawingBounds.left -= tileWidth;
}

void Level::Draw(sf::RenderWindow *window)
{
    for (unsigned int layer = 0; layer < layers.size(); layer++)
    {
        for (unsigned int tile = 0; tile < layers[layer].tiles.size(); tile++)
        {
        	sf::Vector2f position;
        	position = layers[layer].tiles[tile].sprite.getPosition();

            if (drawingBounds.contains(position.x, position.y))
            {
                window->draw(layers[layer].tiles[tile].sprite);
            }
        }
    }
}

void Level::SetEntityList(std::vector <EntityRecord> entityList)
{
	this->entityList = entityList;
}

std::vector <EntityRecord>* Level::GetEntityList()
{
	return &this->entityList;
}

//Returns true if the given tile is solid.
bool Level::IsSolidTile(float x, float y)
{
	bool isSolid = false;

	//calculate tile coordinate from x, y
	unsigned int tile_x = (unsigned int)(x / this->tileWidth);
	unsigned int tile_y = (unsigned int)(y / this->tileHeight);

	//calculate index from tile coordinate.
	unsigned int index = (unsigned int)((tile_y * this->width) + tile_x);

	if ( index < this->layers[0].tiles.size() )
	{
		isSolid = this->layers[0].tiles[index].isSolid;
	}
	else
	{
		//Log Coordinate out of bounds
	}

	return isSolid;
}

