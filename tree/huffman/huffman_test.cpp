#include <stdio.h>
#include "huffman.h"

#define LENGTH(a) ( (sizeof(a)) / (sizeof(a[0])) )

void main()
{
	int a[]= {5,6,8,7,15};
	int i,ilen=LENGTH(a);
	HuffmanTree root=NULL;

	printf("== �������: ");
	for(i=0; i<ilen; i++)
		printf("%d ", a[i]);

	// ��������a��Ӧ��Huffman��
	root = create_huffman(a, ilen);

	printf("\n== ǰ�����: ");
	preorder_huffman(root);

	printf("\n== �������: ");
	inorder_huffman(root);

	printf("\n== �������: ");
	postorder_huffman(root);
	printf("\n");

	printf("== ������ϸ��Ϣ: \n");
	print_huffman(root);

	// ���ٶ�����
	destroy_huffman(root);
}