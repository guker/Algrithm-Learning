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

/// KMP
void get_next(const std::string& T, std::vector<int>& next)
{
	next.resize(T.size());
	int i = 0,j = -1;
	next[0] = -1;
	int len = T.length();
	while(i != len-1)
	{
		if(j == -1 || T[i] == T[j])
		{
			++i,++j;
			next[i] = j;
		}
		else
			j = next[j];
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
	std::string str = "huqunwei";
	std::string p = "wei";

	int index = kmp(str,p);

	return true;
}
