#include<iostream>
#include<queue>
#include <algorithm> 

struct TreeNode
{
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x):val(x),left(NULL),right(NULL){}
};

/// 求二叉树中的结点个数
///思路:  如果二叉树为空，结点个数为0
///      如果二叉树不为空，二叉树结点个数 = 左子树结点个数 + 右子树结点个数 + 1
int GetNodeNum(TreeNode* root)
{
	if(root == NULL)
		return 0;
	return GetNodeNum(root->left) + GetNodeNum(root->right) + 1;
}


int GetDepth(TreeNode* root)
{
	if(root == NULL)
		return 0;
	int depthLeft = GetDepth(root->left);
	int depthRight = GetDepth(root->right);
	return (depthLeft > depthRight)?(depthLeft + 1):(depthRight + 1);
}


void PreOrderTraverse(TreeNode* root)
{
	if(root == NULL)
		return ;
	/// Visit(root);
	PreOrderTraverse(root->left); 
	PreOrderTraverse(root->right);
}


void InOrderTraverse(TreeNode* root)
{
	if(root == NULL)
		return;
	InOrderTraverse(root->left);
	/// Visit(root);
	InOrderTraverse(root->right);
}


void PostOrderTraverse(TreeNode* root)
{
	if(root == NULL)
		return;
	PostOrderTraverse(root->left);
	PostOrderTraverse(root->right);
	/// Visit(root);
}


void LevelTraverse(TreeNode* root)
{
	if(root == NULL)
		return;
	std::queue<TreeNode* > q;
	q.push(root);
	while(!q.empty())
	{
		TreeNode* pNode = q.front();
		q.pop();
		/// Visit(pNode);
		if(pNode->left != NULL)
			q.push(pNode->left);
		if(pNode->right != NULL)
			q.push(pNode->right);
	}
	return;
}


void Convert(TreeNode* root, TreeNode* &pFirstNode,TreeNode* &pLastNode)
{
	TreeNode* pFirstLeft, *pLastLeft, *pFirstRight, *pLastRight;
	if(root == NULL)
	{
		pFirstNode = NULL;
		pLastNode = NULL;
		return;
	}

	if(root->left == NULL)
	{
		pFirstNode = root;
	}
	else
	{
		Convert(root->left,pFirstLeft,pLastLeft);

		pFirstNode = pFirstLeft;

		root->left = pLastLeft;
		pLastLeft->right = root;
	}

	if(root->right == NULL)
	{
		pLastNode = root;
	}
	else
	{
		Convert(root->right,pFirstRight,pLastRight);
		
		pLastNode = pLastRight;
		root->right = pFirstRight;
		pFirstRight->left = root;
	}

	return;

}


int GetNodeNumKthLevel(TreeNode* root, int k)
{
	if(root == NULL || k < 1 )
		return 0;
	if(k = 1)
		return 1;
	int numLeft = GetNodeNumKthLevel(root->left,k-1);
	int numRight = GetNodeNumKthLevel(root->right,k-1);

	return (numLeft + numRight);
}

int GetLeafNodeNum(TreeNode* root)
{
	if(root == NULL)
		return 0;
	if(root->left == NULL && root->right == NULL)
		return 1;
	int numLeft = GetLeafNodeNum(root->left);
	int numRight = GetLeafNodeNum(root->right);
	return (numLeft +numRight);
}

bool StructureCmp(TreeNode* root1, TreeNode* root2)
{
	if(root1 == NULL && root2 == NULL)
		return true;
	else if(root1 == NULL || root2 == NULL)
		return false;
	bool resultLeft = StructureCmp(root1->left,root2->left);
	bool resultRight = StructureCmp(root1->right,root2->right);

	return (resultLeft && resultRight);
}


bool IsAVL(TreeNode* root, int& height)
{
	if(root == NULL)
	{
		height = 0;
		return true;
	}
	int heightLeft;
	bool resultLeft = IsAVL(root->left,heightLeft);

	int heightRight;
	bool resultRight = IsAVL(root->right,heightRight);
	if(resultLeft && resultRight && abs(heightLeft - heightRight) <= 1)
	{
		height = std::max(heightLeft,heightRight) + 1;
		return true;
	}
	else
	{
		height = std::max(heightLeft,heightRight) + 1;
		return false;
	}
}

