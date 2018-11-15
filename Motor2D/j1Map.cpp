#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Map.h"
#include "j1Collisions.h"
//#include "j1EntityManager.h"
#include <math.h>

using namespace pugi;

j1Map::j1Map() : j1Module(), map_loaded(false)
{
	name.create("map");
}

// Destructor
j1Map::~j1Map()
{}

// Called before render is available
bool j1Map::Awake(pugi::xml_node& config)
{
	LOG("Loading Map Parser");
	bool ret = true;

	folder.create(config.child("folder").child_value());


	return ret;
}

void j1Map::Draw()
{
	if (map_loaded == false)
		return;

	// TODO 5: Prepare the loop to draw all tilesets + Blit
	for (uint image_num = 0; image_num < data.imagelayers.count(); ++image_num)
	{
		App->render->Blit(data.imagelayers[image_num]->texture, data.imagelayers[image_num]->offset_x, data.imagelayers[image_num]->offset_y, 1, 1, false, NULL, data.imagelayers[image_num]->speed);
	}


	for (uint layer_num = 0; layer_num < data.maplayers.count(); ++layer_num)
	{
		for (int i = 0; i < data.width; ++i)
		{
			for (int j = 0; j < data.height; ++j)
			{
				uint id = data.maplayers[layer_num]->data[data.maplayers[layer_num]->Get(i, j)];
				if (id != 0)
				{
					SDL_Rect tile_rect = data.tilesets[layer_num]->GetTileRect(id);
					int x = MapToWorld(i, j).x;
					int y = MapToWorld(i, j).y;
					App->render->Blit(data.tilesets[layer_num]->texture, x, y, 1, 1, false, &tile_rect);
				}
			}
		}
	}



	// TODO 9: Complete the draw function

}


iPoint j1Map::MapToWorld(int x, int y) const
{
	iPoint ret;

	ret.x = x * data.tile_width;
	ret.y = y * data.tile_height;

	return ret;
}

iPoint j1Map::WorldToMap(int x, int y) const
{
	iPoint ret;

	ret.x = (x / data.tile_width);
	ret.y = (y / data.tile_height);

	return ret;
}

SDL_Rect TileSet::GetTileRect(int id) const
{
	int relative_id = id - firstgid;
	SDL_Rect rect;
	rect.w = tile_width;
	rect.h = tile_height;
	rect.x = margin + ((rect.w + spacing) * (relative_id % num_tiles_width));
	rect.y = margin + ((rect.h + spacing) * (relative_id / num_tiles_width));
	return rect;
}

int j1Map::MovementCost(int x, int y) const
{
	int ret = -1;

	if (x >= 0 && x < data.width && y >= 0 && y < data.height)
	{
		int id = data.maplayers.start->data->PathLimit(x, y);

		if (id == 0)
			ret = 3;
		else
			ret = 0;
	}

	return ret;
}

// Called before quitting
bool j1Map::CleanUp()
{
	LOG("Unloading map");

	// Remove all tilesets
	p2List_item<TileSet*>* item;
	item = data.tilesets.start;

	while (item != NULL)
	{
		RELEASE(item->data);
		item = item->next;
	}
	data.tilesets.clear();

	// TODO 2: clean up all layer data
	// Remove all layers
	p2List_item<MapLayer*>* item2;
	item2 = data.maplayers.start;

	while (item2 != NULL)
	{
		RELEASE(item2->data);
		item2 = item2->next;
	}
	data.maplayers.clear();


	//Clean Up image layers

	p2List_item<ImageLayer*>* item3;
	item3 = data.imagelayers.start;

	while (item3 != NULL)
	{
		RELEASE(item3->data);
		item3 = item3->next;
	}
	data.imagelayers.clear();

	//Clean Up Object layers
	p2List_item<ObjectLayer*>* item4;
	item4 = data.objectlayers.start;

	while (item4 != NULL)
	{
		RELEASE(item4->data);
		item4 = item4->next;
	}
	data.objectlayers.clear();

	// Clean up the pugui tree
	map_file.reset();

	return true;
}

