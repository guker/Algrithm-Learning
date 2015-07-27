#include <iostream>
#include <stack>

struct ListNode
{
	int val;
	ListNode* next;
	ListNode(int x):val(x),next(NULL){}
};

/// 求单链表中结点的个数
unsigned int GetListLength(ListNode* phead)
{
	if(phead)
		return 0;
	unsigned int nLength = 0;
	ListNode* pCurrent = phead;
	while(pCurrent != NULL)
	{
		nLength++;
		pCurrent = pCurrent->next;
	}

	return nLength;
}

/// 单链表反转
/// 从头到尾遍历原链表，每遍历一个结点，将其摘下放在新链表的最前端
ListNode* ReverseList(ListNode* phead)
{
	if(phead == NULL || phead->next == NULL)
		return phead;

	ListNode* pReversedhead = NULL;
	ListNode* pCurrent = phead;
	while(pCurrent != NULL)
	{
		ListNode* pTmp = pCurrent;
		pCurrent = pCurrent->next;
		pTmp->next = pReversedhead;
		pReversedhead = pTmp;
	}

	return pReversedhead;
}

///  查找单链表中的倒数第K个结点
/// 思路：使用两个指针，先让前面的指针走到正向第K个结点，这样前后两个指针的距离差是k-1，之后前后两个指针一起向前走，前面的
/// 前面的指针走到最后一个结点的时候，后面的指针所指的结点就是倒数第k个结点
ListNode* RGetKthNode(ListNode* phead, unsigned int k)
{
	if(k == 0 || phead == NULL)
		return NULL;

	ListNode* pAhead = phead;
	ListNode* pBehind = phead;
    while(k > 1 && pAhead != NULL)
	{
		pAhead = pAhead->next;
		k--;
	}

	if(k > 1 || pAhead == NULL)
		return NULL;
	while(pAhead->next != NULL)
	{
		pBehind = pBehind->next;
		pAhead = pAhead->next;
	}

	return pBehind;
}

/// 查找单链表的中间结点
/// 思路：设置两个指针，同时向前走，慢指针每次走一步，快指针每次走两步，快指针走到最后一个结点时，慢指针所指的结点就是中间结点
ListNode* GetMiddleNode(ListNode* phead)
{
	if(phead == NULL || phead->next == NULL)
		return NULL;
	
	ListNode* pAhead = phead;
	ListNode* pBehind = phead;

	while(pAhead->next != NULL)
	{
		pBehind = pBehind->next;
		pAhead = pAhead->next;
		if(pAhead->next != NULL)
			pAhead = pAhead->next;
	}

	return pBehind;
}

/// 逆序打印单链表
/// 思路：颠倒顺序问题，一般使用栈实现,要么自己使用栈，要么让系统使用栈也就是递归
void RPrintList(ListNode* phead)
{
	std::stack<ListNode*> s;
	ListNode* pCurrent = phead;
	while(pCurrent != NULL)
	{
		s.push(pCurrent);
		pCurrent = pCurrent->next;
	}

	while(!s.empty())
	{
		pCurrent = s.top();
		std::cout<<pCurrent->val<<"\t";
		s.pop();
	}
}
// 逆序打印单链表
/// 思路：递归
void RPrintList_1(ListNode* phead)
{
	if(phead == NULL)
		return;
	else
	{
		RPrintList_1(phead->next);
		std::cout<<phead->val <<"\t";
	}
}

/// 合并两个有序链表为有序链表
/// 思路：注意链表为空的情况，与其中一个为空的情况
ListNode* MergeSortedList(ListNode* phead1,ListNode* phead2)
{
	if(phead1 == NULL)
		return phead2;
	if(phead2 == NULL)
		return phead1;

	ListNode* pHeadMerged = NULL;
	if(phead1->val < phead2->val)
	{
		pHeadMerged = phead1;
		pHeadMerged->next = NULL;
		phead1 = phead1->next;
	}
	else
	{
		pHeadMerged = phead2;
		pHeadMerged->next = NULL;
		phead2 = phead1->next;
	}

	ListNode* pTmp = pHeadMerged;
	while(phead1 != NULL && phead2 != NULL)
	{
		if(phead1->val < phead2->val)
		{
			pTmp->next = phead1;
			phead1 = phead1->next ;
			pTmp = pTmp->next;
			pTmp->next = NULL;
		}
		else
		{
			pTmp->next = phead2;
			phead2 = phead2->next;
			pTmp = pTmp->next;
			pTmp->next = NULL;

		}
	}

	if(phead1 != NULL)
		pTmp->next = phead1;
	else if(phead2 != NULL)
		pTmp->next = phead2;
	return pHeadMerged;
}

