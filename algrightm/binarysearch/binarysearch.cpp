/*
*                     二分查找（binary search）
*
*       算法思想：从数组中间开始，每次排除一半的数据，时间复杂度为O(lgN)
*/

#include<stdio.h>
int BinSearch(int Array[],int SizeOfArray,int key)  
{  
    int low=0,high=SizeOfArray-1;  
    int mid;  
    while (low<=high)  
    {  
        mid = low+(high-low)/2;//同(low+high)/2,这里为了避免溢出 
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
*     观察发现，如果查找不成功，则low的值恰好是key应该在数组中插入的位置,而且此时low = high +1.
*     假设某个时候[low,high],此时low+1=high，mid = low，显然此时key>a[mid],所以low = low+1=high，
*     mid = low+high/2 = high,此时key<a[mid],所以high = mid-1=high-1=low-1，退出循环
*
*   假定有序数组a={1, 3, 4, 7, 8}， 那么如果key=0，则显然key不在数组中，
*   则二分查找算法最终会使得low=0 > high=-1 退出循环；如果key=9，则key也不在数组中，
*   则最后low=5 > high=4退出循环。如果key=5，则最后low=3 > high=2退出循环
*
*/
int BinSearch01(int Array[],int SizeOfArray,int key)  
{  
    int low=0,high=SizeOfArray-1;  
    int mid;  
    while (low<=high)  
    {  
        mid = low+(high-low)/2;//同(low+high)/2,这里为了避免溢出 
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
*          二分查找数字第一次出现的位置
*
*   考虑有序数组中存在重复数字  参见《编程珠玑》第九章，算法的精髓在于循环不变式的巧妙设计
*   此时循环退出时必然有 low+1=high，而且a[low]<key<=a[high]
*/
int bsearch_first(int a[], int n, int key)  
{  
    int low = -1, high = n;  
    while (low + 1 != high) {  
        /*循环不变式a[low]<key<=a[high] && low<high*/  
        int mid = low + (high - low) / 2; //同（low+high）/ 2  
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

/*               旋转数组元素查找问题
*   二分查找算法有两个关键点：1）数组有序；
                            2）根据当前区间的中间元素与x的大小关系，确定下次二分查找在前半段区间还是后半段区间进行
*
*   仔细分析该问题，可以发现，每次根据low和high求出mid后，mid左边（[low, mid]）和右边（[mid, high]）至少一个是有序的。
*   a[mid]分别与a[left]和a[right]比较，确定哪一段是有序的。
*
*   如果左边是有序的，若x<a[mid]且x>a[left], 则right=mid-1；其他情况，left =mid+1；
*
*   如果右边是有序的，若x> a[mid] 且x<a[right] 则left=mid+1；其他情况，right =mid-1；
*/
int bsearch_rotate(int a[], int n, int t)  
{  
    int low = 0, high = n-1;  
    while (low <= high) {  
        int mid = low + (high-low) / 2;  
        if (t == a[mid])  
            return mid;  
        if (a[mid] >= a[low]) { //数组左半有序  
            if (t >= a[low] && t < a[mid])  
                high = mid - 1;  
            else  
                low = mid + 1;  
        } else {       //数组右半段有序  
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
