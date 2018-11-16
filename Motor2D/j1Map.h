#ifndef __j1MAP_H__
#define __j1MAP_H__

#include "PugiXml/src/pugixml.hpp"
#include "p2List.h"
#include "p2Point.h"
//#include "p2PQueue.h"
//#include "p2Queue.h"
#include "p2SString.h"
#include "p2DynArray.h"
#include "j1Module.h"
#include "j1Textures.h"
#include "j1Render.h"
//#include "j1EntityManager.h"

#define COST_MAP 100

enum OBJECT_TYPE
{
	WALL,
	GROUND,
	BLOCKER
};
// TODO 1: Create a struct for the map layer
// ----------------------------------------------------
struct MapLayer
{
	inline uint Get(int x, int y) const;
	inline uint PathLimit(int x, int y) const;
	p2SString			name;
	uint				width;
	uint				height;
	uint*				data = nullptr;
	uint				size = 0;


	~MapLayer() { delete[] data; }
};

// TODO 6: Short function to get the value of x,y
struct ImageLayer
{
	p2SString			name;
	uint				width;
	uint				height;
	float				speed;
	int					offset_x;
	int					offset_y;
	SDL_Texture* texture;
};

/*inline uint Get(int x, int y) const;*/

struct ObjectLayer
{
	p2SString			name;
	uint*				width = nullptr;
	uint*				height = nullptr;
	float*				x = nullptr;
	float*				y = nullptr;
	uint*				id = nullptr;
	SDL_Rect*			rect = nullptr;
	float*				acceleration_x = nullptr;
	float*				acceleration_y = nullptr;
	float*				velocity_x = nullptr;
	float*				velocity_y = nullptr;
	float*				jump_height = nullptr;
	float*				double_jump_height = nullptr;
	float*				gravity = nullptr;
	OBJECT_TYPE*		type = nullptr;
	

};


// ----------------------------------------------------
struct TileSet
{
	// TODO 7: Create a method that receives a tile id and returns it's Rectfind the Rect associated with a specific tile id
	SDL_Rect GetTileRect(int id) const;

	p2SString			name;
	int					firstgid;
	int					margin;
	int					spacing;
	int					tile_width;
	int					tile_height;
	SDL_Texture*		texture = nullptr;
	int					tex_width;
	int					tex_height;
	int					num_tiles_width;
	int					num_tiles_height;
	int					offset_x;
	int					offset_y;
};

enum MapTypes
{
	MAPTYPE_UNKNOWN = 0,
	MAPTYPE_ORTHOGONAL,
	MAPTYPE_ISOMETRIC,
	MAPTYPE_STAGGERED
};
// ----------------------------------------------------
struct MapData
{
	int					width;
	int					height;
	int					tile_width;
	int					tile_height;
	SDL_Color			background_color;
	MapTypes			type;
	p2List<TileSet*>	tilesets;
	// TODO 2: Add a list/array of layers to the map!
	p2List<MapLayer*>	maplayers;
	p2List<ImageLayer*>	imagelayers;
	p2List<ObjectLayer*> objectlayers;
};

// ----------------------------------------------------
class j1Map : public j1Module
{
public:

	j1Map();

	// Destructor
	virtual ~j1Map();

	// Called before render is available
	bool Awake(pugi::xml_node& conf);

	// Called each loop iteration
	void Draw();

	// Called before quitting
	bool CleanUp();

	// Load new map
	bool Load(const char* path);

	// TODO 8: Create a method that translates x,y coordinates from map positions to world positions
	iPoint MapToWorld(int x, int y) const;
	iPoint WorldToMap(int x, int y) const;

	int MovementCost(int x, int y) const;

private:

	bool LoadMap();
	bool LoadTilesetDetails(pugi::xml_node& tileset_node, TileSet* set);
	bool LoadTilesetImage(pugi::xml_node& tileset_node, TileSet* set);
	// TODO 3: Create a method that loads a single laye
	bool LoadLayer(pugi::xml_node& node, MapLayer* layer);
	bool LoadImageLayer(pugi::xml_node& node, ImageLayer* layer);
	bool LoadObjectLayer(pugi::xml_node& node, ObjectLayer* layer);
	//bool LoadEnemyLayer(pugi::xml_node& node, EnemyLayer* layer);

public:

	MapData				data;
	SDL_Rect			collider;
	uint				cost_so_far[COST_MAP][COST_MAP];

private:

	pugi::xml_document	map_file;
	p2SString			folder;
	bool				map_loaded = false;

	/// BFS
//	p2PQueue<iPoint>	frontier;
	p2List<iPoint>		visited;
	p2List<iPoint>		breadcrumbs;
	p2DynArray<iPoint>	path;
	SDL_Texture*		tile_x = nullptr;
};

#endif // __j1MAP_H__