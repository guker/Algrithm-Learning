/*
                               �ο����㷨���ۡ�


һ��B��T�Ǿ����������ʵ��и���(��Ϊroot[T])��
1��ÿ�����x��������
a��n[x]����ǰ�洢�ڽ��x�еĹؼ��ָ����� 
b��n[x]���ؼ��ֱ����Էǽ����ţ����key1 [x]��key2[x]�ܡ���keyn[x][x]��
c��leaf[x]����һ������ֵ�����x��Ҷ�ӽ��Ļ�������ΪTRUE�����xΪһ���ڽ�㣬����ΪFALSE��
2��ÿ���ڽ��x������n[x]+1��ָ������Ů��ָ��c1[x]��c2[x]������cn[x]+1[x]��Ҷ���û����Ů�������ǵ�ci���޶��塣
3�����ؼ���Keyi[x]�Դ洢�ڸ������еĹؼ��ַ�Χ���Էָ������kiΪ�洢����ci[x]Ϊ���������еĹؼ��֣���k1��key1[x]��k2��key2[x]�ܡ���keyn[x][x]��kn[x]+1
4��ÿ��Ҷ��������ͬ����ȣ������ĸ߶�h��
5��ÿһ������ܰ����Ĺؼ�������һ���Ͻ���½硣��Щ�����һ������B������С��������һ������п�ָ��ĺ��ӽ��������Ĺ̶�����t��2����ʾ��
a��ÿ���Ǹ��Ľ�����������t-1���ؼ��֣�ÿ���Ǹ����ڽ�����������t����Ů��������Ƿǿյģ����������ٰ���һ���ؼ��֡�
b��ÿ�����ɰ�������2t-1���ؼ��֡�����һ���ڽ���������2t����Ů������˵һ����������ģ������ǡ����2t-1���ؼ��֡�
*/

#pragma once  
template<class T>  
class CBTree  
{  
private:  
	static const int M = 3;                  //B������С����  
	static const int KEY_MAX = 2*M-1;        //�ڵ�����ؼ��ֵ�������  
	static const int KEY_MIN = M-1;          //�Ǹ��ڵ�����ؼ��ֵ���С����  
	static const int CHILD_MAX = KEY_MAX+1;  //���ӽڵ��������  
	static const int CHILD_MIN = KEY_MIN+1;  //���ӽڵ����С����  
	struct Node  
	{  
		bool isLeaf;             //�Ƿ���Ҷ�ӽڵ�  
		int keyNum;              //�ڵ�����Ĺؼ�������  
		T keyValue[KEY_MAX];     //�ؼ��ֵ�ֵ����  
		Node *pChild[CHILD_MAX]; //����ָ������  

		Node(bool b=true, int n=0)  
			:isLeaf(b), keyNum(n){}  
	};  
public:  
	CBTree()  
	{  
		m_pRoot = NULL;  //����һ�ÿյ�B��  
	}  

	~CBTree()  
	{  
		clear();  
	}  

	bool insert(const T &key)    //��B���в����½��key  
	{  
		if (contain(key))  //���ùؼ����Ƿ��Ѿ�����  
		{  
			return false;  
		}  
		else  
		{  
			if (m_pRoot==NULL)//����Ƿ�Ϊ����  
			{  
				m_pRoot = new Node();  
			}  
			if (m_pRoot->keyNum==KEY_MAX) //�����ڵ��Ƿ�����  
			{  
				Node *pNode = new Node();  //�����µĸ��ڵ�  
				pNode->isLeaf = false;  
				pNode->pChild[0] = m_pRoot;  
				splitChild(pNode, 0, m_pRoot);  
				m_pRoot = pNode;  //���¸��ڵ�ָ��  
			}  
			insertNonFull(m_pRoot, key);  
			return true;  
		}  
	}  

