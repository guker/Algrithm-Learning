#ifndef _BINARY_SEARCH_TREE_H_
#define _BINARY_SEARCH_TREE_H_

typedef int Type;

typedef struct BSTreeNode{
	Type   key;					// �ؼ���(��ֵ)
	struct BSTreeNode *left;	// ����
	struct BSTreeNode *right;	// �Һ���
	struct BSTreeNode *parent;	// �����
}Node, *BSTree;

// ǰ�����"������"
void preorder_bstree(BSTree tree);
// �������"������"
void inorder_bstree(BSTree tree);
// �������"������"
void postorder_bstree(BSTree tree);

// (�ݹ�ʵ��)����"������"�м�ֵΪkey�Ľڵ�
Node* bstree_search(BSTree x, Type key);
// (�ǵݹ�ʵ��)����"������"�м�ֵΪkey�Ľڵ�
Node* iterative_bstree_search(BSTree x, Type key);

// ������С��㣺����treeΪ�����Ķ���������С��㡣
Node* bstree_minimum(BSTree tree);
// ��������㣺����treeΪ�����Ķ�����������㡣
Node* bstree_maximum(BSTree tree);

// �ҽ��(x)�ĺ�̽�㡣��������"������������ֵ���ڸý��"��"��С���"��
Node* bstree_successor(Node *x);
// �ҽ��(x)��ǰ����㡣��������"������������ֵС�ڸý��"��"�����"��
Node* bstree_predecessor(Node *x);

// �������뵽�������У������ظ��ڵ�
Node* insert_bstree(BSTree tree, Type key);

// ɾ�����(keyΪ�ڵ��ֵ)�������ظ��ڵ�
Node* delete_bstree(BSTree tree, Type key);

// ���ٶ�����
void destroy_bstree(BSTree tree);

// ��ӡ������
void print_bstree(BSTree tree, Type key, int direction);

#endif