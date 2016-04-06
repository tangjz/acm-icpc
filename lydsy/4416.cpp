#include <cstdio>
#include <cstring>
const int maxn = 22, maxm = 456, maxs = 26;
int t, n, m, nxt[maxm][maxs], f[1 << maxn];
char s[maxs];
void upd(int &x, int y)
{
	if(x < y)
		x = y;
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%s", &n, s + 1);
		if(n > maxn)
		{
			puts("NO");
			continue;
		}
		m = strlen(s + 1);
		for(int i = 0; i < n; ++i)
			nxt[m + 1][i] = m + 1;
		for(int i = m; i > 0; --i)
		{
			memcpy(nxt[i], nxt[i + 1], sizeof nxt[0]);
			nxt[i][s[i] - 'a'] = i;
		}
		memcpy(nxt[0], nxt[1], sizeof nxt[0]);
		int all = 1 << n;
		for(int msk = 1; msk < all; ++msk)
		{
			f[msk] = 0;
			for(int i = 0; i < n; ++i)
				if(msk & (1 << i))
					upd(f[msk], nxt[f[msk ^ (1 << i)]][i]);
		}
		puts(f[all - 1] <= m ? "YES" : "NO");
	}
	return 0;
}
