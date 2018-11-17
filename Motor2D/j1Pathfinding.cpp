#include "j1Pathfinding.h"

j1Pathfinding::j1Pathfinding()
{
}


j1Pathfinding::~j1Pathfinding()
{
}

bool j1Pathfinding::Start()
{
	//pathfinder = App->tex->Load("assets/breadcrumbs.png");

	return true;
}

bool j1Pathfinding::CleanUp()
{
	LOG("Freeing pathfinding library");

	frontier.Clear();
	breadcrumbs.clear();
	visited.clear();
	last_path.Clear();

	return true;
}

bool j1Pathfinding::IsWalkable(const iPoint& pos) const
{
	//iPoint auxpos = App->map->MapToWorld(App->map->data.width, App->map->data.height);

	if (pos.x >= 0 && pos.x <App->map->data.width && pos.y >= 0 && pos.y <App->map->data.height)
	{
		return true;
	}
	else
	{
		return false;
	}

}

const p2DynArray<iPoint>* j1Pathfinding::GetLastPath() const
{
	return &last_path;
}


void j1Pathfinding::DrawPath(p2DynArray<iPoint>& trackingpath)
{
	for (uint i = 0; i < trackingpath.Count(); ++i)
	{
		iPoint pos = App->map->MapToWorld(trackingpath[i].x, trackingpath[i].y);
		App->render->Blit(pathfinder, pos.x, pos.y, 1, 1, false);
	}
}

void j1Pathfinding::BackTrackingGround(const iPoint& start, p2DynArray<iPoint>& path)
{
	path.Clear();

	//iPoint goal = App->map->WorldToMap(start.x, start.y);
	iPoint goal = { start.x, start.y };
	iPoint curr = goal;

	path.PushBack(curr);

	while (curr != breadcrumbs.start->data && visited.find(goal) != -1)
	{
		curr = breadcrumbs[visited.find(curr)];
		path.PushBack(curr);
	}

	path.Flip();
}

void j1Pathfinding::BackTrackingAir(const iPoint& start, p2DynArray<iPoint>& path)
{
	path.Clear();

	//iPoint goal = App->map->WorldToMap(start.x, start.y);
	iPoint goal = { start.x, start.y };
	iPoint curr = goal;

	path.PushBack(curr);

	while (curr != breadcrumbs.start->data && visited.find(goal) != -1)
	{
		curr = breadcrumbs[visited.find(curr)];
		path.PushBack(curr);
	}

	path.Flip();
}

int j1Pathfinding::CreatePath(const iPoint& origin, const iPoint& destination)
{
	frontier.Clear();
	breadcrumbs.clear();
	visited.clear();

	int ret = 0;

	if (App->map->MovementCost(destination.x, destination.y) >= 0)
	{
		ret = -1;
	}

	if (ret != -1)
	{
		iPoint curr;

		iPoint goal = App->map->WorldToMap(destination.x, destination.y);

		frontier.Push(App->map->WorldToMap(origin.x, origin.y), 0);

		while (frontier.Count() != 0)
		{
			if (curr == goal)
			{
				break;
			}
			if (frontier.Pop(curr))
			{
				iPoint neighbors[8];
				neighbors[0].create(curr.x + 1, curr.y + 0);
				neighbors[1].create(curr.x + 0, curr.y + 1);
				neighbors[2].create(curr.x - 1, curr.y + 0);
				neighbors[3].create(curr.x + 0, curr.y - 1);
				neighbors[4].create(curr.x + 1, curr.y + 1);
				neighbors[5].create(curr.x - 1, curr.y - 1);
				neighbors[6].create(curr.x - 1, curr.y + 1);
				neighbors[7].create(curr.x + 1, curr.y - 1);


				for (uint i = 0; i < 8; ++i)
				{
					//uint point_dist = sqrt(pow((goal.x - neighbors[i].x), 2) + pow((goal.y - neighbors[i].y), 2));
					uint point_dist = neighbors[i].DistanceTo(goal);

					if (App->map->MovementCost(neighbors[i].x, neighbors[i].y) > 0)
					{
						if (visited.find(neighbors[i]) == -1 && breadcrumbs.find(neighbors[i]) == -1)
						{
							cost_so_far[neighbors[i].x][neighbors[i].y] = point_dist;
							frontier.Push(neighbors[i], point_dist);
							visited.add(neighbors[i]);
							breadcrumbs.add(curr);
						}
					}
					/*if (App->map->MovementCost(neighbors[i].x, neighbors[i].y) >= 0 && App->entity_manager->bat)
					{
						if (visited.find(neighbors[i]) == -1 && breadcrumbs.find(neighbors[i]) == -1)
						{
							cost_so_far[neighbors[i].x][neighbors[i].y] = point_dist;
							frontier.Push(neighbors[i], point_dist);
							visited.add(neighbors[i]);
							breadcrumbs.add(curr);
						}
					}*/
				}
			}
		}
	}
	return ret;
}
