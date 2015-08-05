/*++++++++++++++++++++++++++++++++++++++++++++++
*                 ˵��
*     ʹ��STL�����ȶ���ʵ������ topK
*     ʱ�临�Ӷ�O(N*logN)
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

#define HEAP_SIZE  2   ///�ѵĴ�С

int main()
{
	int num[] = {5,-6,1,3,4,9,0,-1,-2};
    /// ���ȶ���
	std::priority_queue<int> q;
	/// �����С
	int len = sizeof(num)/(sizeof(int));
	for(int i =0; i<len; ++i)
	{
		if(q.size() <= HEAP_SIZE)
			q.push(num[i]);
		else
		{
			///cout<<q.top()<<endl;
			q.pop();
			q.push(num[i]);
		}
	}
	return 0;
	


}
