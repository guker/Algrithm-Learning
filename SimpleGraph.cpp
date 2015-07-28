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
	int edges[MAX][MAX];
	int n;
	int e;
}MGraph;


bool visited[MAX];

void creatMGraph(MGraph& G)
{
	int i, j;
	int s,t;
	int v;
	for(i = 0; i<G.n;++i)
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
		G.edges[s][t] = G.edges[t][s] = v;
	}
}

void DFS(MGraph G, int v)
{
	int i;
	printf("%d",v);
	visited[v] = true;
	for(i = 0;i < G.n; ++i)
	{
		if(G.edges[v][i] != 0 && visited[i] == false)
			DFS(G,i);
	}
}

void dfs(MGraph G,int v)
{
	stack<int> s;
	printf("%d ",v);
	visited[v] = true;
	s.push(v);
	while(!s.empty())
	{
		int i,j;
		i = s.top();
		for(j = 0;j < G.n; j++)
		{
			if(G.edges[i][j] != 0 && visited[j] == false)
			{
				printf("%d ",j);
				visited[j] = true;
				s.push(j);
				break;
			}
		}
		if(j == G.n)
			s.pop();
	}
}


void BFS(MGraph G, int v)
{
	queue<int> q;
	printf("%d",v);
	visited[v] = true;
	q.push(v);
	while(!q.empty())
	{
		int i,j;
		i = q.front();
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
		//DFS(G,0);
		//dfs(G,0);
		BFS(G,0);
	}

	return true;
}




