#include<iostream>
#include<queue>
#include<vector>
#include<stack>
#include <algorithm> 

struct TreeNode
{
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x):val(x),left(NULL),right(NULL){}
};

void preorderTraverse(TreeNode* , std::vector<int>& );

std::vector<int> preorderTraverse(TreeNode* root)
{
	std::vector<int> vals;
	preorderTraverse(root,vals);
}

void preorderTraverse(TreeNode* root,std::vector<int>& vals)
{
	if(root == NULL)
		return;
	vals.push_back(root->val);
	preorderTraverse(root->left,vals);
	preorderTraverse(root->right,vals);
}

std::vector<int> preorderTraverse(TreeNode* root)
{
	std::vector<int> vals;
	std::stack<TreeNode*> s;
	TreeNode* p = root;
	while(!s.empty() || p)
	{
		if(p == NULL)
		{
			while(!s.empty() && (p == s.top()->right || s.top()->right == NULL))
			{
				p = s.top();
				s.pop();
			}
			if(s.empty()) 
				break;
			p = s.top()->right;
		}
		else
		{
			vals.push_back(p->val);
			s.push(p);
			p = p->left;

		}
	}

	return vals;
}


std::vector<int> inorderTraversal(TreeNode *root)   
{  
    std::vector<int> vals;  
    inorderTraversal(root, vals);  
    return vals;  
}  
void inorderTraversal(TreeNode *root,std::vector<int> &vals)  
{  
    if(root == NULL) return;  
    inorderTraversal(root->left, vals);  
    vals.push_back(root->val);  
    inorderTraversal(root->right, vals); 
}


std::vector<int> inorderTraverse(TreeNode* root)
{
	std::vector<int> vals;
	std::stack<TreeNode*> s;
	TreeNode* p = root;
	while(!s.empty() || p)
	{
		while(p)
		{
			s.push(p);
			p = p->left;

		}
		p = s.top();
		s.pop();
		vals.push_back(p->val);
		p = p->right;
	}

	return vals;
}

std::vector<int> postorderTraversal(TreeNode* root)  
{  
    std::vector<int> vals;  
    postorderTraversal(root, vals);  
    return vals;  
}  
void postorderTraversal(TreeNode *root, std::vector<int> &vals)  
{  
    if(root == NULL)  
        return;  
    postorderTraversal(root->left, vals);  
    postorderTraversal(root->right, vals);  
    vals.push_back(root->val);  
} 

std::vector<int> postorderTraversal(TreeNode* root)  
{  
    std::vector<int> vals;  
    std::stack<TreeNode*> s;  
    TreeNode * pre = NULL;  
    TreeNode * p = root;  
    while(!s.empty() || p)  
    {  
        while(p)  
        {  
            s.push(p);  
            p = p->left;  
        }  
        pre = NULL;  
        while(!s.empty() && pre == s.top()->right)  
        {  
            pre = s.top();  
            vals.push_back(s.top()->val);  
            s.pop();  
        }  
        if(s.empty()) break;  
        p = s.top()->right;  
    }  
    return vals;  
}  

std::vector<int> levelOrderTraversal(TreeNode *root)   
{  
    std::vector<int> vals;  
    if(root == NULL)   
        return vals;  
    std::queue<TreeNode*> q;  
    q.push(root);  
    while(!q.empty())  
    {  
        TreeNode * p = q.front();  
        q.pop();  
        vals.push_back(p->val);  
        if(p->left)  
            q.push(p->left);  
        if(p->right)  
            q.push(p->right);  
    }  
}





std::vector<int> levelOrderTraversal(TreeNode *root)   
{  
    std::vector<int> vals;  
    int height = getTreeHeight(root);  
    for(int level = 1; level <= height; level++)  
        levelOrderTraversal(root, level, vals);  
    return vals;  
}  
int getTreeHeight(TreeNode * root)  
{  
    if(root == NULL) return 0;  
    int heightLeft = getTreeHeight(root->left);  
    int heightRight = getTreeHeight(root->right);  
    return std::max(heightLeft, heightRight)+1;  
}  
void levelOrderTraversal(TreeNode *root, int level, std::vector<int> &vals)  
{  
    if(root == NULL) return;  
    if(level == 1)  
    {  
        vals.push_back(root->val);  
        return;  
    }  
    levelOrderTraversal(root->left, level-1, vals);  
    levelOrderTraversal(root->right, level-1, vals);  
} 
  






int main()
{
	/// test code
	return true;
}






