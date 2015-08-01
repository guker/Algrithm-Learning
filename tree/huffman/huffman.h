#ifndef _AVL_TREE_H_
#define _AVL_TREE_H_

typedef int Type;

typedef struct _HuffmanNode{
	Type key;					// Ȩֵ
	struct _HuffmanNode *left;	// ����
	struct _HuffmanNode *right;	// �Һ���
	struct _HuffmanNode *parent;	// ���ڵ�
}HuffmanNode, *HuffmanTree;

// ǰ�����"Huffman��"
void preorder_huffman(HuffmanTree tree);
// �������"Huffman��"
void inorder_huffman(HuffmanTree tree);
// �������"Huffman��"
void postorder_huffman(HuffmanTree tree);

// ����Huffman��
HuffmanNode* create_huffman(Type arr[], int size);

// ����Huffman��
void destroy_huffman(HuffmanTree tree);

// ��ӡHuffman��
void print_huffman(HuffmanTree tree);

#endif