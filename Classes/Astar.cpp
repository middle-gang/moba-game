
#include <math.h>

#include "Astar.h"



void Astar::InitAstar()
{
}



int Astar::calcG(PointCk *temp_start, PointCk *point)
{
	int extraG = (abs(point->x - temp_start->x) + abs(point->y - temp_start->y)) == 1 ? kCost1 : kCost2;
	int parentG = point->parent == NULL ? 0 : point->parent->G; //如果是初始节点，则其父节点是空
	return parentG + extraG;
}



int Astar::calcH(PointCk *point, PointCk *end)
{
	return sqrt((double)(end->x - point->x)*(double)(end->x - point->x) + (double)(end->y - point->y)*(double)(end->y - point->y))*kCost1;
}



int Astar::calcF(PointCk *point)
{
	return point->G + point->H;
}



PointCk *Astar::getLeastFpoint()
{
	if (!openList.empty())
	{
		auto resPoint = openList.front();
		for (auto &point : openList) {
			if (point->F < resPoint->F) resPoint = point;
		}
		return resPoint;
	}
	return NULL;
}



PointCk *Astar::findPath(PointCk &startPoint, PointCk &endPoint, bool isIgnoreCorner)
{
	openList.push_back(new PointCk(startPoint.x, startPoint.y));
	while (!openList.empty())
	{
		auto curPoint = getLeastFpoint(); 
		openList.remove(curPoint); 
		closeList.push_back(curPoint); 
		auto surroundPoints = getSurroundPoints(curPoint, isIgnoreCorner);
		for (auto &target : surroundPoints)
		{
			if (!isInList(openList, target)){
				target->parent = curPoint;
				target->G = calcG(curPoint, target);
				target->H = calcH(target, &endPoint);
				target->F = calcF(target);
				openList.push_back(target);
			}
			else
			{
				int tempG = calcG(curPoint, target);
				if (tempG < target->G){
					target->parent = curPoint;
					target->G = tempG;
					target->F = calcF(target);
				}
			}
			PointCk *resPoint = isInList(openList, &endPoint);
			if (resPoint)  return resPoint; 
		}
	}
	return NULL;
}



std::list<PointCk *> Astar::GetPath(PointCk &startPoint, PointCk &endPoint, bool isIgnoreCorner)
{
	PointCk *result = findPath(startPoint, endPoint, isIgnoreCorner);
	std::list<PointCk *> path;
	while (result)
	{
		path.push_front(result);
		result = result->parent;
	}
	openList.clear();
	closeList.clear();
	return path;
}



PointCk *Astar::isInList(const std::list<PointCk *> &list, const PointCk *point) const
{
	for (auto p : list) {
		if (p->x == point->x&&p->y == point->y) return p;
	}
	return NULL;
}



bool Astar::isCanreach(const PointCk *point, const PointCk *target, bool isIgnoreCorner) const
{
	if (target->x<0 || target->x>31|| target->y<0 || target->y>31
		|| maze[target->x][target->y] == 1|| target->x == point->x&&target->y == point->y
		|| isInList(closeList, target)) 	return false;
	else
	{
		if (abs(point->x - target->x) + abs(point->y - target->y) == 1) return true;
		else
		{
			if (maze[point->x][target->y] == 0 && maze[target->x][point->y] == 0) return true;
			else {
				return isIgnoreCorner;
			}
		}
	}
}



std::vector<PointCk *> Astar::getSurroundPoints(const PointCk *point, bool isIgnoreCorner) const
{
	std::vector<PointCk *> surroundPoints;
	for (int x = point->x - 1; x <= point->x + 1; x++) {
		for (int y = point->y - 1; y <= point->y + 1; y++) {
			if (isCanreach(point, new PointCk(x, y), isIgnoreCorner)) {
				surroundPoints.push_back(new PointCk(x, y));
			}
		}
	}
	return surroundPoints;

}
