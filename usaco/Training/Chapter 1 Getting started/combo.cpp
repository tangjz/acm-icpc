/*
ID: tangjin2
LANG: C++
TASK: combo
*/
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 101;
int n, a, b, c, ans;
bool vis[maxn][maxn][maxn];
int main()
{
	freopen("combo.in", "r", stdin);
	freopen("combo.out", "w", stdout);
	scanf("%d", &n);
	for(int i = 0; i < 2; ++i)
	{
		scanf("%d%d%d", &a, &b, &c);
		for(int d = 1; d <= n; ++d)
		{
			if(min(abs(a - d), n - abs(a - d)) > 2)
				continue;
			for(int e = 1; e <= n; ++e)
			{
				if(min(abs(b - e), n - abs(b - e)) > 2)
					continue;
				for(int f = 1; f <= n; ++f)
				{
					if(min(abs(c - f), n - abs(c - f)) > 2)
						continue;
					if(!vis[d][e][f])
					{
						vis[d][e][f] = 1;
						++ans;
					}
				}
			}
		}
	}
	printf("%d\n", ans);
	return 0;
}
