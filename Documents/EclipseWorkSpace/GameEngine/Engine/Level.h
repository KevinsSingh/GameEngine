#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>
#include <map>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

//Object class. Everything is kept public in case you want to get a different type to the supported ones.
//Also you will be able to modify things. For example doors/changing walls etc (Just give the door a static type and a unique name)
//Kept in same files as level just for convenience. (only have to add two files to your project)
class Object{
    public:
        int GetPropertyInt(std::string name);
        float GetPropertyFloat(std::string name);
        std::string GetPropertyString(std::string name);
        std::string name;
        std::string type;
        sf::Rect <int> rect;
        std::map <std::string, std::string> properties;//All properties of the object. Values are stored as strings and mapped by strings(names provided in editor).
};

struct EntityRecord
{
	sf::Vector2f position;
	int objectID;
};

struct TileRecord
{
	sf::Sprite sprite;
	bool isSolid;
};

struct Layer{
    int opacity;
    std::vector <TileRecord> tiles;
};

class Level
{
    public:
        Level();
        virtual ~Level();
        //Loads the map. Returns false if it fails.
        bool LoadFromFile(std::string filename);
        //Returns the first object found with the given name. This is why we need unique names :)
        Object GetObject(std::string name);
        //Returns the list of entities that need to be loaded and updated by the Object manager.
        std::vector <EntityRecord>* GetEntityList();
        //Sets the EntityList containing all Entities that need to be loaded by the Objecto Manager.
        void SetEntityList(std::vector <EntityRecord> entityList);
        //Returns true if the given tile is solid.
        bool IsSolidTile(float x, float y);
        //Moves the map. Although I would recommend using a view instead in most cases.
        void Move(int xStep, int yStep);
        //Set the area to draw. This rect is usually provided directly from the view you are using.
        void SetDrawingBounds(sf::Rect<float> bounds);
        //Draws the map to the provided window.
        void Draw(sf::RenderWindow * window);

    private:
        //Width(tiles), height(tiles), tile width(pixels), tile height(pixels) of the map.
        int width, height, tileWidth, tileHeight;
        //Used to offset the tile number.
        int firstTileID;
        //Used to clip anything off screen.
        sf::Rect <float> drawingBounds;
        //The tileset image.
        sf::Texture tilesetImage;
        //This stores all the solid areas (objects with type 'solid'). This gets checked by the IsSolid function.
        std::vector <sf::Rect <int> > solidObjects;
        //This stores all objects (including 'solid' types)
        std::vector <Object> objects;
        //This stores each layer of sprites/tiles so they can be drawn in order.
        std::vector <Layer> layers;
        //This stores the entities that should be loaded by the Object manager
        std::vector <EntityRecord> entityList;
};

#endif // LEVEL_H
