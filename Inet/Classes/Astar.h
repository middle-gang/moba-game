#include <vector>
#include <list> 
#include<iostream>
#include"cocos2d.h"
const int kCost1 = 10; //直移一格消耗
const int kCost2 = 14; //斜移一格消耗 
struct PointCk{	
	int x, y; 
	int F, G, H; 	
	PointCk *parent; 
	PointCk(int _x, int _y) :x(_x), y(_y), F(0), G(0), H(0), parent(NULL)
	{	}
}; 

class Astar{
public:	
	void InitAstar();	
	int maze[32][32];
	std::list<PointCk *> GetPath(PointCk &startPoint, PointCk &endPoint, bool isIgnoreCorner);
private:	
	PointCk *findPath(PointCk &startPoint, PointCk &endPoint, bool isIgnoreCorner);
	std::vector<PointCk *> getSurroundPoints(const PointCk *point, bool isIgnoreCorner) const;
	bool isCanreach(const PointCk *point, const PointCk *target, bool isIgnoreCorner) const; //判断某点是否可以用于下一步判断	
	PointCk *isInList(const std::list<PointCk *> &list, const PointCk *point) const; //判断开启/关闭列表中是否包含某点	
	PointCk *getLeastFpoint();
	int calcG(PointCk *temp_start, PointCk *point);
	int calcH(PointCk *point, PointCk *end);
	int calcF(PointCk *point);private:	
	std::list<PointCk *> openList;  //开启列表	
	std::list<PointCk *> closeList; //关闭列表
};
