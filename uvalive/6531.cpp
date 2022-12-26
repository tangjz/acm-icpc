#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 100001, maxd = 17, delta = 150000;
int n, h[maxn][maxd], Log[maxn], que[maxn], top;
bool vis[maxn], first;
int rmq(int L, int R)
{
	int d = Log[R - L + 1];
	return min(h[L][d], h[R - (1 << d) + 1][d]);
}
int main()
{
	for(int i = 2; i < maxn; ++i)
		Log[i] = Log[i >> 1] + 1;
	while(scanf("%d", &n) == 1)
	{
		memset(vis, 0, sizeof vis);
		for(int i = 1; i <= n; ++i)
			scanf("%d", &h[i][0]);
		for(int i = 1; i <= Log[n]; ++i)
			for(int j = 1; j + (1 << i - 1) <= n; ++j)
				h[j][i] = min(h[j][i - 1], h[j + (1 << i - 1)][i - 1]);
		top = 0;
		for(int i = 1; i <= n; ++i)
		{
			while(top && h[que[top - 1]][0] <= h[i][0])
				--top;
			if(top && rmq(que[top - 1], i) > h[i][0] - delta)
				vis[i] = 1;
			que[top++] = i;
		}
		top = 0;
		for(int i = n; i; --i)
		{
			while(top && h[que[top - 1]][0] <= h[i][0])
				--top;
			if(top && rmq(i, que[top - 1]) > h[i][0] - delta)
				vis[i] = 1;
			que[top++] = i;
		}
		first = 0;
		for(int i = 1; i <= n; ++i)
			if(!vis[i])
			{
				if(first)
					putchar(' ');
				else
					first = 1;
				printf("%d", i);
			}
		putchar('\n');
	}
	return 0;
}
