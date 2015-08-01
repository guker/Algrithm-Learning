/**
 * �����(����)
 *
 * @author skywang
 * @date 2014/03/07
 * @modify by hqwsky
 *
 */

#include <stdio.h>
#include <stdlib.h>

#define LENGTH(a) ( (sizeof(a)) / (sizeof(a[0])) )

static int m_heap[30];		// ����
static int m_capacity=30;	// �ܵ�����
static int m_size=0;		// ʵ������(��ʼ��Ϊ0)
 
/* 
 * ����data�ڶ�����е�����
 *
 * ����ֵ��
 *     ���� -- ����data�������е�����
 *     ������ -- -1
 */
int get_index(int data)
{
	int i=0;

	for(i=0; i<m_size; i++)
		if (data==m_heap[i])
			return i;

	return -1;
}

/* 
 * ���ѵ����µ����㷨
 *
 * ע������ʵ�ֵĶ��У���N���ڵ�����ӵ�����ֵ��(2N+1)���Һ��ӵ�������(2N+2)��
 *
 * ����˵����
 *     start -- ���µ��ڵ����ʼλ��(һ��Ϊ0����ʾ�ӵ�1����ʼ)
 *     end   -- ������Χ(һ��Ϊ���������һ��Ԫ�ص�����)
 */
static void maxheap_filterdown(int start, int end)
{
    int c = start; 	 	// ��ǰ(current)�ڵ��λ��
    int l = 2*c + 1; 	// ��(left)���ӵ�λ��
    int tmp = m_heap[c];	// ��ǰ(current)�ڵ�Ĵ�С

    while(l <= end)
    {
		// "l"�����ӣ�"l+1"���Һ���
        if(l < end && m_heap[l] < m_heap[l+1])
            l++;		// ������������ѡ��ϴ��ߣ���m_heap[l+1]
        if(tmp >= m_heap[l])
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
 * ɾ�������е�data
 *
 * ����ֵ��
 *      0���ɹ�
 *     -1��ʧ��
 */
int maxheap_remove(int data)
{
	int index;
    // ���"��"�ѿգ��򷵻�-1
    if(m_size == 0)
        return -1;

	// ��ȡdata�������е�����
	index = get_index(data); 
	if (index==-1)
		return -1;

    m_heap[index] = m_heap[--m_size];		// �����Ԫ���
    maxheap_filterdown(index, m_size-1);	// ��indexλ�ÿ�ʼ�������µ���Ϊ����

    return 0;
}

/*
 * ���ѵ����ϵ����㷨(��start��ʼ����ֱ��0��������)
 *
 * ע������ʵ�ֵĶ��У���N���ڵ�����ӵ�����ֵ��(2N+1)���Һ��ӵ�������(2N+2)��
 *
 * ����˵����
 *     start -- ���ϵ��ڵ����ʼλ��(һ��Ϊ���������һ��Ԫ�ص�����)
 */
static void maxheap_filterup(int start)
{
    int c = start;			// ��ǰ�ڵ�(current)��λ��
    int p = (c-1)/2;		// ��(parent)����λ�� 
    int tmp = m_heap[c];		// ��ǰ�ڵ�(current)�Ĵ�С

    while(c > 0)
    {
        if(m_heap[p] >= tmp)
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
 * ��data���뵽�������
 *
 * ����ֵ��
 *     0����ʾ�ɹ�
 *    -1����ʾʧ��
 */
int maxheap_insert(int data)
{
    // ���"��"�������򷵻�
    if(m_size == m_capacity)
        return -1;
 
    m_heap[m_size] = data;		// ��"����"���ڱ�β
    maxheap_filterup(m_size);	// ���ϵ�����
    m_size++;					// �ѵ�ʵ������+1

    return 0;
}
  
/* 
 * ��ӡ�����
 *
 * ����ֵ��
 *     0����ʾ�ɹ�
 *    -1����ʾʧ��
 */
void maxheap_print()
{
	int i;
	for (i=0; i<m_size; i++)
		printf("%d ", m_heap[i]);
}
	
void main()
{
    int a[] = {10, 40, 30, 60, 90, 70, 20, 50, 80};
	int i, len=LENGTH(a);

	printf("== �������: ");
    for(i=0; i<len; i++)
	{
		printf("%d ", a[i]);
        maxheap_insert(a[i]);
	}

	printf("\n== �� �� ��: ");
	maxheap_print();

	i=85;
    maxheap_insert(i);
	printf("\n== ���Ԫ��: %d", i);
	printf("\n== �� �� ��: ");
	maxheap_print();

	i=90;
	maxheap_remove(i);
	printf("\n== ɾ��Ԫ��: %d", i);
	printf("\n== �� �� ��: ");
	maxheap_print();
	printf("\n");
}