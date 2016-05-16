#include <cstdio>
#include <cstring>
const int maxn = 201, maxv = 501;
int n, v, c[maxn], w[maxn], lim[maxn], pre, cur, f[2][maxn * maxv], que[maxn * maxv], L, R, ans;
int main()
{
	pre = 1;
	cur = 0;
	while(scanf("%d", &n) == 1)
	{
		v = ans = 0;
		for(int i = 0; i < n; ++i)
		{
			int &p = w[i], &m = c[i], l, h;
			scanf("%d%d%d%d", &p, &m, &l, &h);
			v -= l * c[i];
			ans += l * w[i];
			lim[i] = h - l;
		}
		memset(f[cur] + 1, 0xf0, v * sizeof(int));
		for(int i = 0, j, k; i < n; ++i)
			for(j = 0, pre ^= 1, cur ^= 1; j < c[i]; ++j)
				for(k = L = R = 0; k * c[i] + j <= v; ++k)
				{
					while(L < R && f[pre][que[R - 1] * c[i] + j] + (k - que[R - 1]) * w[i] <= f[pre][k * c[i] + j])
						--R;
					que[R++] = k;
					f[cur][k * c[i] + j] = f[pre][que[L] * c[i] + j] + (k - que[L]) * w[i];
					if(que[L] + lim[i] == k)
						++L;
				}
		printf("%d\n", ans + f[cur][v]);
	}
	return 0;
}
