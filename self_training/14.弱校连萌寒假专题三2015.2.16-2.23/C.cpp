#include <cstdio>
#include <cstring>
const int maxn = 501, maxv = 10001;
int t, n, v;
long long f[maxv], INF = 0x3f3f3f3f3f3f3f3fLL;
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		int c, w;
		scanf("%d%d%d", &c, &w, &n);
		v = w - c;
		memset(f, 0x3f, sizeof f);
		f[0] = 0;
		for(int i = 0; i < n; ++i)
		{
			scanf("%d%d", &w, &c);
			for(int j = c; j <= v; ++j)
				if(f[j] > f[j - c] + w)
					f[j] = f[j - c] + w;
		}
		if(f[v] == INF)
			puts("This is impossible.");
		else
			printf("The minimum amount of money in the piggy-bank is %d.\n", f[v]);
	}
	return 0;
}