// Load new map
bool j1Map::Load(const char* file_name)
{
	bool ret = true;
	p2SString tmp("%s%s", folder.GetString(), file_name);

	pugi::xml_parse_result result = map_file.load_file(tmp.GetString());

	if (result == NULL)
	{
		LOG("Could not load map xml file %s. pugi error: %s", file_name, result.description());
		ret = false;
	}

	// Load general info ----------------------------------------------
	if (ret == true)
	{
		ret = LoadMap();
	}

	// Load all tilesets info ----------------------------------------------
	pugi::xml_node tileset;
	for (tileset = map_file.child("map").child("tileset"); tileset && ret; tileset = tileset.next_sibling("tileset"))
	{
		TileSet* set = new TileSet();

		if (ret == true)
		{
			ret = LoadTilesetDetails(tileset, set);
		}

		if (ret == true)
		{
			ret = LoadTilesetImage(tileset, set);
		}

		data.tilesets.add(set);
	}

	// TODO 4: Iterate all layers and load each of them
	// Load layer info ----------------------------------------------
	xml_node layers;
	for (layers = map_file.child("map").child("layer"); layers && ret; layers = layers.next_sibling("layer"))
	{
		MapLayer* set = new MapLayer();

		if (ret == true)
		{
			ret = LoadLayer(layers, set);
		}
		data.maplayers.add(set);
	}

	// Load Image Layer info ----------------------------------------

	xml_node images;
	for (images = map_file.child("map").child("imagelayer"); images && ret; images = images.next_sibling("imagelayer"))
	{
		ImageLayer* setImage = new ImageLayer();

		if (ret == true)
		{
			ret = LoadImageLayer(images, setImage);
		}

		data.imagelayers.add(setImage);
	}

	//Load Object Layer info ----------------------------------------

	xml_node objects;
	for (objects = map_file.child("map").child("objectgroup"); objects && ret; objects = objects.next_sibling("objectgroup"))
	{
		ObjectLayer* setObject = new ObjectLayer();

		if (ret == true)
		{
			ret = LoadObjectLayer(objects, setObject);
		}

		data.objectlayers.add(setObject);
	}


	if (ret == true)
	{
		LOG("Successfully parsed map XML file: %s", file_name);
		LOG("width: %d height: %d", data.width, data.height);
		LOG("tile_width: %d tile_height: %d", data.tile_width, data.tile_height);

		p2List_item<TileSet*>* item = data.tilesets.start;
		while (item != NULL)
		{
			TileSet* s = item->data;
			LOG("Tileset ----");
			LOG("name: %s firstgid: %d", s->name.GetString(), s->firstgid);
			LOG("tile width: %d tile height: %d", s->tile_width, s->tile_height);
			LOG("spacing: %d margin: %d", s->spacing, s->margin);
			item = item->next;
		}

		// TODO 4: Add info here about your loaded layers
		// Adapt this vcode with your own variables

		p2List_item<MapLayer*>* item_layer = data.maplayers.start;
		while (item_layer != NULL)
		{
			MapLayer* l = item_layer->data;
			LOG("Layer ----");
			LOG("name: %s", l->name.GetString());
			LOG("tile width: %d tile height: %d", l->width, l->height);
			item_layer = item_layer->next;
		}

		p2List_item<ImageLayer*>* image_layer = data.imagelayers.start;
		while (image_layer != NULL)
		{
			ImageLayer* l = image_layer->data;
			LOG("Image ----");
			LOG("name: %s", l->name.GetString());
			LOG("tile width: %d tile height: %d", l->width, l->height);
			LOG("speed: %f", l->speed);
			LOG("offset_x: %d, offset_y: %d", l->offset_x, l->offset_y);
			image_layer = image_layer->next;

		}
		int i = 0;
		p2List_item<ObjectLayer*>* object_layer = data.objectlayers.start;
		while (object_layer != NULL)
		{
			ObjectLayer* l = object_layer->data;
			for (l->id[i]; l->id[i] != NULL; ++i) {
				LOG("Object ----");
				LOG("ID: %d", l->id[i]);
				LOG("height: %d, width: %d", l->height[i], l->width[i]);
				LOG("x: %d, y: %d", l->x[i], l->y[i]);
			}

			object_layer = object_layer->next;


		}
	}

	
	for (uint layer_num = 0; layer_num < data.maplayers.count(); ++layer_num)
	{
		for (int i = 0; i < data.width; ++i)
		{
			for (int j = 0; j < data.height; ++j)
			{
				uint id = data.maplayers[layer_num]->data[data.maplayers[layer_num]->Get(i, j)];
				if (id != 0)
				{
					SDL_Rect tile_rect = data.tilesets[layer_num]->GetTileRect(id);
					int x = MapToWorld(i, j).x;
					int y = MapToWorld(i, j).y;
					App->render->Blit(data.tilesets[layer_num]->texture, x, y, 1, 1, false, &tile_rect);
				}
			}
		}
	}
	map_loaded = ret;

	return ret;
}

