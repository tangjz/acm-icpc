#include <cstdio>
#include <cstring>
const int maxl = 21, maxn = 51, maxs = 1001, maxd = 26, mod = 1000003;
struct Trie {
	int fail, nxt[maxd];
	bool ban;
} e[maxs];
int n, sL, sR, tot, msk[maxs], trans[maxs], que[maxs], L, R;
int f[2][8][maxs], cur, pre = 1, ans;
char str[maxs], pat[maxs];
inline void mod_inc(int &x, int y)
{
	(x += y) >= mod && (x -= mod);
}
int main()
{
	for(int i = 0; i < 10; ++i)
	{
		msk[tot] = 1;
		trans[tot] = -1;
		pat[tot++] = '0' + i;
	}
	trans[0] = 'o' - 'a';
	trans[1] = 'i' - 'a';
	trans[3] = 'e' - 'a';
	trans[5] = 's' - 'a';
	trans[7] = 't' - 'a';
	for(int i = 0; i < 26; ++i)
	{
		msk[tot] = 2;
		trans[tot] = i;
		pat[tot++] = 'a' + i;
	}
	for(int i = 0; i < 26; ++i)
	{
		msk[tot] = 4;
		trans[tot] = i;
		pat[tot++] = 'A' + i;
	}
	pat[tot] = '\0';
	scanf("%d%d%d", &sL, &sR, &n);
	tot = 0;
	while(n--)
	{
		int rt = 0;
		scanf("%s", str);
		for(int i = 0; str[i]; ++i)
		{
			str[i] -= 'a';
			if(!e[rt].nxt[str[i]])
				e[rt].nxt[str[i]] = ++tot;
			rt = e[rt].nxt[str[i]];
		}
		e[rt].ban = 1;
	}
	for(int i = 0; i < 26; ++i)
		if(e[0].nxt[i])
			que[R++] = e[0].nxt[i];
	while(L < R)
	{
		int u = que[L++];
		for(int i = 0; i < 26; ++i)
		{
			if(!e[u].nxt[i])
				continue;
			int v = e[u].nxt[i], w = e[u].fail;
			for( ; w && !e[w].nxt[i]; w = e[w].fail);
			e[v].fail = w = e[w].nxt[i];
			e[v].ban |= e[w].ban;
			que[R++] = v;
		}
	}
	f[cur][0][0] = 1;
	for(int i = 1; i <= sR; ++i)
	{
		pre ^= 1;
		cur ^= 1;
		memset(f[cur], 0, sizeof f[0]);
		for(int j = 0; j < 8; ++j)
			for(int k = 0; k <= tot; ++k)
			{
				if(!f[pre][j][k])
					continue;
				for(int o = 0; pat[o]; ++o)
				{
					int kk = k;
					if(trans[o] != -1)
					{
						for( ; kk && !e[kk].nxt[trans[o]]; kk = e[kk].fail);
						kk = e[kk].nxt[trans[o]];
					}
					else
						kk = 0;
					if(!e[kk].ban)
						mod_inc(f[cur][j | msk[o]][kk], f[pre][j][k]);
				}
			}
		if(i >= sL)
			for(int j = 0; j <= tot; ++j)
				mod_inc(ans, f[cur][7][j]);
	}
	printf("%d\n", ans);
	return 0;
}
