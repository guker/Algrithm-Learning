/*
*     异或指针双向链表
* 
* 一般的双向链表节点中包含两个指针，分别指向前驱和后继，异或指针双向链表的节点只有一个指针
* 这个指针是前驱与后继的异或值，并利用一下运算得到前驱和后继的指针
* a^(a^b) = b
* (a^b)^b = a
*
* C语言中，可以先把指针转换成无符号整型数然后进行异或，另外还应保存链表头尾节点的指针
*/

#include<iostream>

using namespace std;

#define NUM 6

typedef struct XorNode
{
    char data;
    struct XorNode *LRPtr;      
}XorNode, *XorPointer;

typedef struct
{
    XorPointer l, r;//分别指向双向链表的左端和右端
}XorLinkedList;

//异或运算
XorPointer XorP(XorPointer p, XorPointer q)
{
    return (XorPointer)((unsigned)p^(unsigned)q);         
}

  
//建立异或指针双向链表
bool initList(XorLinkedList *pList, char value[NUM]){
     if(NUM<1)
       return false;
       
     XorPointer pl, p, pr;
     int i=0;
     
     p=(XorPointer)malloc(sizeof(XorPointer));
     if(!p)
       return false;
     pl=p;
     p->data=value[i++];
     pList->l=p;
     pr=NULL;   
     for(; i<NUM; ++i){
       pr=(XorPointer)malloc(sizeof(XorPointer));
       if(!p)
         return false;
       pr->data=value[i];
       p->LRPtr=XorP(pl, pr);
       pl=p;
       p=pr;
     }
     pList->r=p;
     if(pr!=NULL)
       p->LRPtr=XorP(pl, pr);
     return true;
}
 
//销毁异或指针双向链表
void destroy(XorLinkedList *pList){
     XorPointer m, n, p;   
     XorPointer head=pList->l;
     XorPointer tail=pList->r;
     
     m=n=head;
     while(n!=tail){
       p=XorP(m, n->LRPtr);
       cout<<n->data<<" ";
       free(n);//释放n指向的内容，但n的值本身不变
       m=n;
       n=p;
     }
     cout<<n->data<<" ";
     free(n);
     cout<<endl;
}

 
//遍历异或指针双向链表
void traverse(const XorLinkedList *pList, char direction)
{
     XorPointer m, n, p;
     XorPointer head=(direction=='l')?pList->l:pList->r;
     XorPointer tail=(direction=='r')?pList->l:pList->r;
 
     m=n=head;
     cout<<m->data;
     while(n!=tail)
	 {
       p=XorP(m, n->LRPtr);// 获取当前结点的指针
       cout<<p->data;
       m=n;
       n=p;
     }

}