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
        int ord;//步骤号
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
  // 算法3.3
  // 穷举搜索迷宫maze中的从入口 start到出口 end的一条通道，
  // 结果存放在栈中（从栈底到栈顶），并返回TRUE；失败则返回FALSE
  
  PosType curpos;
  int curstep;
  SElemType e;

  InitStack(S);
  curpos = start;  // 设定"当前位置"为"入口位置"
  curstep = 1;     // 探索第一步
  do {
    if (Pass(maze,curpos)) {  // 当前位置可通过，即是未曾走到过的通道块,无记号
	  printf("当前位置：curpos.x=%d,curpos.y=%d\n",curpos.r,curpos.c);
      FootPrint(maze,curpos); // 留下足迹记号， 避免重复搜索
      e.di =1;
      e.ord = curstep;
      e.seat= curpos;
      Push(S,e);              // 加入路径栈 
      if (curpos.r == end.r && curpos.c==end.c)  
        return (TRUE);        // 判定若到达终点（出口）则返回true 
      curpos = NextPos(curpos, 1);        // 下一位置是当前位置的东邻
      curstep++;                          // 探索下一步
    } else {  // 当前位置不能通过
      if (!StackEmpty(S)) {
        Pop(S,e);
        while (e.di==4 && !StackEmpty(S)) {
          MarkPrint(maze,e.seat);  //留下不能通过的标记，
          Pop(S,e);    // 并退回一步
        } // while
        if (e.di<4) {
          e.di++;
          Push(S, e);  // 换下一个方向探索
          curpos = NextPos(e.seat, e.di); // 当前位置设为新方向的相邻块
        } // if (e.di<4) 
      } // if(!StackEmpty(S))-else 若栈空不处理，while循环会结束 
    } // else  //当前位置不能通过
  } while (!StackEmpty(S) );
  return FALSE;
} // MazePath

Status Pass( MazeType MyMaze,PosType CurPos) {
  if (CurPos.r>=0 && CurPos.r<M && CurPos.c>=0 &&CurPos.c<N )
	 if (MyMaze[CurPos.r][CurPos.c]==' ')
	      return 1;     // 如果当前位置是可以通过，返回1
  return 0;  // 其它情况返回0
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
{//maze为二维字符数组。空格‘ ’代表可通，'x'代表障碍；
//搜索后若位置在路径中则标明路径方向'e'/'s'/'w'/'n'，即“东/南/西/北”
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
    maze[0][0]=maze[M-1][N-1]=' ';//起点和终点
	return OK;

}

 void PrintMaze(MazeType &maze,Stack S )
{
 SElemType e;
 printf("共%d步\n",(int )( S.top-S.base) );
 printf("栈里的内容(逆序) : ");
 
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
		case 'x': printf("%2s","■");break;//墙 
		case '!': printf("%2s","!"); break;//错误路径 
		case 'e': printf("%2s","→");break;//向东 
		case 's': printf("%2s","↓");break;//向南 
		case 'w': printf("%2s","←");break;//向西 
		case 'n': printf("%2s","↑");break;//向北 
		case '*': printf("%2s","☆");break;//到过的脚印 
		default: printf("%2s"," ");//未到达此处 
	  }//switch
  }//for
  printf("\n");
 }//for
} 

int main(int argc, char* argv[])
//命令行参数：行数和列数  如：puzzle.exe 30 30 
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