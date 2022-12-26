#include <cstdio>
#include <cstring>
const int maxn = 101, maxt = 10001, maxv = 121, INF = 0x3f3f3f3f;
int n, t, lim, v[maxn], c[maxn], que[maxt + maxv * maxv][2], l, r, f[maxt + maxv * maxv], g[maxv * maxv], ans;
int main()
{
	scanf("%d%d", &n, &t);
	for(int i = 0; i < n; ++i)
	{
		scanf("%d", v + i);
		if(lim < v[i])
			lim = v[i];
	}
	for(int i = 0; i < n; ++i)
		scanf("%d", c + i);
	lim *= lim;
	t += lim;
	memset(f, 0x3f, sizeof f);
	memset(g, 0x3f, sizeof g);
	f[0] = g[0] = 0;
	for(int i = 0; i < n; ++i)
		for(int a = 0; a < v[i]; ++a)
		{
			l = r = 0;
			for(int j = 0; j * v[i] + a <= t; ++j)
			{
				int tmp = f[j * v[i] + a] - j;
				while(l < r && que[r - 1][1] >= tmp)
					--r;
				que[r][0] = j;
				que[r++][1] = tmp;
				f[j * v[i] + a] = que[l][1] + j;
				if(que[l][0] == j - c[i])
					++l;
			}
		}
	for(int i = 0; i < n; ++i)
		for(int j = v[i]; j <= lim; ++j)
			if(g[j] > g[j - v[i]] + 1)
				g[j] = g[j - v[i]] + 1;
	t -= lim;
	ans = INF;
	for(int i = 0; i <= lim; ++i)
		if(ans > f[t + i] + g[i])
			ans = f[t + i] + g[i];
	if(ans != INF)
		printf("%d\n", ans);
	else
		puts("-1");
	return 0;
}