TreeNode* Mirror(TreeNode* root)
{
	if(root == NULL)
		return NULL;
	TreeNode* pLeft = Mirror(root->left);
	TreeNode* pRight = Mirror(root->right);

	root->left = pRight;
	root->right = pLeft;
	return root;
}

bool FindNode(TreeNode* root, TreeNode* pNode)
{
	if(root == NULL || pNode == NULL)
		return false;
	if(root == pNode)
		return true;
	bool found = FindNode(root->left,pNode);
	if(!found)
		found = FindNode(root->right,pNode);
	return found;
}

TreeNode* GetLastCommonParent(TreeNode* root,
							  TreeNode* pNode1,
							  TreeNode* pNode2)
{
	if(FindNode(root->left,pNode1))
	{
		if(FindNode(root->right,pNode2))
			return root;
		else
			return GetLastCommonParent(root->left,pNode1,pNode2);
	}
	else
	{
		if(FindNode(root->left,pNode2))
			return root;
		else
			return GetLastCommonParent(root->right,pNode1,pNode2);
	}
}



int GetMaxDistance(TreeNode* root,int& maxLeft,int& maxRight)
{
	if(root == NULL)
	{
		maxLeft = 0;
		maxRight = 0;
		return 0;
	}

	int maxLL,maxLR,maxRL,maxRR;
	int maxDistLeft,maxDistRight;
	if(root->left != NULL)
	{
		maxDistLeft = GetMaxDistance(root->left,maxLL,maxLR);
		maxLeft = std::max(maxLL,maxLR) + 1;
	}
	else
	{
		maxDistLeft = 0;
		maxLeft = 0;
	}
	if(root->right != NULL)
	{
		maxDistRight = GetMaxDistance(root->right,maxRL,maxRR);
		maxRight= std::max(maxRL,maxRR) + 1;
	}
	else
	{
		maxDistRight = 0;
		maxRight = 0;
	}
	return std::max(std::max(maxDistLeft,maxDistRight),maxLeft+maxRight);
}


TreeNode* ReBuildBinaryTree(int* pPreOrder, int* pInOrder, int nodeNum)
{
	if(pPreOrder == NULL || pInOrder == NULL || nodeNum <= 0)
		return NULL;
	TreeNode* root = new TreeNode(0);

	root->val = pPreOrder[0];
     
	int rootPositionInOrder = -1;
	for(int i = 0;i < nodeNum; i++)
	{
		if(pInOrder[i] == root->val)
		{
			rootPositionInOrder = i;
			break;
		}
	}

	if(rootPositionInOrder == -1)
	{
		throw std::exception("Invalid input");
	}

	int nodeNumLeft = rootPositionInOrder;
	int* pPreOrderLeft = pPreOrder + 1;
	int* pInOrderLeft = pInOrder + 1;
	int* pInOrderLeft = pInOrder;
	root->left = ReBuildBinaryTree(pPreOrderLeft,pInOrderLeft,nodeNumLeft);

	int nodeNumRight = nodeNum - nodeNumLeft - 1;
	int* pPreOrderRight = pPreOrder + 1 + nodeNumLeft;
	int* pInOrderRight = pInOrder + nodeNumLeft + 1;
	root->right = ReBuildBinaryTree(pPreOrderRight,pInOrderRight,nodeNumRight);

	return root;
}


bool IsCompleteBinaryTree(TreeNode* root)
{
	if(root == NULL)
		return false;
	std::queue<TreeNode* > q;
	q.push(root);

	bool mustHaveNoChild = false;
	bool result = true;
	while(!q.empty())
	{
		TreeNode* pNode = q.front();
		q.pop();
		if(mustHaveNoChild)
		{
			if(pNode->left != NULL || pNode->right != NULL)
			{
				result = false;
				break;
			}

		}
		else
		{
			if(pNode->left != NULL && pNode->right != NULL)
			{
				q.push(pNode->left);
				q.push(pNode->right);
			}
			else if(pNode->left != NULL && pNode->right == NULL)
			{
				mustHaveNoChild = true;
				q.push(pNode->left);
			}
			else if(pNode->left == NULL && pNode->right != NULL)
			{
				result = false;
				break;
			}
			else
				mustHaveNoChild = true;
		}
	}

	return result;
}


int main()
{
	/// test code
	return true;
}