/// 判断一个单链表是否有环
/// 设置两个指针，如果有环的话，用一个指针去遍历，是永远走不到头的，用两个指针遍历，一个指针一次走两步，一个指针一次走一步
/// 如果有环的话，两个指针肯定会相遇。
bool HasCircle(ListNode* phead)
{
	ListNode* pFast = phead;
	ListNode* pSlow = phead;
	while(pFast != NULL && pFast->next != NULL)
	{
		pSlow = pSlow->next;
		pFast = pFast->next;
		if(!pFast)
			pFast = pFast->next;

		if(pSlow == pFast)
			return true;
	}
	return false;



/// 判断两个单链表是否相交
/// 思路：如果两个链表相交于某个结点，那么在这个相交结点之后的所有的结点都是两个链表共有的，也就是说，如果两个链表相交
/// 那么最后一个结点肯定是相同的，所以先遍历第一个链表，记住最后一个结点，然后遍历第二个结点，到最后一个结点时和第一个链表
/// 的最后的一个结点作比较，如果相同则相交
bool IsIntersected(ListNode* phead1,ListNode* phead2)
{
	if(phead1 == NULL || phead2 == NULL)
		return false;
    ListNode* pTail1 = phead1;
	while(pTail1->next != NULL)
		pTail1 = pTail1->next;

	ListNode* pTail2 = phead2;
	while(pTail2->next != NULL)
		pTail2 = pTail2->next;

	return pTail1 = pTail2;
}

/// 求两个单链表相交的第一个结点
/// 思路：根据上题的方法先判断是否有交点，并分别计算每个链表的长度，len1，len2
/// 两个链表均从头结点开始，假设len1大于len2，那么先将第一个结点链表先遍历len1-len2个结点，此时两个链表当前结点到第一个
/// 结点的距离就相等，然后一起向后一起遍历，知道两两个的地址相同
ListNode* GetFirstCommNode(ListNode* phead1,ListNode* phead2)
{
	if(phead1 == NULL || phead2 == NULL)
		return NULL;
	int len1 = 1;
	ListNode* pTail1 = phead1;
	while(pTail1->next != NULL)
	{
		pTail1 = pTail1->next;
		len1++;
	}

	int len2 = 1;
	ListNode* pTail2 = phead2;
	while(pTail2->next != NULL)
	{
		pTail2 = pTail2->next;
		len2++;
	}

	if(pTail1 != pTail2)
		return NULL;

	ListNode* pNode1 = phead1;
	ListNode* pNode2 = phead2;
	if(len1 > len2)
	{
		int k = len1 - len2;
		while(k--)
			pNode1 = pNode1->next;
	}
	else
	{
		int k = len2 - len1;
		while(k--)
			pNode2 = pNode2->next;
	}

	while(pNode1 != pNode2)
	{
		pNode1 = pNode1->next;
		pNode2 = pNode2->next;
	}
	return pNode1;

}
/// 已知一个单链表中存在环，求进入环中的第一个结点
/// 思路：设置两个指针，慢指针，快指针，慢指针每次走一步，快指针每次走两步，直到相遇
/// 然后让慢指针从头遍历，再次相遇就是进入环的第一个结点
ListNode* detectCycle(ListNode* phead)
{
	ListNode* slow = phead;
	ListNode* fast = phead;
	do
	{
		if(!slow || !fast)
			return NULL;
		slow = slow->next;
		fast = fast->next;
		if(fast)
			fast = fast->next;
		else 
			return NULL;
	}while(slow != fast)
	
	slow = phead;
	while(slow != fast)
	{
		slow = slow->next;
		fast = fast->next;
	}
	return slow;
}
	


/// 给出一个单链表的头指针phead和一个结点指针pToBeDeleted，O(1)时间复杂度删除结点pToBeDeleted
/// 思路： 我们可以把该节点的下一个结点的数据复制到该结点，然后删除下一个结点即可。
void Delete(ListNode* phead,ListNode* pToBeDeleted)
{
	if(pToBeDeleted == NULL)
		return ;
	if(pToBeDeleted->next != NULL)
	{
		pToBeDeleted->val = pToBeDeleted->next->val;
		ListNode* temp = pToBeDeleted->next;
		pToBeDeleted->next = pToBeDeleted->next->next;
		delete temp;
	}
	else
	{
		if(phead == pToBeDeleted)
		{
			phead = NULL;
			delete pToBeDeleted;
		}
		else
		{
			ListNode* pNode = phead;
			while(pNode->next != pToBeDeleted)
				pNode = pNode->next;
			delete pToBeDeleted;
		}
	}
}


int main()
{

	return true;
}
