#include <cstdio>
const int maxn = 50001;
int n, k, fa[maxn * 3], ans;
int find(int x)
{
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}
int main()
{
	scanf("%d%d", &n, &k);
	ans = 0;
	for(int i = 1; i <= n * 3; ++i)
		fa[i] = i;
	while(k--)
	{
		int d, x, y;
		scanf("%d%d%d", &d, &x, &y);
		if(x > n || y > n)
		{
			++ans;
			continue;
		}//同类			被吃				吃
		int fx1 = find(x), fx2 = find(x + n), fx3 = find(x + n + n);
		int fy1 = find(y), fy2 = find(y + n), fy3 = find(y + n + n);
		if(d == 1)
		{
			if(fx1 == fy2 || fx1 == fy3 || fy1 == fx2 || fy1 == fx3)
			{
				++ans;
				continue;
			}
			fa[find(fx1)] = find(fy1);
			fa[find(fx2)] = find(fy2);
			fa[find(fx3)] = find(fy3);
		}
		else
		{
			if(fx1 == fy1 || fx1 == fy3 || fx2 == fy1)
			{
				++ans;
				continue;
			}
			fa[find(fx1)] = find(fy2);
			fa[find(fx2)] = find(fy3);
			fa[find(fx3)] = find(fy1);
		}
	}
	printf("%d\n", ans);
	return 0;
}
