#include <iostream>
#include "astar.h"


/*��ͼ���� 0��ʾ����ͨ����1��ʾ�ϰ�*/

#if MSVC08
char maps[10][10] =
{
	{ 0, 1, 0, 0, 0, 1, 0, 0, 0, 0 },
	{ 0, 0, 0, 1, 0, 1, 0, 1, 0, 1 },
	{ 1, 1, 1, 1, 0, 1, 0, 1, 0, 1 },
	{ 0, 0, 0, 1, 0, 0, 0, 1, 0, 1 },
	{ 0, 1, 0, 1, 1, 1, 1, 1, 0, 1 },
	{ 0, 1, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 0, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 0, 0, 0, 0, 1, 0, 0, 0, 1, 0 },
	{ 1, 1, 0, 0, 1, 0, 1, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 1, 0, 1, 0 },
};

bool query( const AStar::Vec2 & pos)
{
	return maps[pos.y][pos.x] == 0;
}
#endif

int main(int argc, char *argv[])
{
#if  MSVC10  
	char maps[10][10] =
	{
		{ 0, 1, 0, 0, 0, 1, 0, 0, 0, 0 },
		{ 0, 0, 0, 1, 0, 1, 0, 1, 0, 1 },
		{ 1, 1, 1, 1, 0, 1, 0, 1, 0, 1 },
		{ 0, 0, 0, 1, 0, 0, 0, 1, 0, 1 },
		{ 0, 1, 0, 1, 1, 1, 1, 1, 0, 1 },
		{ 0, 1, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 0, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 0, 0, 0, 0, 1, 0, 0, 0, 1, 0 },
		{ 1, 1, 0, 0, 1, 0, 1, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 1, 0, 1, 0 },
	};
#endif

	AStar::Param param;
	param.width = 10;
	param.height = 10;
	param.corner = true;
	param.start = AStar::Vec2(0, 0);
	param.end = AStar::Vec2(9,9);

#if MSVC08
	param.can_reach =(AStar::QueryFunction)query;
#else
	param.can_reach = [&](const AStar::Vec2 &pos)->bool
	{
		return maps[pos.y][pos.x] == 0;
	};
#endif	

	AStar as;

	std::vector<AStar::Vec2> path = as.find(param);
	std::cout << (path.empty() ? "·��δ�ҵ���" : "·�����ҵ���") << std::endl;
	std::vector<AStar::Vec2>::iterator iter=path.begin();
	int i=0;
	for(;iter!=path.end();iter++)
	{
		std::cout<<'('<<iter->x<<','<<iter->y<<')'<<"-->";
	}

	return 0;
}