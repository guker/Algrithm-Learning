///+++++++++++++++++++++++++++++++++++++++++++++++
///
///            Graph Traverse
///
///         @copyright hqwsky 2015
///
///++++++++++++++++++++++++++++++++++++++++++++++++

#include <iostream>
#include<queue>
#include <stack>
#include<stdio.h>


#define MAX  100
using namespace std;

typedef struct
{
	int edges[MAX][MAX]; /// 邻接矩阵
	int n;               /// 顶点树
	int e;               /// 边数
}MGraph;


bool visited[MAX];       /// 访问标记
/// 邻接矩阵 无向图
void creatMGraph(MGraph& G)
{
	int i, j;
	int s,t;             /// 存储顶点编号
	int v;               /// 存储边的权值
	for(i = 0; i<G.n;++i)/// 初始化邻接矩阵
	{
		for(j = 0; j < G.n;j++)
		{
			G.edges[i][j] = 0;
		}
		visited[i] = false;
	}
	for(i = 0; i < G.e; i++)
	{
		scanf("%d %d %d",&s,&t,&v);
		G.edges[s][t] = G.edges[t][s] = v; /// 无向图的邻接矩阵为对称
	}
}
/// 深度优先遍历 
/// 递归实现
void DFS(MGraph G, int v)
{
	int i;
	printf("%d ",v);        /// v为顶点编号
	visited[v] = true;
	for(i = 0;i < G.n; ++i) /// 访问与V相邻的未被访问过的顶点 
	{
		if(G.edges[v][i] != 0 && visited[i] == false)
			DFS(G,i);
	}
}
/// 深度优先遍历
/// 栈实现
void dfs(MGraph G,int v)
{
	stack<int> s;
	printf("%d ",v);       /// 访问初始顶点
	visited[v] = true;
	s.push(v);             /// 入栈
	while(!s.empty())
	{
		int i,j;
		i = s.top();       /// 取栈顶顶点
		for(j = 0;j < G.n; j++)   /// 访问与顶点i相邻的顶点
		{
			if(G.edges[i][j] != 0 && visited[j] == false)
			{
				printf("%d ",j);
				visited[j] = true;
				s.push(j);        /// 访问完入栈
				break;            /// 找到一个相邻未访问的顶点，则将顶点i出栈
			}
		}
		if(j == G.n)              ///如果与i相邻的顶点都被访问过，则将顶点i出栈
			s.pop();
	}
	printf("\n");
}

/// 广度优先遍历
/// 队列实现
void BFS(MGraph G, int v)
{
	queue<int> q;
	printf("%d ",v);
	visited[v] = true;
	q.push(v);
	while(!q.empty())
	{
		int i,j;
		i = q.front(); /// 取队首顶点
		q.pop();
		for(j = 0; j < G.n; j++)
		{
			if(G.edges[i][j] != 0 && visited[j] == false)
			{
				printf("%d ",j);
				visited[j] = true;
				q.push(j);
			}
		}
	}
	printf("\n");
}



int main()
{
	int n,e;
	while(scanf("%d %d",&n,&e) == 2 && n > 0 )
	{
		MGraph G;
		G.n = n;
		G.e = e;
		creatMGraph(G);
		printf("深度优先遍历序列：\n");
		DFS(G,0);
		printf("\n");
		
		printf("深度优先遍历序列：\n");
		for(int i = 0; i < G.n; i++)
			visited[i] = false;
		dfs(G,0);
		
		printf("广度优先遍历序列：\n");
		for(int i = 0; i < G.n; i++)
			visited[i] = false;
		BFS(G,0);
	}

	return true;
}