	bool remove(const T &key)    //��B��ɾ�����key  
	{  
		if (!search(m_pRoot, key))  //������  
		{  
			return false;  
		}  
		if (m_pRoot->keyNum==1)//�����������  
		{  
			if (m_pRoot->isLeaf)  
			{  
				clear();  
				return true;  
			}  
			else  
			{  
				Node *pChild1 = m_pRoot->pChild[0];  
				Node *pChild2 = m_pRoot->pChild[1];  
				if (pChild1->keyNum==KEY_MIN&&pChild2->keyNum==KEY_MIN)  
				{  
					mergeChild(m_pRoot, 0);  
					deleteNode(m_pRoot);  
					m_pRoot = pChild1;  
				}  
			}  
		}  
		recursive_remove(m_pRoot, key);  
		return true;  
	}  
	void display()const //��ӡ���Ĺؼ���  
	{  
		displayInConcavo(m_pRoot,KEY_MAX*10);  
	}  
	bool contain(const T &key)const   //����key�Ƿ������B����  
	{  
		return search(m_pRoot, key);  
	}  
	void clear()                      //���B��  
	{  
		recursive_clear(m_pRoot);  
		m_pRoot = NULL;  
	}  
private:  
	//ɾ����  
	void recursive_clear(Node *pNode)  
	{  
		if (pNode!=NULL)  
		{  
			if (!pNode->isLeaf)  
			{  
				for(int i=0; i<=pNode->keyNum; ++i)  
					recursive_clear(pNode->pChild[i]);  
			}  
			deleteNode(pNode);  
		}  
	}  

	//ɾ���ڵ�  
	void deleteNode(Node *&pNode)  
	{  
		if (pNode!=NULL)  
		{  
			delete pNode;  
			pNode = NULL;  
		}  
	}  

	//���ҹؼ���  
	bool search(Node *pNode, const T &key)const   
	{  
		if (pNode==NULL)  //���ڵ�ָ���Ƿ�Ϊ�գ���ýڵ��Ƿ�ΪҶ�ӽڵ�  
		{  
			return false;  
		}  
		else  
		{  
			int i;  
			for (i=0; i<pNode->keyNum && key>*(pNode->keyValue+i); ++i)//�ҵ�ʹkey<=pNode->keyValue[i]��������С�±�i  
			{  
			}  
			if (i<pNode->keyNum && key==pNode->keyValue[i])  
			{  
				return true;  
			}  
			else  
			{  
				if (pNode->isLeaf)   //���ýڵ��Ƿ�ΪҶ�ӽڵ�  
				{  
					return false;  
				}  
				else  
				{  
					return search(pNode->pChild[i], key);  
				}  
			}  
		}  
	}  

	//�����ӽڵ�  
	void splitChild(Node *pParent, int nChildIndex, Node *pChild)    
	{  
		//��pChild���ѳ�pLeftNode��pChild�����ڵ�  
		Node *pRightNode = new Node();//���Ѻ���ҽڵ�  
		pRightNode->isLeaf = pChild->isLeaf;  
		pRightNode->keyNum = KEY_MIN;  
		int i;  
		for (i=0; i<KEY_MIN; ++i)//�����ؼ��ֵ�ֵ  
		{  
			pRightNode->keyValue[i] = pChild->keyValue[i+CHILD_MIN];  
		}  
		if (!pChild->isLeaf)  //�������Ҷ�ӽڵ㣬�������ӽڵ�ָ��  
		{  
			for (i=0; i<CHILD_MIN; ++i)  
			{  
				pRightNode->pChild[i] = pChild->pChild[i+CHILD_MIN];  
			}  
		}  

		pChild->keyNum = KEY_MIN;  //�����������Ĺؼ��ָ���  

		for (i=pParent->keyNum; i>nChildIndex; --i)//�����ڵ��е�nChildIndex������йؼ��ֵ�ֵ������ָ�������һλ  
		{  
			pParent->pChild[i+1] = pParent->pChild[i];  
			pParent->keyValue[i] = pParent->keyValue[i-1];  
		}  
		++pParent->keyNum;  //���¸��ڵ�Ĺؼ��ָ���  
		pParent->pChild[nChildIndex+1] = pRightNode;  //�洢������ָ��  
		pParent->keyValue[nChildIndex] = pChild->keyValue[KEY_MIN];//�ѽڵ���м�ֵ�ᵽ���ڵ�  
	}  

