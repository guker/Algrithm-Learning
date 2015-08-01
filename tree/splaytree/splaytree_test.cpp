#include <stdio.h>
#include "splay_tree.h"

static int arr[]= {10,50,40,30,20,60};
#define TBL_SIZE(a) ( (sizeof(a)) / (sizeof(a[0])) )

void main()
{
	int i, ilen;
	SplayTree root=NULL;

	printf("== �������: ");
	ilen = TBL_SIZE(arr);
	for(i=0; i<ilen; i++)
	{
		printf("%d ", arr[i]);
		root = insert_splaytree(root, arr[i]);
	}

	printf("\n== ǰ�����: ");
	preorder_splaytree(root);

	printf("\n== �������: ");
	inorder_splaytree(root);

	printf("\n== �������: ");
	postorder_splaytree(root);
	printf("\n");

	printf("== ��Сֵ: %d\n", splaytree_minimum(root)->key);
	printf("== ���ֵ: %d\n", splaytree_maximum(root)->key);
	printf("== ������ϸ��Ϣ: \n");
	print_splaytree(root, root->key, 0);

	i = 30;
	printf("\n== ��ת�ڵ�(%d)Ϊ���ڵ�\n", i);
	printf("== ������ϸ��Ϣ: \n");
	root = splaytree_splay(root, i);
	print_splaytree(root, root->key, 0);

	// ������չ��
	destroy_splaytree(root);
}