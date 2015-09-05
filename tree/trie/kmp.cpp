/*
*--------------------------------------KMP---------------------------------------
*  最长前后缀
*               / -1 , j = 0; 
*    next[j] = | max{k|0<k<j and p(0)p(1)...p(k-1) = p(j-k)....p(j-1)};
*              \ 0,other;
* 
*  模式串"abaabcac"
*     j   0 1 2 3 4 5 6 7
*     p   a b a a b c a c
*next[j] -1 0 0 1 1 2 0 1
* 
*   
*   next数组的初始条件是next[0]=-1,设next[j]=k，k表示index为j的最大前后缀长度，刻画了
*   p(0)...p(j-1)串的对称程度
*
*   那么next[j+1]有两种情况：
*   1. p(k) == p(j)
*       此时next[j+1] = next[j]+1; 
*   
*   2. p(k) != p(j)(note：采用递推方法)
*       此时需要将P向右滑动之后继续比较P中index为j的字符与index为next[k]的字符
*       如果p(next[k])=p(j),则next[j+1]=next[k]+1;
*       否则，继续将P向右滑动，直至匹配成功，或者不存在这样的匹配，此时next[j+1]=0;
*
*---------------------------------------------------------------------------------
*/
#include <string>
#include <vector>

///朴素匹配
int index(const std::string &S, const std::string &T,  int pos  = 0)
{
    int i = pos, j = 0;
    int slen = S.length();
    int tlen = T.length();

    if (slen < 1 || tlen < 1 || pos < 0)
    {
        return -1;
    }

    while (i != slen && j != tlen)
    {
        if (S[i] == T[j])
        {
            ++i;
            ++j;
        }
        else
        {
            i = i - j + 1;
            j = 0;
        }
    }
    return j == tlen? i - j: -1;
}

/// next数组 
void get_next(const std::string& T, std::vector<int>& next)
{
	next.resize(T.size());
	int i = 0,j = -1;
	next[0] = -1;
	int len = T.length();
	while(i != len - 1)
	{   
		/// i == 0时实际上求得是next[1]的值
		if(j == -1 || T[i] == T[j])
		{
			++i,++j;
			next[i] = j;
		}
		else
			j = next[j];  // T[i] != T[j]
	}
}

int kmp(const std::string& S, const std::string& T, int pos = 0)
{
	int i = pos;
	int j = 0;
	std::vector<int> next(T.size());
	get_next(T,next);

	int slen = S.length();
	int tlen = T.length();
	while( i != slen && j != tlen)
	{
		if(j == -1 || S[i] == T[j])
		{
			++i;
			++j;
		}
		else j = next[j];
	}

	return j == tlen? i-j:-1;
}



int main()
{
	std::string str = "aaaabaabcacdd";
	std::string p = "abaabcac";

	int index = kmp(str,p);

	return true;
}