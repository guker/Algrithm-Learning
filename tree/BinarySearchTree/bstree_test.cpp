#include <stdio.h>
#include "bstree.h"

static int arr[]= {1,5,4,3,2,6};
#define TBL_SIZE(a) ( (sizeof(a)) / (sizeof(a[0])) )

void main()
{
	int i, ilen;
	BSTree root=NULL;

	printf("== �������: ");
	ilen = TBL_SIZE(arr);
	for(i=0; i<ilen; i++)
	{
		printf("%d ", arr[i]);
		root = insert_bstree(root, arr[i]);
	}

	printf("\n== ǰ�����: ");
	preorder_bstree(root);

	printf("\n== �������: ");
	inorder_bstree(root);

	printf("\n== �������: ");
	postorder_bstree(root);
	printf("\n");

	printf("== ��Сֵ: %d\n", bstree_minimum(root)->key);
	printf("== ���ֵ: %d\n", bstree_maximum(root)->key);
	printf("== ������ϸ��Ϣ: \n");
	print_bstree(root, root->key, 0);

	printf("\n== ɾ�����ڵ�: %d", arr[3]);
	root = delete_bstree(root, arr[3]);

	printf("\n== �������: ");
	inorder_bstree(root);
	printf("\n");

	// ���ٶ�����
	destroy_bstree(root);
}