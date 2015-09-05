/*
*------------------------------------AC自动机----------------------------------------------------
*  Aho-Corasick算法　　
*
*　使用Aho-Corasick算法需要三步：
*
*　1.建立模式的Trie
*    Trie树也是一种自动机。对于多模式集合{"say","she","shr","he","her"}，对应的Trie树如下，
*    其中红色标记的圈是表示为接收态
*
*　2.给Trie添加失败路径
*
*    构造失败指针的过程概括起来就一句话：设这个节点上的字母为C，沿着他父亲的失败指针走，直到走到一个节点，
*
*	 他的儿子中也有字母为C的节点。然后把当前节点的失败指针指向那个字母也为C的儿子。如果一直走到了root都没找到，
*
*	 那就把失败指针指向root
*
*	 使用广度优先搜索BFS，层次遍历节点来处理，每一个节点的失败路径。
*
*	 特殊处理：第二层要特殊处理，将这层中的节点的失败路径直接指向父节点(也就是根节点)。
*
*　3.根据AC自动机，搜索待处理的文本
*
*    从root节点开始，每次根据读入的字符沿着自动机向下移动。
*
*　　当读入的字符，在分支中不存在时，递归走失败路径。如果走失败路径走到了root节点，则跳过该字符，处理下一个字符。
*
*　　因为AC自动机是沿着输入文本的最长后缀移动的，所以在读取完所有输入文本后，最后递归走失败路径，直到到达根节点，这样可以检测出所有的模式。
*
*
*
*
*/
#include<iostream>
#include<string.h>
#include<malloc.h>
#include <queue>
using namespace std;

typedef struct node
{
    struct node *next[26];  //接收的态
    struct node *par;   //父亲节点
    struct node *fail;  //失败节点
    char inputchar;
    int patterTag;    //是否为可接收态
    int patterNo;   //接收态对应的可接受模式
}*Tree,TreeNode;

char pattern[4][30]={"nihao","hao","hs","hsr"};

/**
申请新的节点，并进行初始化
*/
TreeNode *getNewNode()
{
    int i;
    TreeNode* tnode=(TreeNode*)malloc(sizeof(TreeNode));
    tnode->fail=NULL;
    tnode->par=NULL;
    tnode->patterTag=0;
    for(i=0;i<26;i++)
        tnode->next[i]=NULL;
    return tnode;
}

/**
将Trie树中，root节点的分支节点，放入队列
*/
int  nodeToQueue(Tree root,queue<Tree> &myqueue)
{
    int i;
    for (i = 0; i < 26; i++)
    {
        if (root->next[i]!=NULL)
            myqueue.push(root->next[i]);
    }
    return 0;
}

/**
建立trie树
*/
Tree buildingTree()
{
    int i,j;
    Tree root=getNewNode();
    Tree tmp1=NULL,tmp2=NULL;
    for(i=0;i<4;i++)
    {
        tmp1=root;
        for(j=0;j<strlen(pattern[i]);j++)   ///对每个模式进行处理
        {
            if(tmp1->next[pattern[i][j]-'a']==NULL) ///是否已经有分支，Trie共用节点
            {
                tmp2=getNewNode();
                tmp2->inputchar=pattern[i][j];
                tmp2->par=tmp1;
                tmp1->next[pattern[i][j]-'a']=tmp2;
                tmp1=tmp2;
            }
            else
                tmp1=tmp1->next[pattern[i][j]-'a'];
        }
        tmp1->patterTag=1;
        tmp1->patterNo=i;
    }
    return root;
}

/**
建立失败指针
*/
int buildingFailPath(Tree root)
{
    int i;
    char inputchar;
    queue<Tree> myqueue;
    root->fail=root;
    for(i=0;i<26;i++)   ///对root下面的第二层进行特殊处理
    {
        if (root->next[i]!=NULL)
        {
            nodeToQueue(root->next[i],myqueue);
            root->next[i]->fail=root;
        }
    }

    Tree tmp=NULL,par=NULL;
    while(!myqueue.empty())
    {
        tmp=myqueue.front();
        myqueue.pop();
        nodeToQueue(tmp,myqueue);

        inputchar=tmp->inputchar;
        par=tmp->par;

        while(true)
        {
            if(par->fail->next[inputchar-'a']!=NULL)
            {
                tmp->fail=par->fail->next[inputchar-'a'];
                break;
            }
            else
            {
                if(par->fail==root)
                {
                    tmp->fail=root;
                    break;
                }
                else
                    par=par->fail->par;
            }
        }
    }
    return 0;
}

/**
进行多模式搜索，即搜寻AC自动机
*/
int searchAC(Tree root,char* str,int len)
{
    TreeNode *tmp=root;
    int i=0;
    while(i < len)
    {
        int pos=str[i]-'a';
        if (tmp->next[pos]!=NULL)
        {
            tmp=tmp->next[pos];
            if(tmp->patterTag==1)    ///如果为接收态
            {
                cout<<i-strlen(pattern[tmp->patterNo])+1<<'\t'<<tmp->patterNo<<'\t'<<pattern[tmp->patterNo]<<endl;
            }
            i++;
        }
        else
        {
            if(tmp==root)
                i++;
            else
            {
                tmp=tmp->fail;
                if(tmp->patterTag==1)    //如果为接收态
                    cout<<i-strlen(pattern[tmp->patterNo])+1<<'\t'<<tmp->patterNo<<'\t'<<pattern[tmp->patterNo]<<endl;
            }
        }
    }
    while(tmp!=root)
    {
        tmp=tmp->fail;
        if(tmp->patterTag==1)
            cout<<i-strlen(pattern[tmp->patterNo])+1<<'\t'<<tmp->patterNo<<'\t'<<pattern[tmp->patterNo]<<endl;
    }
    return 0;
}

/**
释放内存，DFS
*/
int destory(Tree tree)
{
    if(tree==NULL)
        return 0;
    queue<Tree> myqueue;
    TreeNode *tmp=NULL;

    myqueue.push(tree);
    tree=NULL;
    while(!myqueue.empty())
    {
        tmp=myqueue.front();
        myqueue.pop();

        for (int i = 0; i < 26; i++)
        {
            if(tmp->next[i]!=NULL)
                myqueue.push(tmp->next[i]);
        }
        free(tmp);
    }
    return 0;
}

int main()
{
    char a[]="sdmfhsgnshejfgnihaofhsrnihao";
    Tree root=buildingTree();   ///建立Trie树
    buildingFailPath(root); ///添加失败转移
    cout<<"待匹配字符串："<<a<<endl;
    cout<<"模式"<<pattern[0]<<" "<<pattern[1]<<" "<<pattern[2]<<" "<<pattern[3]<<" "<<endl<<endl;
    cout<<"匹配结果如下："<<endl<<"位置\t"<<"编号\t"<<"模式"<<endl;
    searchAC(root,a,strlen(a)); ///搜索
    destory(root);  ///释放动态申请内存
    return 0;
}