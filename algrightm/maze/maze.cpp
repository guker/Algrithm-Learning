#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
#include <time.h>

#define INIT_STACKSIZE 100
#define OK 1
#define TRUE 1
#define FALSE 0
#define ERROR -1
#define Abort(msg)   { printf("aborting:%s\n",msg);exit(0);}

typedef int Status;

typedef struct PosType{
        int r;   //row num
        int c;   //col num
}PosType;

typedef struct{
        int di;
        int ord;//�����
        PosType seat ;
}SElemType;
 
typedef struct{
        SElemType *top,*base;
        int stacksize;
}Stack;

typedef char ** MazeType; //[MAZESIZE][MAZESIZE];

Status Pass(MazeType MyMaze, PosType CurPos);
void FootPrint(MazeType &MyMaze, PosType CurPos);
void MarkPrint(MazeType &MyMaze, PosType CurPos);
PosType NextPos(PosType CurPos, int Dir);

int M,N;//gloable variable ,maze size: M*N

Status InitStack(Stack &S)
{
     S.base = (SElemType *)malloc(INIT_STACKSIZE * sizeof(SElemType));
     if(!S.base) Abort("malloc failed.");
     S.top=S.base;
     S.stacksize= INIT_STACKSIZE;
     return(OK);
}

Status StackEmpty(Stack S) 
{
	if(S.top==S.base)return (TRUE);
	else return (FALSE);
}

Status Push(Stack &S, SElemType e)
{
 if(S.top-S.base>=S.stacksize)
 {
  S.base=(SElemType*)realloc(S.base,(S.stacksize+10)*sizeof(SElemType));
  if(!S.base) Abort("OVERFLOW");
  S.top=S.base+S.stacksize;
  S.stacksize+=10;
 }
 *S.top=e; S.top++;
 return OK;
}//push

Status Pop(Stack &S, SElemType &e)
{
 if(S.top==S.base) return ERROR;
  e=*(--S.top);
 return OK;
}//Pop


Status MazePath(MazeType &maze, PosType start, PosType end,  Stack &S) {  
  // �㷨3.3
  // ��������Թ�maze�еĴ���� start������ end��һ��ͨ����
  // ��������ջ�У���ջ�׵�ջ������������TRUE��ʧ���򷵻�FALSE
  
  PosType curpos;
  int curstep;
  SElemType e;

  InitStack(S);
  curpos = start;  // �趨"��ǰλ��"Ϊ"���λ��"
  curstep = 1;     // ̽����һ��
  do {
    if (Pass(maze,curpos)) {  // ��ǰλ�ÿ�ͨ��������δ���ߵ�����ͨ����,�޼Ǻ�
	  printf("��ǰλ�ã�curpos.x=%d,curpos.y=%d\n",curpos.r,curpos.c);
      FootPrint(maze,curpos); // �����㼣�Ǻţ� �����ظ�����
      e.di =1;
      e.ord = curstep;
      e.seat= curpos;
      Push(S,e);              // ����·��ջ 
      if (curpos.r == end.r && curpos.c==end.c)  
        return (TRUE);        // �ж��������յ㣨���ڣ��򷵻�true 
      curpos = NextPos(curpos, 1);        // ��һλ���ǵ�ǰλ�õĶ���
      curstep++;                          // ̽����һ��
    } else {  // ��ǰλ�ò���ͨ��
      if (!StackEmpty(S)) {
        Pop(S,e);
        while (e.di==4 && !StackEmpty(S)) {
          MarkPrint(maze,e.seat);  //���²���ͨ���ı�ǣ�
          Pop(S,e);    // ���˻�һ��
        } // while
        if (e.di<4) {
          e.di++;
          Push(S, e);  // ����һ������̽��
          curpos = NextPos(e.seat, e.di); // ��ǰλ����Ϊ�·�������ڿ�
        } // if (e.di<4) 
      } // if(!StackEmpty(S))-else ��ջ�ղ�����whileѭ������� 
    } // else  //��ǰλ�ò���ͨ��
  } while (!StackEmpty(S) );
  return FALSE;
} // MazePath

