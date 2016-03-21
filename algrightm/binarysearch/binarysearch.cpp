/*
*                     ���ֲ��ң�binary search��
*
*       �㷨˼�룺�������м俪ʼ��ÿ���ų�һ������ݣ�ʱ�临�Ӷ�ΪO(lgN)
*/

#include<stdio.h>
int BinSearch(int Array[],int SizeOfArray,int key)  
{  
    int low=0,high=SizeOfArray-1;  
    int mid;  
    while (low<=high)  
    {  
        mid = low+(high-low)/2;//ͬ(low+high)/2,����Ϊ�˱������ 
        if(key>Array[mid])
			low = mid+1;
		else if(key < Array[mid])
			high = mid-1;
		else
			return mid;
    }
	printf("high - low = %d\n",high - low);
    return -1; 
}

/*  
*     �۲췢�֣�������Ҳ��ɹ�����low��ֵǡ����keyӦ���������в����λ��,���Ҵ�ʱlow = high +1
*
*   �ٶ���������a={1, 3, 4, 7, 8}�� ��ô���key=0������Ȼkey���������У�
*   ����ֲ����㷨���ջ�ʹ��low=0 > high=-1 �˳�ѭ�������key=9����keyҲ���������У�
*   �����low=5 > high=4�˳�ѭ�������key=5�������low=3 > high=2�˳�ѭ��
*
*/
int BinSearch01(int Array[],int SizeOfArray,int key)  
{  
    int low=0,high=SizeOfArray-1;  
    int mid;  
    while (low<=high)  
    {  
        mid = low+(high-low)/2;//ͬ(low+high)/2,����Ϊ�˱������ 
        if(key>Array[mid])
			low = mid+1;
		else if(key < Array[mid])
			high = mid-1;
		else
			return mid;
    }  
    return -(low+1); 
}

/*
*          ���ֲ������ֵ�һ�γ��ֵ�λ��
*
*   �������������д����ظ�����  �μ���������ᡷ�ھ��£��㷨�ľ�������ѭ������ʽ���������
*   ��ʱѭ���˳�ʱ��Ȼ�� low+1=high������a[low]<key<=a[high]
*/
int bsearch_first(int a[], int n, int key)  
{  
    int low = -1, high = n;  
    while (low + 1 != high) {  
        /*ѭ������ʽa[low]<key<=a[high] && low<high*/  
        int mid = low + (high - low) / 2; //ͬ��low+high��/ 2  
        if (key> a[mid])  
            low = mid;  
        else  
            high = mid;  
    }  
    /*assert: l+1=u && a[l]<t<=a[u]*/  
    int p = high;  
    if (p>=n || a[p]!=key)  
        p = -1;  
    return p;  
} 

/*               ��ת����Ԫ�ز�������
*   ���ֲ����㷨�������ؼ��㣺1����������
                            2�����ݵ�ǰ������м�Ԫ����x�Ĵ�С��ϵ��ȷ���´ζ��ֲ�����ǰ������仹�Ǻ����������
*
*   ��ϸ���������⣬���Է��֣�ÿ�θ���low��high���mid��mid��ߣ�[low, mid]�����ұߣ�[mid, high]������һ��������ġ�
*   a[mid]�ֱ���a[left]��a[right]�Ƚϣ�ȷ����һ��������ġ�
*
*   ������������ģ���x<a[mid]��x>a[left], ��right=mid-1�����������left =mid+1��
*
*   ����ұ�������ģ���x> a[mid] ��x<a[right] ��left=mid+1�����������right =mid-1��
*/
int bsearch_rotate(int a[], int n, int t)  
{  
    int low = 0, high = n-1;  
    while (low <= high) {  
        int mid = low + (high-low) / 2;  
        if (t == a[mid])  
            return mid;  
        if (a[mid] >= a[low]) { //�����������  
            if (t >= a[low] && t < a[mid])  
                high = mid - 1;  
            else  
                low = mid + 1;  
        } else {       //�����Ұ������  
            if (t > a[mid] && t <= a[high])  
                low = mid + 1;  
            else  
                high = mid - 1;  
        }     
    }     
    return -1;   
} 


int main(int argc,char* argv[])
{
	int a[7] = {1,3,3,4,6,8,9};
	int key = 2;
	printf("%d\n",BinSearch(a,7,key));
	return 0;
}