// Load map general properties
bool j1Map::LoadMap()
{
	bool ret = true;
	pugi::xml_node map = map_file.child("map");

	if (map == NULL)
	{
		LOG("Error parsing map xml file: Cannot find 'map' tag.");
		ret = false;
	}
	else
	{
		data.width = map.attribute("width").as_int();
		data.height = map.attribute("height").as_int();
		data.tile_width = map.attribute("tilewidth").as_int();
		data.tile_height = map.attribute("tileheight").as_int();
		p2SString bg_color(map.attribute("backgroundcolor").as_string());

		data.background_color.r = 0;
		data.background_color.g = 0;
		data.background_color.b = 0;
		data.background_color.a = 0;

		if (bg_color.Length() > 0)
		{
			p2SString red, green, blue;
			bg_color.SubString(1, 2, red);
			bg_color.SubString(3, 4, green);
			bg_color.SubString(5, 6, blue);

			int v = 0;

			sscanf_s(red.GetString(), "%x", &v);
			if (v >= 0 && v <= 255) data.background_color.r = v;

			sscanf_s(green.GetString(), "%x", &v);
			if (v >= 0 && v <= 255) data.background_color.g = v;

			sscanf_s(blue.GetString(), "%x", &v);
			if (v >= 0 && v <= 255) data.background_color.b = v;
		}

		p2SString orientation(map.attribute("orientation").as_string());

		if (orientation == "orthogonal")
		{
			data.type = MAPTYPE_ORTHOGONAL;
		}
		else if (orientation == "isometric")
		{
			data.type = MAPTYPE_ISOMETRIC;
		}
		else if (orientation == "staggered")
		{
			data.type = MAPTYPE_STAGGERED;
		}
		else
		{
			data.type = MAPTYPE_UNKNOWN;
		}
	}

	return ret;
}

bool j1Map::LoadTilesetDetails(pugi::xml_node& tileset_node, TileSet* set)
{
	bool ret = true;
	set->name.create(tileset_node.attribute("name").as_string());
	set->firstgid = tileset_node.attribute("firstgid").as_int();
	set->tile_width = tileset_node.attribute("tilewidth").as_int();
	set->tile_height = tileset_node.attribute("tileheight").as_int();
	set->margin = tileset_node.attribute("margin").as_int();
	set->spacing = tileset_node.attribute("spacing").as_int();
	pugi::xml_node offset = tileset_node.child("tileoffset");

	if (offset != NULL)
	{
		set->offset_x = offset.attribute("x").as_int();
		set->offset_y = offset.attribute("y").as_int();
	}
	else
	{
		set->offset_x = 0;
		set->offset_y = 0;
	}

	return ret;
}

bool j1Map::LoadTilesetImage(pugi::xml_node& tileset_node, TileSet* set)
{
	bool ret = true;
	pugi::xml_node image = tileset_node.child("image");

	if (image == NULL)
	{
		LOG("Error parsing tileset xml file: Cannot find 'image' tag.");
		ret = false;
	}
	else
	{
		set->texture = App->tex->Load(PATH(folder.GetString(), image.attribute("source").as_string()));
		int w, h;
		SDL_QueryTexture(set->texture, NULL, NULL, &w, &h);
		set->tex_width = image.attribute("width").as_int();

		if (set->tex_width <= 0)
		{
			set->tex_width = w;
		}

		set->tex_height = image.attribute("height").as_int();

		if (set->tex_height <= 0)
		{
			set->tex_height = h;
		}

		set->num_tiles_width = set->tex_width / set->tile_width;
		set->num_tiles_height = set->tex_height / set->tile_height;
	}

	return ret;
}

// TODO 3: Create the definition for a function that loads a single layer
bool j1Map::LoadLayer(pugi::xml_node& node, MapLayer* layer)
{
	bool ret = true;
	pugi::xml_node aux = node.child("data").child("tile");

	layer->name = node.attribute("name").as_string();
	layer->width = node.attribute("width").as_uint(0);//return 0 in case "width" doesn't exist
	layer->height = node.attribute("height").as_uint(0);//return 0 in case "height" doesn't exist
	layer->size = layer->width*layer->height;

	layer->data = new uint[layer->size];//allocates the array with a certain size
	memset(layer->data, 0, sizeof(uint)*(layer->size));

	for (uint i = 0; i < layer->size; ++i)
	{
		layer->data[i] = aux.attribute("gid").as_uint();
		aux = aux.next_sibling();
	}
	return ret;
}

