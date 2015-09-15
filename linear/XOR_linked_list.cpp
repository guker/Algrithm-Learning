/*
*     ���ָ��˫������
* 
* һ���˫������ڵ��а�������ָ�룬�ֱ�ָ��ǰ���ͺ�̣����ָ��˫������Ľڵ�ֻ��һ��ָ��
* ���ָ����ǰ�����̵����ֵ��������һ������õ�ǰ���ͺ�̵�ָ��
* a^(a^b) = b
* (a^b)^b = a
*
* C�����У������Ȱ�ָ��ת�����޷���������Ȼ�����������⻹Ӧ��������ͷβ�ڵ��ָ��
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
    XorPointer l, r;//�ֱ�ָ��˫���������˺��Ҷ�
}XorLinkedList;

//�������
XorPointer XorP(XorPointer p, XorPointer q)
{
    return (XorPointer)((unsigned)p^(unsigned)q);         
}

  
//�������ָ��˫������
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
 
//�������ָ��˫������
void destroy(XorLinkedList *pList){
     XorPointer m, n, p;   
     XorPointer head=pList->l;
     XorPointer tail=pList->r;
     
     m=n=head;
     while(n!=tail){
       p=XorP(m, n->LRPtr);
       cout<<n->data<<" ";
       free(n);//�ͷ�nָ������ݣ���n��ֵ������
       m=n;
       n=p;
     }
     cout<<n->data<<" ";
     free(n);
     cout<<endl;
}

 
//�������ָ��˫������
void traverse(const XorLinkedList *pList, char direction)
{
     XorPointer m, n, p;
     XorPointer head=(direction=='l')?pList->l:pList->r;
     XorPointer tail=(direction=='r')?pList->l:pList->r;
 
     m=n=head;
     cout<<m->data;
     while(n!=tail)
	 {
       p=XorP(m, n->LRPtr);// ��ȡ��ǰ����ָ��
       cout<<p->data;
       m=n;
       n=p;
     }

}