#include <iostream>
#include <stack>

struct ListNode
{
	int val;
	ListNode* next;
	ListNode(int x):val(x),next(NULL){}
};


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

}

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

ListNode* GetfirstNodeInCircle(ListNode* phead)
{
	if(phead == NULL || phead->next == NULL)
		return NULL;

	ListNode* pFast = phead;
	ListNode* pSlow = phead;

	while(pFast != NULL && pFast->next != NULL)
	{
		pSlow = pSlow->next;
		pFast = pFast->next->next;
		if(pSlow == pFast)
			break;
	}
	if(pFast == NULL || pFast->next == NULL)
		return NULL;
}



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
