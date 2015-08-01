#include <stdio.h>

// ���鳤��
#define LENGTH(array) ( (sizeof(array)) / (sizeof(array[0])) )
// ������ֵ
#define swap(a,b)	(a^=b,b^=a,a^=b)

/*
 * ð������
 *
 * ����˵����
 *     a -- �����������
 *     n -- ����ĳ���
 */
void bubble_sort1(int a[], int n)
{
	int i,j;

	for (i=n-1; i>0; i--)
	{
        // ��a[0...i]���������ݷ���ĩβ
		for (j=0; j<i; j++)
		{
			if (a[j] > a[j+1])
				swap(a[j], a[j+1]);
		}
	}
}

/*
 * ð������(�Ľ���)
 *
 * ����˵����
 *     a -- �����������
 *     n -- ����ĳ���
 */
void bubble_sort2(int a[], int n)
{
	int i,j;
	int flag; 				// ���

	for (i=n-1; i>0; i--)
	{
		flag = 0;			// ��ʼ�����Ϊ0

        // ��a[0...i]���������ݷ���ĩβ
		for (j=0; j<i; j++)
		{
			if (a[j] > a[j+1])
			{
				swap(a[j], a[j+1]);
				flag = 1;	// ������������������Ϊ1
			}
		}

		if (flag==0)
			break;			// ��û������������˵������������
	}
}

void main()
{
	int i;
	int a[] = {20,40,30,10,60,50};
	int ilen = LENGTH(a);

	printf("before sort:");
	for (i=0; i<ilen; i++)
		printf("%d ", a[i]);
	printf("\n");

	bubble_sort1(a, ilen);
	//bubble_sort2(a, ilen);

	printf("after  sort:");
	for (i=0; i<ilen; i++)
		printf("%d ", a[i]);
	printf("\n");
}