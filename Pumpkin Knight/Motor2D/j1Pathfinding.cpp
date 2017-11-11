#include "j1Pathfinding.h"



j1Pathfinding::j1Pathfinding()
{
}


j1Pathfinding::~j1Pathfinding()
{
}

bool j1Pathfinding::CleanUp()
{
	LOG("Freeing pathfinding library");

	last_path.Clear();
	RELEASE_ARRAY(map);
	return true;
}

void j1Pathfinding::SetMap(uint width, uint height, uchar* data)
{
	this->width = width;
	this->height = height;

	RELEASE_ARRAY(map);
	map = new uchar[width*height];
	memcpy(map, data, width*height);
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

void j1Pathfinding::DrawPath()
{

}

int j1Pathfinding::CreatePath(const iPoint& origin, const iPoint& destination)
{
	int ret;

	if (!(IsWalkable(origin) || IsWalkable(destination)))
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
			if (goal == curr)
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
					uint point_dist = sqrt(pow((goal.x - neighbors[i].x), 2) + pow((goal.y - neighbors[i].y), 2));

					if (App->map->MovementCost(neighbors[i].x, neighbors[i].y) >= 0)
					{
						if (visited.find(neighbors[i]) == -1)
						{
							App->map->cost_so_far[neighbors[i].x][neighbors[i].y] = point_dist;
							frontier.Push(neighbors[i], point_dist);
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

