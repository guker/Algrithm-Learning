/*
*    create List
*
*    @date  2015/8/8
*
*/
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

struct ListNode
{
	int val;
	struct ListNode* next;
	ListNode(int x):val(x),next(NULL){}
};

ListNode* createList(int a[],int len)
{
	ListNode* head = NULL;
	ListNode* p;
	for(int i = 0;i < len; i++)
	{
		if(head == NULL)
		{
			head = new ListNode(a[i]);
			p = head;
		}
		else
		{
			p->next = new ListNode(a[i]);
			p = p->next;
		}
	}
	
	return head;
}

int main()
{
	int a[] = {2,3,5};
	ListNode* p1 = createList(a,sizeof(a)/sizeof(int));
	
	return 0;
}


