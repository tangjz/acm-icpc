#include <cstdio>
const int maxn = 25;
int n, a[maxn], b[maxn], c[maxn], ans;
int main()
{
	while(scanf("%d", &n) == 1)
	{
		for(int i = 1; i <= n; ++i)
		{
			int x;
			scanf("%d", &x);
			a[x] = i;
		}
		for(int i = 1; i <= n; ++i)
			scanf("%d", b + i);
		for(int i = 1; i <= n; ++i)
			c[i] = a[b[i]];
		ans = 0;
		for(int i = 1; i <= n; ++i)
			for(int j = i + 1; j <= n; ++j)
				if(c[i] > c[j])
					++ans;
		printf("%d\n", ans);
	}
	return 0;
}
