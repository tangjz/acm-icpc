#include <map>
#include <string>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 17, maxm = 101, maxs = 25;
map<string, int> idx;
int n, sz[maxn], bit[maxn][maxs], m, tot, seq[maxn];
char nam[maxn][maxm][maxs], str[maxs];
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
	{
		scanf("%s%d", str, sz + i);
		idx[str] = i;
		memset(bit[i], -1, sizeof bit[0]);
		for(int j = 0; j < sz[i]; ++j)
		{
			scanf("%s%s", str, nam[i][j]);
			for(int k = 0; str[k]; ++k)
				if(str[k] == '.' && bit[i][k] == -1)
					bit[i][k] = j;
		}
	}
	scanf("%d", &m);
	while(m--)
	{
		scanf("%d", &tot);
		for(int i = 0; i < tot; ++i)
		{
			scanf("%s", str);
			seq[i] = idx[str];
		}
		int tim;
		for(tim = 0; tim < 24; ++tim)
		{
			bool chk = 1;
			for(int j = 0; j < tot && chk; ++j)
				chk &= bit[seq[j]][tim] != -1;
			if(chk)
				break;
		}
		if(tim == 24)
			puts("No");
		else
		{
			printf("Yes");
			for(int i = 0; i < tot; ++i)
				printf(" %s", nam[seq[i]][bit[seq[i]][tim]]);
			putchar('\n');
		}
	}
	return 0;
}
