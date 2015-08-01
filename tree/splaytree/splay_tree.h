#ifndef _SPLAY_TREE_H_
#define _SPLAY_TREE_H_

typedef int Type;

typedef struct SplayTreeNode {
	Type key;						// �ؼ���(��ֵ)
	struct SplayTreeNode *left;		// ����
	struct SplayTreeNode *right;	// �Һ���
} Node, *SplayTree; 

// ǰ�����"��չ��"
void preorder_splaytree(SplayTree tree);
// �������"��չ��"
void inorder_splaytree(SplayTree tree);
// �������"��չ��"
void postorder_splaytree(SplayTree tree);

// (�ݹ�ʵ��)����"��չ��x"�м�ֵΪkey�Ľڵ�
Node* splaytree_search(SplayTree x, Type key);
// (�ǵݹ�ʵ��)����"��չ��x"�м�ֵΪkey�Ľڵ�
Node* iterative_splaytree_search(SplayTree x, Type key);

// ������С��㣺����treeΪ��������չ������С��㡣
Node* splaytree_minimum(SplayTree tree);
// ��������㣺����treeΪ��������չ��������㡣
Node* splaytree_maximum(SplayTree tree);

// ��תkey��Ӧ�Ľڵ�Ϊ���ڵ㡣
Node* splaytree_splay(SplayTree tree, Type key);

// �������뵽��չ���У������ظ��ڵ�
Node* insert_splaytree(SplayTree tree, Type key);

// ɾ�����(keyΪ�ڵ��ֵ)�������ظ��ڵ�
Node* delete_splaytree(SplayTree tree, Type key);

// ������չ��
void destroy_splaytree(SplayTree tree);

// ��ӡ��չ��
void print_splaytree(SplayTree tree, Type key, int direction);

#endif