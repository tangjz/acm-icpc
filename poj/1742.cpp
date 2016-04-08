#include <cstdio>
#include <cstring>
const int maxn = 101, maxv = 100001;
int n, v, c[maxn], w[maxn], f[maxv], ans;
int main()
{
	while(scanf("%d%d", &n, &v) == 2 && n + v)
	{
		ans = 0;
		memset(f, -1, sizeof f);
		for(int i = 0; i < n; ++i)
			scanf("%d", c + i);
		for(int i = 0; i < n; ++i)
			scanf("%d", w + i);
		f[0] = 0;
		for(int i = 0; i < n; ++i)
			for(int j = 0; j <= v; ++j)
				if(f[j] >= 0)
					f[j] = w[i];
				else if(j >= c[i] && f[j - c[i]] > 0)
					f[j] = f[j - c[i]] - 1;
		for(int i = 1; i <= v; ++i)
			if(f[i] >= 0)
				++ans;
		printf("%d\n", ans);
	}
	return 0;
}