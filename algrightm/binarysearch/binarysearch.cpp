/*
*                     二分查找（binary search）
*
*       算法思想：从数组中间开始，每次排除一半的数据，时间复杂度为O(lgN)
*/
/*
*       1.while 循环的条件是 low<=high，这里如果查找值未找到，则此时一定 low = high + 1 
*       
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
/*
            非降序数组A, 查找 第一个  值==val的元素，若找到则返回下标位置，若未找到则返回-1
            
            当 val < a[mid] 时， 接下来的搜索范围减半  high = mid - 1
            当 val > a[mid] 时， 接下来的搜索范围减半  low  = mid + 1
            当 val == a[mid] 时，这个时候就不能简单的返回了，我们要求的是第一个 == val 的值，什么条件下是第一个呢？
            
            当 mid == 0 那当然是第一个
             当 mid > 1 && a[mid - 1] != val 这个时候也是第一个
             其他情况下，这个时候查找到的值不是第一个，此时我们应该继续搜索，而不是返回，搜索范围是什么呢？ 因为是查找第一个，那么接下来肯定应该在
             此时位置的左边继续搜索，即 high = mid - 1

*/
int search_first(int* a, int len, int val)
  {
     assert(a != NULL && len > 1);
     int low = 0;
      int high = len - 1;
      while (low <= high) {
          int mid = low + (high - low) / 2;
          if (val < a[mid]) {
              high = mid - 1;
        } else if (val > a[mid]) {
             low = mid + 1;
         } else {
             if (mid == 0) return mid;
             if (mid > 0 && a[mid-1] != val) return mid;
            high = mid - 1;
         }
     }
     return -1;
 }
 /*
               非降序数组A, 查找 最后一个值==val的元素，若找到则返回下标位置，若未找到则返回-1
 */
  int search_last(int* a, int len, int val)
  {
      assert(a != NULL && len > 1);
      int low = 0;
      int high = len - 1;
      while (low <= high) {
          int mid = low + (high - low) / 2;
          if (val < a[mid]) {
              high = mid - 1;
         } else if (val > a[mid]) {
             low = mid + 1;
         } else {
             if (mid == (len - 1)) return mid;
             if (mid < (len - 1) && a[mid+1] != val) return mid;
             low = mid + 1;
         }
     }
     return -1;
 }

 
 
 
 
/*
        非降序数组A, 查找任一 值为val的元素，保证插入该元素后 数组仍然有序，返回可以插入的任一位置
        当 a[mid] == val 则返回 mid，因为在该位置插入 val 数组一定保证有序
        当 循环结束后 仍未查找到 val值，我们之前说过，此时 一定有 high = low + 1，其实查找值永远都 
        应该在 low和high组成的区间内，现在区间内没空位了，所以可以宣告该值没有查找到，如果仍然有空位
        ，则val一定在该区间内。也就是说此时的 low 和 high 这两个值就是 val 应该处于的位置，因为通常都
        是在位置之前插入，所以此时直接返回 low 即可

*/
int bsearch_insert(int* a, int len, int val)
 {
     assert(a != NULL && len > 0);
      int low = 0;
      int high = len - 1;
      while (low <= high) {
          int mid = low + (high - low) / 2;
          if (val < a[mid]) {
              high = mid - 1;
          } else if (val > a[mid]) {
            low = mid + 1;
         } else {
            return mid;
         }
    }
    return low;
 }
 
 /*
             非降序数组A, 查找任一 值为val的元素，保证插入该元素后 数组仍然有序，返回可以插入的第一个位置
             因为是要求第一个可以插入的位置，当查找值不在数组中时，插入的位置是唯一的，即 return low
 */
 int insert_first(int* a, int len, int val)
 {
      assert(a != NULL && len > 1);
     int low = 0;
     int high = len - 1;
     while (low <= high) {
         int mid = low + (high - low) / 2;
         if (val < a[mid]) {
             high = mid - 1;
         } else if (val > a[mid]) {
             low = mid + 1;
         } else {
             if (mid == 0) return mid;
             if (mid > 0 && a[mid-1] != val) return mid;
             high = mid - 1;
         }
     }
     return low;
 }
/*
               非降序数组A, 查找 任一个  值==val的元素，若找到则 返回一组下标区间(该区间所有值 ==val)，若未找到则返回-1
               1.当 a[mid] == val 时，并不立即 return mid，而是 以 mid 为中心 向左右两边搜索 得到所有值 == val 的区间,但此时的算法
               复杂度为O(N)
               2.所以可以使用上面找第一个与最后一个的下标，这样就可以组成区间
*/


/*
                给定一个有序（非降序）数组A，可含有重复元素，求最小的i使得A[i]等于target，不存在则返回-1

*/
int searchFirstPos(int A[], int n, int target)  
{  
    if(n <= 0) return -1;  
    int low = 0, high = n-1;  
    while(low < high)  
    {  
        int mid = low+((high-low)>>1);  
        if(A[mid] < target)  
            low = mid+1;  
        else // A[mid] >= target  
            high = mid;  
    }  
    /*  
    循环过程中，当low大于0时，A[low-1]是小于target的，因为A[mid] < target时， 
    low=mid+1；当high小于n-1时，A[high]是大于等于target的，因为A[mid] >= target时， 
    high = mid；循环结束时，low 等于 high，所以，如果A[low](A[high])等于target， 
    那么low(high)就是target出现的最小位置，否则target在数组中不存在。 
    */  
    if(A[low] != target)  
        return -1;  
    else  
        return low;  
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
