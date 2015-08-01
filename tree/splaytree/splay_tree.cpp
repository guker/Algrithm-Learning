/**
 * SplayTree��չ��(C����): C����ʵ�ֵ���չ����
 *
 * @author skywang
 * @date 2014/02/03
 * @modify by hqwsky
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "splay_tree.h"

/*
 * ǰ�����"��չ��"
 */
void preorder_splaytree(SplayTree tree)
{
	if(tree != NULL)
	{
		printf("%d ", tree->key);
		preorder_splaytree(tree->left);
		preorder_splaytree(tree->right);
	}
}

/*
 * �������"��չ��"
 */
void inorder_splaytree(SplayTree tree)
{
	if(tree != NULL)
	{
		inorder_splaytree(tree->left);
		printf("%d ", tree->key);
		inorder_splaytree(tree->right);
	}
}

/*
 * �������"��չ��"
 */
void postorder_splaytree(SplayTree tree)
{
	if(tree != NULL)
	{
		postorder_splaytree(tree->left);
		postorder_splaytree(tree->right);
		printf("%d ", tree->key);
	}
}

/*
 * (�ݹ�ʵ��)����"��չ��x"�м�ֵΪkey�Ľڵ�
 */
Node* splaytree_search(SplayTree x, Type key)
{
	if (x==NULL || x->key==key)
		return x;

	if (key < x->key)
		return splaytree_search(x->left, key);
	else
		return splaytree_search(x->right, key);
}

/*
 * (�ǵݹ�ʵ��)����"��չ��x"�м�ֵΪkey�Ľڵ�
 */
Node* iterative_splaytree_search(SplayTree x, Type key)
{
	while ((x!=NULL) && (x->key!=key))
	{
		if (key < x->key)
			x = x->left;
		else
			x = x->right;
	}

	return x;
}

/* 
 * ������С��㣺����treeΪ��������չ������С��㡣
 */
Node* splaytree_minimum(SplayTree tree)
{
	if (tree == NULL)
		return NULL;

	while(tree->left != NULL)
		tree = tree->left;
	return tree;
}
 
/* 
 * ��������㣺����treeΪ��������չ��������㡣
 */
Node* splaytree_maximum(SplayTree tree)
{
	if (tree == NULL)
		return NULL;

	while(tree->right != NULL)
		tree = tree->right;
	return tree;
}

/* 
 * ��תkey��Ӧ�Ľڵ�Ϊ���ڵ㣬�����ظ��ڵ㡣
 *
 * ע�⣺
 *   (a)����չ���д���"��ֵΪkey�Ľڵ�"��
 *          ��"��ֵΪkey�Ľڵ�"��תΪ���ڵ㡣
 *   (b)����չ���в�����"��ֵΪkey�Ľڵ�"������key < tree->key��
 *      b-1 "��ֵΪkey�Ľڵ�"��ǰ���ڵ���ڵĻ�����"��ֵΪkey�Ľڵ�"��ǰ���ڵ���תΪ���ڵ㡣
 *      b-2 "��ֵΪkey�Ľڵ�"��ǰ���ڵ���ڵĻ�������ζ�ţ�key�������κμ�ֵ��С����ô��ʱ������С�ڵ���תΪ���ڵ㡣
 *   (c)����չ���в�����"��ֵΪkey�Ľڵ�"������key > tree->key��
 *      c-1 "��ֵΪkey�Ľڵ�"�ĺ�̽ڵ���ڵĻ�����"��ֵΪkey�Ľڵ�"�ĺ�̽ڵ���תΪ���ڵ㡣
 *      c-2 "��ֵΪkey�Ľڵ�"�ĺ�̽ڵ㲻���ڵĻ�������ζ�ţ�key�������κμ�ֵ������ô��ʱ�������ڵ���תΪ���ڵ㡣
 */
Node* splaytree_splay(SplayTree tree, Type key)
{
    Node N, *l, *r, *c;

    if (tree == NULL) 
        return tree;

    N.left = N.right = NULL;
    l = r = &N;

    for (;;)
    {
        if (key < tree->key)
        {
            if (tree->left == NULL)
                break;
            if (key < tree->left->key)
            {
                c = tree->left;                           /* 01, rotate right */
                tree->left = c->right;
                c->right = tree;
                tree = c;
                if (tree->left == NULL) 
                    break;
            }
            r->left = tree;                               /* 02, link right */
            r = tree;
            tree = tree->left;
        }
		else if (key > tree->key)
        {
            if (tree->right == NULL) 
                break;
            if (key > tree->right->key) 
            {
                c = tree->right;                          /* 03, rotate left */
                tree->right = c->left;
                c->left = tree;
                tree = c;
                if (tree->right == NULL) 
                    break;
            }
            l->right = tree;                              /* 04, link left */
            l = tree;
            tree = tree->right;
        }
		else
		{
            break;
        }
    }

    l->right = tree->left;                                /* 05, assemble */
    r->left = tree->right;
    tree->left = N.right;
    tree->right = N.left;

    return tree;
}

