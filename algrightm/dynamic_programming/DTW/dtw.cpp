/*============================================================================================================================================

                                                        dynamic time warping 

												            动态时间规整

	算法思想：  计算时间序列之间的距离，时间序列的点可以为特征矢量，两个时间序列的长度可以不同

	步骤：1）  计算距离矩阵，矩阵的ij位置上的值为序列1的第i个特征矢量与序列2的第j个特征矢量的距离，此时的距离可以为欧氏距离，曼哈顿距离等
	      
		  2） 根据距离矩阵初始化累积距离矩阵的第0行与第0列

		  3） 计算累积距离矩阵的ij位置上的值，最后一个元素的值即为时间序列之间的距离

		  4） 找出最短路径，即序列之间的映射关系


	应用：孤立词识别系统，利用模板匹配法，在训练模型阶段，用户将词汇表中的单词说一遍，提取MFCC特征序列，作为该词汇的模板，存入模板库。识别阶段，对于一个
	      新的需要识别的词，同样提取MFCC特征序列，然后采用DTW算法与模板库的每一个模板进行匹配，计算距离，求出最短距离对应的模板即为识别的结果。


   input file1.txt：
                    1 1 1 1 1 1 1 1 1 1 1 1
                    2 2 2 2 2 2 2 2 2 2 2 2
                    3 3 3 3 3 3 3 3 3 3 3 3
                    4 4 4 4 4 4 4 4 4 4 4 4
                    5 5 5 5 5 5 5 5 5 5 5 5
                    6 6 6 6 6 6 6 6 6 6 6 6
                    7 7 7 7 7 7 7 7 7 7 7 7
                    8 8 8 8 8 8 8 8 8 8 8 8
                    9 9 9 9 9 9 9 9 9 9 9 9
	input file2.txt
	                1 1 1 1 1 1 1 1 1 1 1 1
					3 3 3 3 3 3 3 3 3 3 3 3
					5 5 5 5 5 5 5 5 5 5 5 5
					7 7 7 7 7 7 7 7 7 7 7 7
					9 9 9 9 9 9 9 9 9 9 9 9
					11 11 11 11 11 11 11 11 11 11 11 11

===============================================================================================================================================*/


#include<stdio.h>
#include<math.h>
#include<malloc.h>


int  distance_measure(int ct[12], int cr[12]) 
{

	int i;
	int D = 0 ;
	for(i=0; i<12; i++)
		D += (ct[i]-cr[i])*(ct[i]-cr[i]) ; // 考虑为整型，不开方
	return D;
}
int min( int x, int y, int z ) // return minimum among integer x, y and z
{
	if( ( x <= y ) && ( x <= z ) ) return x;
	if( ( y <= x ) && ( y <= z ) ) return y;
	if( ( z <= x ) && ( z <= y ) ) return z;
}
int main()
{
	int i,k;
	printf("\n------------------------------------------ input1 -----------------------------\n");
	int n;
	printf("First Input Text File => No. of Rows : ");
	scanf("%d",&n);

	int **ceps1 = (int **)malloc(sizeof(int*)*n);
	for(int i=0; i < n;i++)
	{
		ceps1[i]= (int *)malloc(sizeof(int)*12);
	}
	char filename1[256];
	printf("First Input Text File Name : ");
	scanf("%s",filename1);
	printf("\n");
	FILE *file1;
	file1 = fopen(filename1,"r");
	if(file1==NULL)
		printf("file not found!");
	for(i=0; i<n; i++)
	{
		for(k=0; k<12; k++)
		{
			fscanf(file1,"%d",&ceps1[i][k]);
			printf("%d ",ceps1[i][k]);
		}printf("\n");
	}
	fclose(file1);
	printf("\n------------------------------------------ input2 -----------------------------\n");
	int m;
	printf("First Input Text File => No. of Rows : ");
	scanf("%d",&m);
	int** ceps2 = (int**)malloc(sizeof(int *)*m);

	for(int i= 0;i<m;i++)
	{
		ceps2[i]=(int*)malloc(sizeof(int)*12);
	}


	char filename2[256];
	printf("Second Input Text File Name : ");
	scanf("%s",filename2);
	printf("\n");
	FILE *file2;
	file2 = fopen(filename2,"r");
	if(file2==NULL)
		printf("file not found!");
	for(i=0; i<m; i++)
	{
		for(k=0; k<12; k++)
		{
			fscanf(file2,"%d",&ceps2[i][k]);
			printf("%d ",ceps2[i][k]);
		}printf("\n");
	}
	fclose(file2);
	printf("\n----------------------------- Local Distance Matrix ---------------------------\n\n");
	int local_distance[n][m];
	for(i=0; i<n; i++)
	{
		for(k=0; k<m; k++)
		{
			local_distance[i][k] = distance_measure(ceps1[i],ceps2[k]);
			printf("%d\t ",local_distance[i][k]);
		}
		printf("\n");
	}
	printf("-------------------------------------------------------------------------------\n\n");
	printf("----------------------------- Global Distance Matrix --------------------------\n\n");
	int global_distance[n][m];
	global_distance[0][0] = local_distance[0][0];
	printf("%d\t ",global_distance[0][0]);
	for(i=1; i<n; i++) // generating first row element of global_distance matrix
		global_distance[i][0] = local_distance[i][0] + global_distance[i-1][0];
	for(k=1; k<m; k++) // generating first column element of global_distance matrix
	{
		global_distance[0][k] = local_distance[0][k] + global_distance[0][k-1];
		printf("%d\t ",global_distance[0][k]);
	}
	printf("\n");
	for(i=1; i<n; i++)
	{
		printf("%d\t ",global_distance[i][0]);
		for(k=1; k<m; k++)
		{
			global_distance[i][k] = local_distance[i][k] + min(global_distance[i-1][k],global_distance[i-1][k-1],global_distance[i][k-1]);
			printf("%d\t ",global_distance[i][k]);
		}
		printf("\n");
	}
	printf("-------------------------------------------------------------------------------\n\n");
	printf("Optimal Warping Path : (0,0) ");
	i=0;
	k=0;
	while((i!=n-1)||(k!=m-1))
	{
		if(i==n-1) // if you reached to the last row (n-1) then go only one step forward in last row
			k=k+1;
		else if(k==m-1) //if you have reached to the last column (m-1) then go only one step upward in last column
			i=i+1;
		else
		{ 
			int global_minm = min(global_distance[i+1][k],global_distance[i+1][k+1],global_distance[i][k+1]);
			if(global_distance[i+1][k] == global_minm)
			{
				i=i+1;
			}
			else if(global_distance[i+1][k+1] == global_minm)
			{
				i=i+1;
				k=k+1;
			}
			else//(global_distance[i][k+1] == global_minm)
			{
				k=k+1;
			}
		}
		printf("(%d,%d) ",i,k);
	}
	printf("\nOptimal Warping Path Cost : %d\n", global_distance[n-1][m-1]);
	printf("\n-------------------------------------------------------------------------------\n\n");
	return 0;
}