inline uint MapLayer::Get(int x, int y) const
{
	return x + y * width;
}

inline uint MapLayer::PathLimit(int x, int y) const
{
	return data[(y*width) + x];
}

bool j1Map::LoadImageLayer(pugi::xml_node& node, ImageLayer* layer)
{
	bool ret = true;
	layer->name = node.attribute("name").as_string();

	layer->name = node.attribute("name").as_string();
	layer->width = node.child("image").attribute("width").as_uint();
	layer->height = node.child("image").attribute("height").as_uint();
	layer->speed = node.child("properties").child("property").attribute("value").as_float();
	layer->offset_x = node.attribute("offsetx").as_int();
	layer->offset_y = node.attribute("offsety").as_int();
	//layer->texture = App->tex->Load(node.child("image").attribute("source").as_string());
	layer->texture = App->tex->Load(PATH(folder.GetString(), node.child("image").attribute("source").as_string()));

	return ret;
}

bool j1Map::LoadObjectLayer(pugi::xml_node& node, ObjectLayer* layer)
{
	pugi::xml_node aux;
	aux = node.child("object");
	int i = 0;
	layer->width = new uint[200];
	layer->height = new uint[200];
	layer->x = new float[200];
	layer->y = new float[200];
	layer->id = new uint[200];
	layer->rect = new SDL_Rect[200];
	layer->type = new OBJECT_TYPE[200];

	layer->name = node.attribute("name").as_string();

	while (aux != NULL)
	{
		if (aux.attribute("id").as_int() != NULL)
		{
			layer->id[i] = aux.attribute("id").as_int();
		}
		if (aux.attribute("x").as_int() != NULL)
		{
			layer->x[i] = aux.attribute("x").as_int();
		}
		if (aux.attribute("y").as_int() != NULL)
		{
			layer->y[i] = aux.attribute("y").as_int();
		}
		if (aux.attribute("width").as_int() != NULL)
		{
			layer->width[i] = aux.attribute("width").as_int();
		}
		if (aux.attribute("height").as_int() != NULL)
		{
			layer->height[i] = aux.attribute("height").as_int();
		}

		layer->rect[i].h = layer->height[i];
		layer->rect[i].w = layer->width[i];
		layer->rect[i].x = layer->x[i];
		layer->rect[i].y = layer->y[i];

		p2SString object_type(aux.child("properties").child("property").attribute("value").as_string());

		if (object_type == "WALL")
		{
			collider = { (int)layer->x[i], (int)layer->y[i], (int)layer->width[i], (int)layer->height[i] };
			App->collisions->AddCollider(collider, COLLIDER_WALL);
			layer->type[i] = WALL;
						
		}
		if (object_type == "GROUND")
		{
			collider = { (int)layer->x[i], (int)layer->y[i], (int)layer->width[i], (int)layer->height[i] };
			App->collisions->AddCollider(collider, COLLIDER_GROUND);
			layer->type[i] = GROUND;
		}
		/*p2SString type(aux.child("properties").child("property").attribute("value").as_string());
		if (type == "WHITE WOLF")
		{
			layer->entity_type[i] = WOLF;
		}
		if (type == "BLACK BAT")
		{
			layer->entity_type[i] = BAT;
		}
		if (type == "PLAYER")
		{
			layer->entity_type[i] = PLAYER;
		}
		if (type == NULL)
		{
			layer->entity_type[i] = NO_TYPE;
		}*/
		aux = aux.next_sibling("object");
		++i;
	}




	return true;
}


/*bool j1Map::LoadEnemyLayer(pugi::xml_node& node, EnemyLayer* layer)
{
pugi::xml_node aux;
aux = node.first_child();
int i = 0;
layer->width = new uint[200];
layer->height = new uint[200];
layer->x = new int[200];
layer->y = new int[200];
layer->id = new uint[200];
layer->rect = new SDL_Rect[200];
layer->name = node.attribute("name").as_string();
while (aux != aux.last_child())
{
layer->id[i] = aux.attribute("id").as_uint();
layer->x[i] = aux.attribute("x").as_int();
layer->y[i] = aux.attribute("y").as_int();
layer->width[i] = aux.attribute("width").as_uint();
layer->height[i] = aux.attribute("height").as_uint();
layer->rect[i].h = layer->height[i];
layer->rect[i].w = layer->width[i];
layer->rect[i].x = layer->x[i];
layer->rect[i].y = layer->y[i];
aux = aux.next_sibling("object");
++i;
}
return true;
}*/