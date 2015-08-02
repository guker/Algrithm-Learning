#include <stdio.h>

// ���鳤��
#define LENGTH(array) ( (sizeof(array)) / (sizeof(array[0])) )
#define swap(a,b) (a^=b,b^=a,a^=b)

/*
 * ѡ������
 *
 * ����˵����
 *     a -- �����������
 *     n -- ����ĳ���
 */
void select_sort(int a[], int n)
{
	int i;		// ��������ĩβλ��
	int j;		// ����������ʼλ��
	int min;	// ����������СԪ��λ��

	for(i=0; i<n; i++)
	{
		min=i;

		// �ҳ�"a[i+1] ... a[n]"֮�����СԪ�أ�����ֵ��min��
		for(j=i+1; j<n; j++)
		{
			if(a[j] < a[min])
				min=j;
		}

		// ��min!=i���򽻻� a[i] �� a[min]��
		// ����֮�󣬱�֤��a[0] ... a[i] ֮���Ԫ��������ġ�
		if(min != i)
			swap(a[i], a[min]);
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

	select_sort(a, ilen);

	printf("after  sort:");
	for (i=0; i<ilen; i++)
		printf("%d ", a[i]);
	printf("\n");
}