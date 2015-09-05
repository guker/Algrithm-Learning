/*
trie图用于解决多模式匹配问题。设有N个长度不超过L的模式串，匹配串长为M，那么用trie图解决多模式匹配问题的复杂度为O(N*L+M).

思路:

trie图的基础是trie树。

1.用trie树实现多模式匹配

　　首先建立N个模式串的trie树。设匹配串为s，我们枚举匹配起始位置i，在trie树中依次去查询字典中是否有字符串&str[i]的前缀。
　　这样做的复杂度为O(M*L).

2.用trie图实现多模式匹配

　　对于上述用trie树实现多模式匹配的方式，当我们沿trie树匹配的过程中找不到当前字符对应的边的时候，我们的做法是改变起始位置i的
　　值，从trie树根节点从头再来。

　　但其实此时我们已经从s的当前起始点i开始成功匹配了k个字符，那么我们在枚举下一个起点i+1的时候，意味着前k-1个字符已经在
　　上一次枚举中匹配过了，就像kmp算法一样，如果我们能利用好这个信息，就能大大的减小时间复杂度。

2.1后缀节点的概念

　　假设从根节点到当前节点A的路径所对应的字符串为"abcde"，那么"bcde"所对应的路径末节点就是节点A的后缀节点。但是，
　　trie树中可能并不存在"bcde"这样一条从根节点开始的路径，此时A的后缀节点是"bcde"的后缀节点，即后缀节点的后缀节点，如此递归。
　　特别的，根节点的后缀节点为根节点，深度为1的节点的后缀节点也为根节点。

2.2后缀节点的求法

　　采用广度优先遍历来求解后缀节点，这样，当我们要求trie树中第i层节点的后缀节点的时候，第0~i-1层的所有点的后缀节点都已知了。
　　我们可以根据父节点来求当前节点的后缀节点：假设父节点到当前节点的边为ch，那么当前节点的后缀节点就是父节点的后缀节点通过ch
　　这样一条边所到达的节点。然而，父节点的后缀节点有可能并不存在ch这样一条边，此时，我们需要看后缀节点的后缀节点是否存在ch
　　这样一条边，如此递归。但是，如果我们每次都这样递归来做未免显得有些麻烦，所以，在bfs的时候，对于每个节点，我们用一个数组
　　记录下从当前节点经过每一个ch所到达的节点，这里的“到达”的理解：当存在ch边的时候，就是一般意义的到达，当不存在ch边的时候，
　　这里的“到达”应该理解为其后缀节点经过ch这样一条边所到达的节点。如此一来，后缀节点的求解就很简单了。

　　还有一个问题需要注意：当当前节点不存在匹配字符所对应的边即不匹配的时候，我们直接跳转到其后缀节点，然后继续往下匹配，
　　我们这种做法会可能造成一种后果：那就是从根节点到后缀节点的路径中可能存在标记节点，而被我们忽略了。
　　解决这个问题的方法是“在求解当前后缀节点的过程中，若求得的后缀节点是标记节点，那么当前节点也要被标记”。

2.3实现多模式匹配

　　求得了所有的后缀节点，相当于我们的trie图已经构建完毕了。此时，多模式匹配问题，就只需要遍历匹配串，从trie树的根节点
　　开始逐个字符匹配，当匹配不成功的时候，就跳转到后缀节点继续匹配，直到匹配成功或者匹配串遍历结束。
*/

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
