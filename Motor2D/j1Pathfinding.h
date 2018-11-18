#ifndef __ModulePathfinding_H__
#define __ModulePathfinding_H__

#include "j1Module.h"
#include "p2DynArray.h"
#include "p2List.h"
#include "p2PQueue.h"
#include "p2Queue.h"
#include "j1App.h"
#include "j1Map.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Map.h"
#include "p2Log.h"

#define COST_MAP 1000

class j1Pathfinding : public j1Module
{
public:
	j1Pathfinding();
	~j1Pathfinding();

	bool Start();

	// Called before quitting
	bool CleanUp();

	// Main function to request a path from A to B
	int CreatePath(const iPoint& origin, const iPoint& destination);

	// To request all tiles involved in the last generated path
	const p2DynArray<iPoint>* GetLastPath() const;

	//Draws path on screen
	void DrawPath(p2DynArray<iPoint>& path);

	//Backtracking function
	void BackTracking(const iPoint& start, p2DynArray<iPoint>& path);

	// Utility: returns true is the tile is walkable
	bool IsWalkable(const iPoint& pos) const;

	SDL_Texture*		pathfinder = nullptr;

private:

	uchar * map;

	p2PQueue<iPoint>	frontier;
	p2List<iPoint>		visited;
	p2List<iPoint>		breadcrumbs;
	p2DynArray<iPoint>	last_path;

	uint				cost_so_far[COST_MAP][COST_MAP];


};
#endif
