/*============================================================================================================================================

                                                        dynamic time warping 

												            ��̬ʱ�����

	�㷨˼�룺  ����ʱ������֮��ľ��룬ʱ�����еĵ����Ϊ����ʸ��������ʱ�����еĳ��ȿ��Բ�ͬ

	���裺1��  ���������󣬾����ijλ���ϵ�ֵΪ����1�ĵ�i������ʸ��������2�ĵ�j������ʸ���ľ��룬��ʱ�ľ������Ϊŷ�Ͼ��룬�����پ����
	      
		  2�� ���ݾ�������ʼ���ۻ��������ĵ�0�����0��

		  3�� �����ۻ���������ijλ���ϵ�ֵ�����һ��Ԫ�ص�ֵ��Ϊʱ������֮��ľ���

		  4�� �ҳ����·����������֮���ӳ���ϵ


	Ӧ�ã�������ʶ��ϵͳ������ģ��ƥ�䷨����ѵ��ģ�ͽ׶Σ��û����ʻ���еĵ���˵һ�飬��ȡMFCC�������У���Ϊ�ôʻ��ģ�壬����ģ��⡣ʶ��׶Σ�����һ��
	      �µ���Ҫʶ��Ĵʣ�ͬ����ȡMFCC�������У�Ȼ�����DTW�㷨��ģ����ÿһ��ģ�����ƥ�䣬������룬�����̾����Ӧ��ģ�弴Ϊʶ��Ľ����


   input file1.txt��
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
		D += (ct[i]-cr[i])*(ct[i]-cr[i]) ; // ����Ϊ���ͣ�������
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