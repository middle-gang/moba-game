#include <vector>
#include <list> 
#include<iostream>
#include"cocos2d.h"
const int kCost1 = 10; //ֱ��һ������
const int kCost2 = 14; //б��һ������ 
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
	bool isCanreach(const PointCk *point, const PointCk *target, bool isIgnoreCorner) const; //�ж�ĳ���Ƿ����������һ���ж�	
	PointCk *isInList(const std::list<PointCk *> &list, const PointCk *point) const; //�жϿ���/�ر��б����Ƿ����ĳ��	
	PointCk *getLeastFpoint();
	int calcG(PointCk *temp_start, PointCk *point);
	int calcH(PointCk *point, PointCk *end);
	int calcF(PointCk *point);private:	
	std::list<PointCk *> openList;  //�����б�	
	std::list<PointCk *> closeList; //�ر��б�
};
