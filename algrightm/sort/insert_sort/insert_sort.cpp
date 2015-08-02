#include <stdio.h>

// ���鳤��
#define LENGTH(array) ( (sizeof(array)) / (sizeof(array[0])) )

/*
 * ֱ�Ӳ�������
 *
 * ����˵����
 *     a -- �����������
 *     n -- ����ĳ���
 */
void insert_sort(int a[], int n)
{
	int i, j, k;

	for (i = 1; i < n; i++)
	{
		//Ϊa[i]��ǰ���a[0...i-1]������������һ�����ʵ�λ��
		for (j = i - 1; j >= 0; j--)
			if (a[j] < a[i])
				break;

		//���ҵ���һ�����ʵ�λ��
		if (j != i - 1)
		{
			//����a[i]������������
			int temp = a[i];
			for (k = i - 1; k > j; k--)
				a[k + 1] = a[k];
			//��a[i]�ŵ���ȷλ����
			a[k + 1] = temp;
		}
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

	insert_sort(a, ilen);

	printf("after  sort:");
	for (i=0; i<ilen; i++)
		printf("%d ", a[i]);
	printf("\n");
}