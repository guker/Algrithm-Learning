#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"

static HuffmanNode *m_heap;	// ��С�ѵ�����
static int m_capacity;		// �ܵ�����
static int m_size;			// ��ǰ��Ч���ݵ�����
 
/* 
 * ��С�ѵ����µ����㷨
 *
 * ע������ʵ�ֵĶ��У���N���ڵ�����ӵ�����ֵ��(2N+1)���Һ��ӵ�������(2N+2)��
 *
 * ����˵����
 *     start -- ���µ��ڵ����ʼλ��(һ��Ϊ0����ʾ�ӵ�1����ʼ)
 *     end   -- ������Χ(һ��Ϊ���������һ��Ԫ�ص�����)
 */
static void minheap_filterdown(int start, int end)
{
    int c = start; 	 	// ��ǰ(current)�ڵ��λ��
    int l = 2*c + 1; 	// ��(left)���ӵ�λ��
    HuffmanNode tmp = m_heap[c];	// ��ǰ(current)�ڵ�

    while(l <= end)
    {
		// "l"�����ӣ�"l+1"���Һ���
        if(l < end && m_heap[l].key > m_heap[l+1].key)
            l++;		// ������������ѡ���С�ߣ���m_heap[l+1]
        if(tmp.key <= m_heap[l].key)
            break;		//��������
        else
        {
            m_heap[c] = m_heap[l];
            c = l;
            l = 2*l + 1;   
        }       
    }   
    m_heap[c] = tmp;
}
 
/*
 * ��С�ѵ����ϵ����㷨(��start��ʼ����ֱ��0��������)
 *
 * ע������ʵ�ֵĶ��У���N���ڵ�����ӵ�����ֵ��(2N+1)���Һ��ӵ�������(2N+2)��
 *
 * ����˵����
 *     start -- ���ϵ��ڵ����ʼλ��(һ��Ϊ���������һ��Ԫ�ص�����)
 */
static void filter_up(int start)
{
    int c = start;			// ��ǰ�ڵ�(current)��λ��
    int p = (c-1)/2;		// ��(parent)����λ�� 
    HuffmanNode tmp = m_heap[c];		// ��ǰ�ڵ�(current)

    while(c > 0)
    {
        if(m_heap[p].key <= tmp.key)
            break;
        else
        {
            m_heap[c] = m_heap[p];
            c = p;
            p = (p-1)/2;   
        }       
    }
    m_heap[c] = tmp;
}
  
/* 
 * ��node���뵽�������
 *
 * ����ֵ��
 *     0����ʾ�ɹ�
 *    -1����ʾʧ��
 */
int dump_to_minheap(HuffmanNode *node)
{
    // ���"��"�������򷵻�
    if(m_size == m_capacity)
        return -1;
 
    m_heap[m_size] = *node;     // ��"node������"ȫ�����Ƶ�"����ĩβ"
    filter_up(m_size);			// ���ϵ�����
    m_size++;					// �ѵ�ʵ������+1

    return 0;
}

/*
 * ��������HuffmanNode�ڵ��ȫ������
 */
static void swap_node(int i, int j)
{
	HuffmanNode tmp = m_heap[i];
	m_heap[i] = m_heap[j];
	m_heap[j] = tmp;
}

/* 
 * �½�һ���ڵ㣬������С������С�ڵ�����ݸ��Ƹ��ýڵ㡣
 * Ȼ�����С�ڵ�֮����������¹������С�ѡ�
 *
 * ����ֵ��
 *     ʧ�ܷ���NULL��
 */
HuffmanNode* dump_from_minheap()
{
    // ���"��"�ѿգ��򷵻�
    if(m_size == 0)
		return NULL;

	HuffmanNode *node;
    if((node = (HuffmanNode *)malloc(sizeof(HuffmanNode))) == NULL)
		return NULL;

	// ��"��С�ڵ��ȫ������"���Ƹ�node
	*node = m_heap[0];

	swap_node(0, m_size-1);				// ����"��С�ڵ�"��"���һ���ڵ�"
    minheap_filterdown(0, m_size-2);	// ��m_heap[0...m_size-2]�����һ����С��
	m_size--;						

	return node;
}

/* 
 * ��ӡ�����
 *
 * ����ֵ��
 *     0����ʾ�ɹ�
 *    -1����ʾʧ��
 */
void minheap_print()
{
	int i;
	for (i=0; i<m_size; i++)
		printf("%d ", m_heap[i].key);
}

/* 
 * ������С��
 *
 * ����˵����
 *     a -- �������ڵ�����
 *     size -- �����С
 */
void create_minheap(Type a[], int size)
{
	int i;

	// ������С������Ӧ������
	m_size = size;
	m_capacity = size;
	m_heap = (HuffmanNode *)malloc(sizeof(HuffmanNode)*size);
	
	// ��ʼ������
    for(i=0; i<size; i++)
	{
		m_heap[i].key = a[i];
		m_heap[i].parent = m_heap[i].left = m_heap[i].right = NULL;
	}

    // ��(size/2-1) --> 0��α���������֮�󣬵õ�������ʵ������һ����С�ѡ�
    for (i = size / 2 - 1; i >= 0; i--)
		minheap_filterdown(i, size-1);
}

// ������С��
void destroy_minheap()
{
	m_size = 0;
	m_capacity = 0;
	free(m_heap);
}