	//�ڷ����ڵ��в���ؼ���  
	void insertNonFull(Node *pNode, const T &key)  
	{  
		int i = pNode->keyNum;  //��ȡ�ڵ��ڹؼ��ָ���  
		if (pNode->isLeaf)      //pNode��Ҷ�ӽڵ�  
		{  
			while (i>0&&key<pNode->keyValue[i-1])   //�Ӻ���ǰ�����ҹؼ��ֵĲ���λ��  
			{  
				pNode->keyValue[i] = pNode->keyValue[i-1];  //�����λ  
				--i;  
			}  
			pNode->keyValue[i] = key;  //����ؼ��ֵ�ֵ  
			++pNode->keyNum; //���½ڵ�ؼ��ֵĸ���  
		}  
		else//pNode���ڽڵ�  
		{  
			while(i>0&&key<pNode->keyValue[i-1])   //�Ӻ���ǰ�����ҹؼ��ֵĲ��������  
				--i;  
			Node *pChild = pNode->pChild[i];  //Ŀ���������ָ��   
			if (pChild->keyNum==KEY_MAX)  //�����ڵ�����  
			{  
				splitChild(pNode, i, pChild);//���������ڵ�  
				if(key>pNode->keyValue[i])   //ȷ��Ŀ������  
					pChild = pNode->pChild[i+1];  
			}  
			insertNonFull(pChild, key);  //����ؼ��ֵ�Ŀ�������ڵ�  
		}  
	}  

	//�����Ŵ�ӡ��  
	void displayInConcavo(Node *pNode, int count)const  
	{  
		if (pNode!=NULL)  
		{  
			int i, j;  
			for (i=0; i<pNode->keyNum; ++i)  
			{  
				if (!pNode->isLeaf)  
				{  
					displayInConcavo(pNode->pChild[i], count-2);  
				}  
				for (j=count; j>=0; --j)  
				{  
					cout<<"-";  
				}  
				cout<<pNode->keyValue[i]<<endl;  
			}  
			if (!pNode->isLeaf)  
			{  
				displayInConcavo(pNode->pChild[i], count-2);  
			}  
		}  
	}  

	//�ϲ������ӽڵ�  
	void mergeChild(Node *pParent, int index)  
	{  
		Node *pChild1 = pParent->pChild[index];  
		Node *pChild2 = pParent->pChild[index+1];  
		//��pChild2���ݺϲ���pChild1  
		pChild1->keyNum = KEY_MAX;  
		pChild1->keyValue[KEY_MIN] = pParent->keyValue[index];//�����ڵ�index��ֵ����  
		int i;  
		for (i=0; i<KEY_MIN; ++i)  
		{  
			pChild1->keyValue[i+KEY_MIN+1] = pChild2->keyValue[i];  
		}  
		if (!pChild1->isLeaf)  
		{  
			for (i=0; i<CHILD_MIN; ++i)  
			{  
				pChild1->pChild[i+CHILD_MIN] = pChild2->pChild[i];  
			}  
		}  

		//���ڵ�ɾ��index��key��index�����ǰ��һλ  
		--pParent->keyNum;  
		for(i=index; i<pParent->keyNum; ++i)  
		{  
			pParent->keyValue[i] = pParent->keyValue[i+1];  
			pParent->pChild[i+1] = pParent->pChild[i+2];  
		}  
		deleteNode(pChild2);  //ɾ��pChild2  
	}  

