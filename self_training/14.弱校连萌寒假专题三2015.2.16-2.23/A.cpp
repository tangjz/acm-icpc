#include <cstdio>
#include <cstring>
const int maxn = 1001, maxv = 1001;
int t, n, v, f[maxv], c[maxn], w[maxn];
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		memset(f, 0, sizeof f);
		scanf("%d%d", &n, &v);
		for(int i = 1; i <= n; ++i)
			scanf("%d", w + i);
		for(int i = 1; i <= n; ++i)
			scanf("%d", c + i);
		for(int i = 1; i <= n; ++i)
			for(int j = v; j >= c[i]; --j)
				if(f[j] < f[j - c[i]] + w[i])
					f[j] = f[j - c[i]] + w[i];
		printf("%d\n", f[v]);
	}
	return 0;
}
