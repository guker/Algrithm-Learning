#include <stdio.h>

// ���鳤��
#define LENGTH(array) ( (sizeof(array)) / (sizeof(array[0])) )

/*
 * ��������
 *
 * ����˵����
 *     a -- �����������
 *     l -- �������߽�(���磬����ʼλ�ÿ�ʼ������l=0)
 *     r -- ������ұ߽�(���磬�������������ĩβ����r=a.length-1)
 */
void quick_sort(int a[], int l, int r)
{
    if (l < r)
    {
		int i,j,x;

        i = l;
        j = r;
        x = a[i];
        while (i < j)
        {
            while(i < j && a[j] > x)
				j--; // ���������ҵ�һ��С��x����
            if(i < j)
				a[i++] = a[j];
            while(i < j && a[i] < x)
				i++; // ���������ҵ�һ������x����
            if(i < j)
				a[j--] = a[i];
        }
        a[i] = x;
        quick_sort(a, l, i-1); /* �ݹ���� */
        quick_sort(a, i+1, r); /* �ݹ���� */
    }
}

void main()
{
	int i;
	int a[] = {30,40,60,10,20,50};
	//int a[] = {10,20,30,40,50,60};
	int ilen = LENGTH(a);

	printf("before sort:");
	for (i=0; i<ilen; i++)
		printf("%d ", a[i]);
	printf("\n");

	quick_sort(a, 0, ilen-1);

	printf("after  sort:");
	for (i=0; i<ilen; i++)
		printf("%d ", a[i]);
	printf("\n");
}