Status Pass( MazeType MyMaze,PosType CurPos) {
  if (CurPos.r>=0 && CurPos.r<M && CurPos.c>=0 &&CurPos.c<N )
	 if (MyMaze[CurPos.r][CurPos.c]==' ')
	      return 1;     // �����ǰλ���ǿ���ͨ��������1
  return 0;  // �����������0
}

void FootPrint(MazeType &MyMaze,PosType CurPos) {
  MyMaze[CurPos.r][CurPos.c]='*';
}

void MarkPrint(MazeType &MyMaze,PosType CurPos) {
  MyMaze[CurPos.r][CurPos.c]='!';
}

PosType NextPos(PosType CurPos, int Dir) {
  PosType ReturnPos; 
  switch (Dir) {
    case 1:
        ReturnPos.r=CurPos.r;
        ReturnPos.c=CurPos.c+1;
        break;
    case 2:
        ReturnPos.r=CurPos.r+1;
        ReturnPos.c=CurPos.c;
        break;
    case 3:
        ReturnPos.r=CurPos.r;
        ReturnPos.c=CurPos.c-1;
        break;
    case 4:
        ReturnPos.r=CurPos.r-1;
        ReturnPos.c=CurPos.c;
        break;
  }
  return ReturnPos;
}

Status MakeMaze(MazeType &maze )
{//mazeΪ��ά�ַ����顣�ո� �������ͨ��'x'�����ϰ���
//��������λ����·���������·������'e'/'s'/'w'/'n'��������/��/��/����
	int i,j;
	char * p;
	maze = (MazeType)malloc(M* sizeof(char *));
	if (!maze) Abort("MEM OVERFLOW");
	p=(char *)malloc(M*N*sizeof(char));
	if (!p) Abort("MEM OVERFLOW");
	for(i=0;i<M;i++)
		maze[i]=p + i*N;

	srand((unsigned)time(NULL));
	for(i=0;i<M;i++)
		for(j=0;j<N;j++)
		{
			if (0==rand()%4)
				maze[i][j]='x';//'x'
			else
				maze[i][j]=' ';
		}
    maze[0][0]=maze[M-1][N-1]=' ';//�����յ�
	return OK;

}

 void PrintMaze(MazeType &maze,Stack S )
{
 SElemType e;
 printf("��%d��\n",(int )( S.top-S.base) );
 printf("ջ�������(����) : ");
 
 while(!StackEmpty(S))
 {
   int n;
   Pop(S,e);
   n=e.di;  
   switch(n)
   {
   case 1: maze[e.seat.r][e.seat.c]='e';putchar('e');break;
   case 2: maze[e.seat.r][e.seat.c]='s';putchar('s');break;
   case 3: maze[e.seat.r][e.seat.c]='w';putchar('w');break;
   case 4: maze[e.seat.r][e.seat.c]='n';putchar('n');break;
   }//switch
 }//while
 printf("\n");
 for(int i=0;i<M;++i)
 {
  for(int j=0;j<N;++j)
  {
	  switch(maze[i][j])
	  {
		case 'x': printf("%2s","��");break;//ǽ 
		case '!': printf("%2s","!"); break;//����·�� 
		case 'e': printf("%2s","��");break;//�� 
		case 's': printf("%2s","��");break;//���� 
		case 'w': printf("%2s","��");break;//���� 
		case 'n': printf("%2s","��");break;//�� 
		case '*': printf("%2s","��");break;//�����Ľ�ӡ 
		default: printf("%2s"," ");//δ����˴� 
	  }//switch
  }//for
  printf("\n");
 }//for
} 

int main(int argc, char* argv[])
//�����в���������������  �磺puzzle.exe 30 30 
{
	MazeType maze;
	Stack mystack;
	PosType start,end;
	//int col,row;
	
	M = atoi(argv[1]);
	N = atoi(argv[2]);
	if( (argc <3)  ||(M <=0) ||N <=0 )  
		Abort("command format error.");

	MakeMaze(maze );

	start.c = start.r = 0;
	end.c=N-1; 	
	end.r=M-1;
	
	if(MazePath(maze, start, end,mystack))
		PrintMaze(maze, mystack);
	else 
		{
			printf("route not found.\n");
			PrintMaze(maze, mystack);
	}

	getchar();
	return 0;
}