/* 
 * �������뵽��չ����(����ת)
 *
 * ����˵����
 *     tree ��չ���ĸ����
 *     z ����Ľ��
 * ����ֵ��
 *     ���ڵ�
 */
static Node* splaytree_insert(SplayTree tree, Node *z)
{
	Node *y = NULL;
	Node *x = tree;

	// ����z�Ĳ���λ��
	while (x != NULL)
	{
		y = x;
		if (z->key < x->key)
			x = x->left;
		else if (z->key > x->key)
			x = x->right;
		else
		{
			printf("�����������ͬ�ڵ�(%d)!\n", z->key);
			// �ͷ�����Ľڵ㣬������tree��
			free(z);
			return tree;
		}
	}

	if (y==NULL)
		tree = z;
	else if (z->key < y->key)
		y->left = z;
	else
		y->right = z;

	return tree;
}

/*
 * ������������չ����㡣
 *
 * ����˵����
 *     key �Ǽ�ֵ��
 *     parent �Ǹ���㡣
 *     left �����ӡ�
 *     right ���Һ��ӡ�
 */
static Node* create_splaytree_node(Type key, Node *left, Node* right)
{
	Node* p;

	if ((p = (Node *)malloc(sizeof(Node))) == NULL)
		return NULL;
	p->key = key;
	p->left = left;
	p->right = right;

	return p;
}

/* 
 * �½����(key)��Ȼ������뵽��չ���У���������ڵ���תΪ���ڵ�
 *
 * ����˵����
 *     tree ��չ���ĸ����
 *     key ������ļ�ֵ
 * ����ֵ��
 *     ���ڵ�
 */
Node* insert_splaytree(SplayTree tree, Type key)
{
	Node *z;	// �½����

	// ����½����ʧ�ܣ��򷵻ء�
	if ((z=create_splaytree_node(key, NULL, NULL)) == NULL)
		return tree;

	// ����ڵ�
	tree = splaytree_insert(tree, z);
	// ���ڵ�(key)��תΪ���ڵ�
	tree = splaytree_splay(tree, key);
}

/* 
 * ɾ�����(keyΪ�ڵ�ļ�ֵ)�������ظ��ڵ㡣
 *
 * ����˵����
 *     tree ��չ���ĸ����
 *     z ɾ���Ľ��
 * ����ֵ��
 *     ���ڵ�(���ڵ��Ǳ�ɾ���ڵ��ǰ���ڵ�)
 *
 */
Node* delete_splaytree(SplayTree tree, Type key)
{
    Node *x;

    if (tree == NULL) 
        return NULL;

	// ���Ҽ�ֵΪkey�Ľڵ㣬�Ҳ����Ļ�ֱ�ӷ��ء�
	if (splaytree_search(tree, key) == NULL)
		return tree;

	// ��key��Ӧ�Ľڵ���תΪ���ڵ㡣
    tree = splaytree_splay(tree, key);

	if (tree->left != NULL)
	{
		// ��"tree��ǰ���ڵ�"��תΪ���ڵ�
		x = splaytree_splay(tree->left, key);
		// �Ƴ�tree�ڵ�
		x->right = tree->right;
	}
	else
		x = tree->right;

	free(tree);

	return x;
}

/*
 * ������չ��
 */
void destroy_splaytree(SplayTree tree)
{
	if (tree==NULL)
		return ;

	if (tree->left != NULL)
		destroy_splaytree(tree->left);
	if (tree->right != NULL)
		destroy_splaytree(tree->right);

	free(tree);
}

/*
 * ��ӡ"��չ��"
 *
 * tree       -- ��չ���Ľڵ�
 * key        -- �ڵ�ļ�ֵ 
 * direction  --  0����ʾ�ýڵ��Ǹ��ڵ�;
 *               -1����ʾ�ýڵ������ĸ���������;
 *                1����ʾ�ýڵ������ĸ������Һ��ӡ�
 */
void print_splaytree(SplayTree tree, Type key, int direction)
{
	if(tree != NULL)
	{
		if(direction==0)	// tree�Ǹ��ڵ�
			printf("%2d is root\n", tree->key);
		else				// tree�Ƿ�֧�ڵ�
			printf("%2d is %2d's %6s child\n", tree->key, key, direction==1?"right" : "left");

		print_splaytree(tree->left, tree->key, -1);
		print_splaytree(tree->right,tree->key,  1);
	}
}