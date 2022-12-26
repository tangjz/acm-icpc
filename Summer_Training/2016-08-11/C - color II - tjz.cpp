#include <cstdio>
const int maxn = 18;
int t, n;
char e[maxn][maxn + 1], lbt[1 << maxn], f[1 << maxn];
bool can[1 << maxn];
inline void upd(char &x, char y)
{
	if(x > y)
		x = y;
}
int main()
{
	for(int i = 1; i < 1 << maxn; ++i)
		lbt[i] = i & 1 ? 0 : lbt[i >> 1] + 1;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		int all = 1 << n;
		for(int i = 0; i < n; ++i)
			scanf("%s", e[i]);
		can[0] = 1;
		for(int i = 1; i < all; ++i)
		{
			int u = lbt[i & -i];
			if(!(can[i] = can[i ^ (1 << u)]))
				continue;
			for(int j = u + 1; j < n; ++j)
				if((i & (1 << j)) && e[u][j] == '1')
				{
					can[i] = 0;
					break;
				}
		}
		f[0] = 0;
		unsigned int ans = 0, pw = 233u;
		for(int i = 1; i < all; ++i, pw *= 233u)
		{
			f[i] = n;
			for(int j = i; j; j = (j - 1) & i)
				if(can[j])
					upd(f[i], f[i ^ j] + 1);
			ans += f[i] * pw;
		}
		printf("%u\n", ans);
	}
	return 0;
}
