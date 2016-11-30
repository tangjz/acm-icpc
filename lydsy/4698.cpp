#include <stdio.h>
const int maxn = 1001, maxm = 101;
int n, sz[maxn], a[maxn][maxm], f[maxn], ans;
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
	{
		scanf("%d", sz + i);
		for(int j = 0; j < sz[i]; ++j)
			scanf("%d", a[i] + j);
		--sz[i];
		for(int j = 1; j <= sz[i]; ++j)
			a[i][j - 1] -= a[i][j];
	}
	for(int dt = 0; dt + ans < sz[0]; ++dt)
	{
		int *pat = a[0] + dt, len = sz[0] - dt, tp = len;
		for(int i = 1, j = 0; i < len; f[++i] = j)
		{
			for( ; j && pat[j] != pat[i]; j = f[j]);
			if(pat[j] == pat[i])
				++j;
		}
		for(int k = 1; k < n; ++k)
		{
			int *tex = a[k], tl = 0;
			for(int i = 0, j = 0; i < sz[k]; ++i)
			{
				for( ; j && pat[j] != tex[i]; j = f[j]);
				if(pat[j] == tex[i] && tl < ++j)
					tl = j;
			}
			if(tp > tl)
				tp = tl;
		}
		if(ans < tp)
			ans = tp;
	}
	printf("%d\n", ++ans);
	return 0;
}
