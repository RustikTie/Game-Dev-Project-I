#include "j1Pathfinding.h"



j1Pathfinding::j1Pathfinding()
{
}


j1Pathfinding::~j1Pathfinding()
{
}

bool j1Pathfinding::Start()
{
	pathfinder = App->tex->Load("assets/breadcrumbs.png");

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

	if (pos.x >= 0 && pos.x <= (int)width && pos.y >= 0 && pos.y <= (int)height)
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
		App->render->Blit(pathfinder, pos.x, pos.y, 0, 0, false);
	}
}

void j1Pathfinding::BackTracking(const iPoint& start, p2DynArray<iPoint>& path)
{
	path.Clear();
	iPoint goal = App->map->WorldToMap(start.x, start.y);
	iPoint curr = goal;
	p2List_item<iPoint>* item = breadcrumbs.end;

	path.PushBack(curr);

	while (item != breadcrumbs.start && visited.find(curr) != -1)
	{
		curr = breadcrumbs[visited.find(curr)];
		path.PushBack(curr);
		item = item->prev;
	}
	
	path.Flip();
}

int j1Pathfinding::CreatePath(const iPoint& origin, const iPoint& destination)
{
	frontier.Clear();
	breadcrumbs.clear();
	visited.clear();
	last_path.Clear();

	int ret = 0;

	if (!(IsWalkable(origin)) || !(IsWalkable(destination)))
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
				iPoint neighbors[4];
				neighbors[0].create(curr.x + 1, curr.y + 0);
				neighbors[1].create(curr.x + 0, curr.y + 1);
				neighbors[2].create(curr.x - 1, curr.y + 0);
				neighbors[3].create(curr.x + 0, curr.y - 1);


				for (uint i = 0; i < 4; ++i)
				{
					//uint Distance = sqrt(pow((goal.x-neighbors[i].x),2)+pow((goal.y- neighbors[i].y),2));
					uint Distance = neighbors[i].DistanceTo(goal);

					if (App->map->MovementCost(neighbors[i].x, neighbors[i].y) >= 0)
					{
						if (breadcrumbs.find(neighbors[i]) == -1 && visited.find(neighbors[i]) == -1)
						{
							App->map->cost_so_far[neighbors[i].x][neighbors[i].y] = Distance;
							frontier.Push(neighbors[i], Distance);							//El nou cost es la distancia
							visited.add(neighbors[i]);
							breadcrumbs.add(curr);
						}
					}
				}
			}
		}
	}
	return ret;
}

