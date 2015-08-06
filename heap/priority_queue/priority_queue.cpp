/*++++++++++++++++++++++++++++++++++++++++++++++
*                 说明
*     使用STL的优先队列实现最大堆 topK
*     时间复杂度O(N*logN)
*          
*     @date  2015/08/05
*
*
+++++++++++++++++++++++++++++++++++++++++++++++*/
#include <iostream>
#include<queue>

using std::cin;
using std::cout;
using std::endl;

#define HEAP_SIZE  2   ///堆的大小

int main()
{
	/*
	///最小堆
	std::priority_queue<int,vector<int>,greater<int> > q;
	const int size = 2;
	int num[]={2,3,4,6,1,2};
	int len = sizeof(num)/sizeof(int);
	int i =0;
	while(i<len)
	{
		if(q.size()<size)
		{
			q.push(num[i]);
			i++;
		}
		else
		{
			if(num[i]>q.top())
			{
				q.pop();
				q.push(num[i]);
				i++;
			}
			else
				i++;
		}

	}
	*/
	int num[] = {5,-6,1,3,4,9,0,-1,-2};
    /// 优先队列
	std::priority_queue<int> q;
	/// 数组大小
	int len = sizeof(num)/(sizeof(int));
	for(int i =0; i<len; ++i)
	{
		if(q.size() < HEAP_SIZE)
			q.push(num[i]);
		else
		{
			///cout<<q.top()<<endl;
			if(num[i]<q.top())
			{
				q.pop();
				q.push(num[i]);
				i++;
			}
			else
				i++;
		}
	}
	return 0;
	


}
