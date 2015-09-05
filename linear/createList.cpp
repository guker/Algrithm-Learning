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

ListNode* createList1(int a[],int len)
{
	if(len == 0)
		return NULL;
	/// 因为有放到链表首位的操作，需要一个dummy的头结点
	ListNode dummy(-1);
	ListNode* tail = &dummy;

	for(int i = 0; i < len; i++)
	{
		ListNode* tmp = new ListNode(a[i]);
		tail->next = tmp;
		tail = tail->next;
	}

	return dummy.next;
}

int main()
{
	int a[] = {2,3,5};
	ListNode* p1 = createList(a,sizeof(a)/sizeof(int));
	
	return 0;
}


