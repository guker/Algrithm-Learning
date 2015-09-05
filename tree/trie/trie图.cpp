#include<iostream>
#include<string>
#include<queue>
using namespace std;
//结点结构 
class Node
{ 
public:
	Node()
	{
		bad=false;
		prev=NULL;
		for(int i=0;i<26;i++)
		{
			next[i]=NULL;
		}
	}
	bool bad;//是否是终点
	Node *next[26] ;//26个字母
	Node *prev;//前缀结点 
};


class TrieTree
{
public:
	TrieTree()
	{
		root=new Node();
	} 
	void insert(string &word);
	void build();//创建Trie图 
	bool search(string &word);

private:
	Node *root;
};


void TrieTree::insert(string &word)
{
	Node *proot=root;
	for(unsigned int i=0; i<word.size(); i++)
	{
		if(proot->next[word.at(i)-'a']==NULL)
			proot->next[word.at(i)-'a']=new Node();
		proot=proot->next[word.at(i)-'a'];			
	}
	proot->bad=true;//单词结尾结点 
}
void TrieTree::build()
{
	queue<Node*> Q;
	Node *proot=root;
	//root->prev=root;//根节点的前缀还是根节点 
	for(int i=0;i<26;i++)//初始化第一层结点 
	{
		if(proot->next[i]!=NULL)
		{
			proot->next[i]->prev=root;//第一层结点的前缀是根节点 
			Q.push(proot->next[i]);//第一层结点入队 
		}
	}
	while(!Q.empty())
	{
		proot=Q.front();//返回第一个元素 
		Q.pop();//删除第一个元素 
		for(int i=0; i<26; i++)
		{
			Node *p=proot->next[i];
			if(p!=NULL&&p->bad==false)//有孩子  可以加上&&p->bad==false,也可以不加
			{
				Node *prev=proot->prev;//父结点的前缀结点
				while(prev)
				{
					if(prev->next[i]!=NULL)
					{
						p->prev=prev->next[i];//设置孩子结点的前缀结点 
						if(p->prev->bad==true)
							p->bad=true;
						break;
					}
					else
						prev=prev->prev;
				}

				if(p->prev==NULL)//如果没有前缀，最后指向根节点 
					p->prev=root; 				

				//if(p->bad==false)//如果p结点为坏结点，它的孩子其实就没必要判断了 
				Q.push(p);//队列中加入p 
			} //end if
		} //end for
	}//end while	
} 

bool TrieTree::search(string &word)
{
	unsigned int len=word.size();
	Node *proot=root;
	for(unsigned int i=0; i<len; i++)
	{
		while(true)
		{
			if(proot->next[word.at(i)-'a']!=NULL)
			{
				proot=proot->next[word.at(i)-'a'];
				if(proot->bad==true)
					return true;
				break;
			}
			else
				proot=proot->prev;
			if(proot==root||proot==NULL)
			{
				proot=root;
				break; 
			}

		}

	}
	return false;
}

int main()
{
	int N;
	TrieTree T;
	string s;//过滤单词 
	string sen;//文章 
	cin>>N;
	for(int i=0; i<N; i++)
	{
		cin>>s;
		T.insert(s);
	}
	T.build();//构建Trie图
	cin>>sen;
	bool test=T.search(sen);
	if(test)
		cout<<"YES"<<endl;
	else 
		cout<<"NO"<<endl;
	return 0;
}