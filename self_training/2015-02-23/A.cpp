#include <deque>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 40001, maxs = 4;
int n, m, k, qsize, tot, cnt, seq[maxn];
char str[maxn][maxs];
deque<int> Q;
bool flag;
int main()
{
	char op[10];
	scanf("%d%d%d", &n, &m, &k);
	while(n--)
	{
		scanf("%s", str[tot++]);
		Q.push_front(tot - 1);
		++qsize;
	}
	while(qsize > k)
	{
		seq[cnt++] = Q.front();
		Q.pop_front();
		--qsize;
	}
	while(m--)
	{
		scanf("%s", op);
		if(op[0] == 'R')
			flag ^= 1;
		else
		{
			for(int i = 5; op[i]; ++i)
				if(op[i] == ')')
					op[i] = '\0';
			strcpy(str[tot++], op + 4);
			if(flag)
			{
				Q.push_front(tot - 1);
				++qsize;
				if(qsize > k)
				{
					seq[cnt++] = Q.back();
					Q.pop_back();
					--qsize;
				}
			}
			else
			{
				Q.push_back(tot - 1);
				++qsize;
				if(qsize > k)
				{
					seq[cnt++] = Q.front();
					Q.pop_front();
					--qsize;
				}
			}
		}
	}
	if(flag)
		while(qsize)
		{
			seq[cnt++] = Q.back();
			Q.pop_back();
			--qsize;
		}
	else
		while(qsize)
		{
			seq[cnt++] = Q.front();
			Q.pop_front();
			--qsize;
		}
	for(int i = cnt - 1; i >= 0; --i)
		printf("%s\n", str[seq[i]]);
	return 0;
}