	//�ݹ��ɾ���ؼ���  
	void recursive_remove(Node *pNode, const T &key)  
	{  
		int i=0;  
		while(i<pNode->keyNum&&key>pNode->keyValue[i])  
			++i;  
		if (i<pNode->keyNum&&key==pNode->keyValue[i])//�ؼ���key�ڽڵ�pNode��  
		{  
			if (pNode->isLeaf)//pNode�Ǹ�Ҷ�ڵ�  
			{  
				//��pNode��ɾ��k  
				--pNode->keyNum;  
				for (; i<pNode->keyNum; ++i)  
				{  
					pNode->keyValue[i] = pNode->keyValue[i+1];  
				}  
				return;  
			}  
			else//pNode�Ǹ��ڽڵ�  
			{  
				Node *pChildPrev = pNode->pChild[i];//�ڵ�pNode��ǰ��key���ӽڵ�  
				Node *pChildNext = pNode->pChild[i+1];//�ڵ�pNode�к���key���ӽڵ�  
				if (pChildPrev->keyNum>=CHILD_MIN)//�ڵ�pChildPrev�����ٰ���CHILD_MIN���ؼ���  
				{  
					T prevKey = getPredecessor(pChildPrev); //��ȡkey��ǰ���ؼ���  
					recursive_remove(pChildPrev, prevKey);  
					pNode->keyValue[i] = prevKey;     //�滻��key��ǰ���ؼ���  
					return;  
				}  
				else if (pChildNext->keyNum>=CHILD_MIN)//�ڵ�pChildNext�����ٰ���CHILD_MIN���ؼ���  
				{  
					T nextKey = getSuccessor(pChildNext); //��ȡkey�ĺ�̹ؼ���  
					recursive_remove(pChildNext, nextKey);  
					pNode->keyValue[i] = nextKey;     //�滻��key�ĺ�̹ؼ���  
					return;  
				}  
				else//�ڵ�pChildPrev��pChildNext�ж�ֻ����CHILD_MIN-1���ؼ���  
				{  
					mergeChild(pNode, i);  
					recursive_remove(pChildPrev, key);  
				}  
			}  
		}  
		else//�ؼ���key���ڽڵ�pNode��  
		{  
			Node *pChildNode = pNode->pChild[i];//����key���������ڵ�  
			if (pChildNode->keyNum==KEY_MIN)//ֻ��t-1���ؼ���  
			{  
				Node *pLeft = i>0 ? pNode->pChild[i-1] : NULL;  //���ֵܽڵ�  
				Node *pRight = i<pNode->keyNum ? pNode->pChild[i+1] : NULL;//���ֵܽڵ�  
				int j;  
				if (pLeft&&pLeft->keyNum>=CHILD_MIN)//���ֵܽڵ�������CHILD_MIN���ؼ���  
				{  
					//���ڵ���i-1�Ĺؼ���������pChildNode��  
					for (j=pChildNode->keyNum; j>0; --j)    
					{  
						pChildNode->keyValue[j] = pChildNode->keyValue[j-1];  
					}  
					pChildNode->keyValue[0] = pNode->keyValue[i-1];  

					if (!pLeft->isLeaf)    
					{  
						for (j=pChildNode->keyNum+1; j>0; --j) //pLeft�ڵ��к��ʵ���Ůָ����ֲ��pChildNode��  
						{  
							pChildNode->pChild[j] = pChildNode->pChild[j-1];  
						}  
						pChildNode->pChild[0] = pLeft->pChild[pLeft->keyNum];  
					}  
					++pChildNode->keyNum;  
					pNode->keyValue[i] = pLeft->keyValue[pLeft->keyNum-1];//pLeft�ڵ��е����ؼ���������pNode��  
					--pLeft->keyNum;  
				}  
				else if (pRight&&pRight->keyNum>=CHILD_MIN)//���ֵܽڵ�������CHILD_MIN���ؼ���  
				{  
					//���ڵ���i�Ĺؼ���������pChildNode��  
					pChildNode->keyValue[pChildNode->keyNum] = pNode->keyValue[i];  
					++pChildNode->keyNum;  
					pNode->keyValue[i] = pRight->keyValue[0];//pRight�ڵ��е���С�ؼ���������pNode��  
					--pRight->keyNum;  
					for (j=0; j<pRight->keyNum; ++j)  
					{  
						pRight->keyValue[j] = pRight->keyValue[j+1];  
					}  
					if (!pRight->isLeaf)    
					{  
						pChildNode->pChild[pChildNode->keyNum] = pRight->pChild[0];//pRight�ڵ��к��ʵ���Ůָ����ֲ��pChildNode��  
						for (j=0; j<=pRight->keyNum; ++j)  
						{  
							pRight->pChild[j] = pRight->pChild[j+1];  
						}  
					}  
				}  
				//�����ֵܽڵ㶼ֻ����CHILD_MIN-1���ڵ�  
				else if (pLeft)//�����ֵܺϲ�  
				{  
					mergeChild(pNode, i-1);  
					pChildNode = pLeft;  
				}  
				else if (pRight)//�����ֵܺϲ�  
				{  
					mergeChild(pNode, i);  

				}  
			}  
			recursive_remove(pChildNode, key);  
		}  
	}  

	T getPredecessor(Node *pNode)//�ҵ�ǰ���ؼ���  
	{  
		while (!pNode->isLeaf)  
		{  
			pNode = pNode->pChild[pNode->keyNum];  
		}  
		return pNode->keyValue[pNode->keyNum-1];  
	}  

	T getSuccessor(Node *pNode)//�ҵ���̹ؼ���  
	{  
		while (!pNode->isLeaf)  
		{  
			pNode = pNode->pChild[0];  
		}  
		return pNode->keyValue[0];  
	}  

private:  
	Node * m_pRoot;  //B���ĸ��ڵ�  
}; 