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
/// 思路:  如果二叉树为空，结点个数为0
///        如果二叉树不为空，二叉树结点个数 = 左子树结点个数 + 右子树结点个数 + 1
int GetNodeNum(TreeNode* root)
{
	if(root == NULL)
		return 0;
	return GetNodeNum(root->left) + GetNodeNum(root->right) + 1;
}

/// 求二叉树的深度
/// 递归解法：如果二叉树为空，二叉树的深度为0
///           如果二叉树不空，二叉树的深度 = max(左子树深度，右子树深度)+1
int GetDepth(TreeNode* root)
{
	if(root == NULL) /// 递归出口
		return 0;
	int depthLeft = GetDepth(root->left);
	int depthRight = GetDepth(root->right);
	return (depthLeft > depthRight)?(depthLeft + 1):(depthRight + 1);
}

/// 前序遍历
/// 递归：如果二叉树为空，空操作
///       如果二叉树不为空，访问根结点，前序遍历左子树，前序遍历右子树
void PreOrderTraverse(TreeNode* root)
{
	if(root == NULL)
		return ;
	/// Visit(root);
	PreOrderTraverse(root->left); 
	PreOrderTraverse(root->right);
}

/// 中序遍历
void InOrderTraverse(TreeNode* root)
{
	if(root == NULL)
		return;
	InOrderTraverse(root->left);
	/// Visit(root);
	InOrderTraverse(root->right);
}

/// 后序遍历
void PostOrderTraverse(TreeNode* root)
{
	if(root == NULL)
		return;
	PostOrderTraverse(root->left);
	PostOrderTraverse(root->right);
	/// Visit(root);
}

/// 层序遍历
/// 思路：相当于广度优先搜索，使用队列实现，队列初始化，将根结点压入队列，当队列不为空，进行如下操作：
///       弹出一个结点，访问，若左子结点或右子结点不为空，将其压入队列
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

/// 将二叉树查找树变为有序的双向链表
/// 要求不能创建新结点，只调整指针
/// 递归：如果二叉查找树为空，不需要转换，对应双向链表的第一个结点为NULL，最后一个结点为NULL
///       如果二叉查找树不为空
///       如果左子树为空，对应双向有序链表的第一个节点是根节点，左边不需要其他操作；
///       如果左子树不为空，转换左子树，二叉查找树对应双向有序链表的第一个节点就是左子树转换后双向有序链表的第一个节点，同时将根节点和左子树转换后的双向有序链 表的最后一个节点连接；
///       如果右子树为空，对应双向有序链表的最后一个节点是根节点，右边不需要其他操作；
///       如果右子树不为空，对应双向有序链表的最后一个节点就是右子树转换后双向有序链表的最后一个节点，同时将根节点和右子树转换后的双向有序链表的第一个节点连 接。
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

/// 求二叉树第K层的结点个数
/// 递归：如果二叉树为空或者k<1返回0
///       如果二叉树不为空且k == 1.返回1
///       如果二叉树不为空且k>1,返回左子树中k-1层的结点个数与右子树k-1层结点个数之和
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

/// 求二叉树中叶子结点的个数
/// 递归：如果二叉树为空，返回0
///       如果二叉树不为空且左右子树为空，返回1
///       如果二叉树不为空，且左右子树不同时为空，返回左子树中叶子结点的个数加上右子树中叶子结点个数
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
/// 判断两个二叉树结构是否相同
/// 不考虑数据内容，结构相同以为着对应左子树和右子树都结构相同
/// 递归：如果二叉树都为空，返回真
/// 如果两颗二叉树一颗为空，另一颗不为空，返回false
/// 如果两颗二叉树都不为空，如果对应的左子树和右子树都同构返回true，其他返回false
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

/// 判断二叉树是否为平衡二叉树
/// 递归解法：如果二叉树为空，返回真
///           如果二叉树不为空，如果左子树和右子树都是AVL树，且左子树和右子树高度相差不大于1，返回真，其他返回假
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

/// 求二叉树的镜像
/// 递归解法：如果二叉树为空，返回空
///           如果二叉树不为空，求左子树和右子树的镜像，然后交换左子树和右子树
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
/// 求二叉树中两个结点的最低公共祖先结点
/// 递归解法：如果两个结点分别在根结点的左子树和右子树，则返回根结点
///           如果两个结点都在左子树，则递归处理左子树，如果两个结点都在右子树，则递归处理右子树
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

/// 求二叉树中的结点的最大距离
///  递归解法：如果二叉树为空，返回0，同时记录左子树和右子树的深度，都为0
///            如果二叉树不为空，最大距离么实在左子树中的最大距离，要么是在右子树中的最大距离，要么是左子树结点中到根节点的最大
///            距离+右子树结点中到根节点的最大距离，同时记录左子树和右子树结点中到根结点的最大距离

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

/// 由前序遍历序列和中序遍历序列重建二叉树
/// 分析：二叉树前序遍历序列中，第一个元素总是树的根结点的值，中序遍历序列中，左子树的结点的值位于根节点的值的左边，右子树
///       的结点的值位于根节点的值的右边
/// 递归解答：如果前序序列为空或中序序列为空或结点个数小于等于0，返回NULL
///           创建根节点，前序遍历的第一个数据就是根节点的值，在中序遍历序列中找到根节点的位置，可分别得知左子树和右子树
///           的前序和中序遍历序列，重建左右子树
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
	int* pInOrderLeft = pInOrder;
	root->left = ReBuildBinaryTree(pPreOrderLeft,pInOrderLeft,nodeNumLeft);

	int nodeNumRight = nodeNum - nodeNumLeft - 1;
	int* pPreOrderRight = pPreOrder + 1 + nodeNumLeft;
	int* pInOrderRight = pInOrder + nodeNumLeft + 1;
	root->right = ReBuildBinaryTree(pPreOrderRight,pInOrderRight,nodeNumRight);

	return root;
}

/// 判断二叉树是不是完全二叉树
/// 若设二叉树的深度为h，除了第h层外，其他各层(1~h-1)的结点树都达到最大个数，第h层所有结点都连续集中在最左边，这就是完全二叉树
/// 按层序遍历二叉树，当遇到一个结点的左子树为空，则该结点的右子树必须为空，且后边遍历的结点左右子树都必须为空，否则不是
/// 完全二叉树
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






