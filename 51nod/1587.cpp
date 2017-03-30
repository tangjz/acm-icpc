#include <stdio.h>
#include <cstring>
const int maxd = 53, maxs = 1001, maxo = 25001, maxc = 10, mod = 1000000007;
struct Trie {
	int nxt[maxc + 1], fail;
	bool ban;
} e[maxo];
int d, num[maxd], tot, que[maxo], L, R, f[maxd][maxo], ans;
char str[maxs], buf[maxd];
int solve()
{
	int ret = 0, rt = 0;
	for(int i = d - 1; i >= 0; --i)
		ret = (10LL * ret + num[i]) % mod;
	for(int i = d - 2; i >= 0; --i)
		for(int j = 1; j < maxc; ++j)
			if((ret -= f[i][e[0].nxt[j]]) < 0)
				ret += mod;
	for(int i = d - 1; i >= 0; --i)
	{
		for(int j = i == d - 1; j < num[i]; ++j)
		{
			int v = rt;
			for( ; v && !e[v].nxt[j]; v = e[v].fail);
			v = e[v].nxt[j];
			if((ret -= f[i][v]) < 0)
				ret += mod;
		}
		for( ; rt && !e[rt].nxt[num[i]]; rt = e[rt].fail);
		rt = e[rt].nxt[num[i]];
		if(e[rt].ban)
			break;
	}
	return ret;
}
int main()
{
	scanf("%s%s", str, buf);
	d = strlen(buf);
	for(int i = 0, slen = strlen(str), tlen = d >> 1; i <= slen - tlen; ++i)
	{
		int rt = 0;
		for(int j = 0; j < tlen; ++j)
		{
			if(!e[rt].nxt[(int)(str[i + j] - '0')])
				rt = e[rt].nxt[(int)(str[i + j] - '0')] = ++tot;
			else
				rt = e[rt].nxt[(int)(str[i + j] - '0')];
		}
		e[rt].ban = 1;
	}
	for(int i = 0; i < maxc; ++i)
		if(e[0].nxt[i])
			que[R++] = e[0].nxt[i];
	while(L < R)
		for(int i = 0, u = que[L++]; i < maxc; ++i)
		{
			if(!e[u].nxt[i])
				continue;
			int v = e[u].nxt[i], w = e[u].fail;
			que[R++] = v;
			for( ; w && !e[w].nxt[i]; w = e[w].fail);
			e[v].fail = w = e[w].nxt[i];
			e[v].ban |= e[w].ban;
		}
	for(int i = 0; i <= tot; ++i)
		f[0][i] = !e[i].ban;
	for(int i = 1; i <= d; ++i)
		for(int u = 0; u <= tot; ++u) if(!e[u].ban)
			for(int j = 0; j < maxc; ++j)
			{
				int v = u;
				for( ; v && !e[v].nxt[j]; v = e[v].fail);
				v = e[v].nxt[j];
				if((f[i][u] += f[i - 1][v]) >= mod)
					f[i][u] -= mod;
			}
	for(int i = 0; i < d; ++i)
		num[i] = buf[d - 1 - i] - '0';
	ans = mod - solve();
	scanf("%s", buf);
	for(int i = 0; i < d; ++i)
		num[i] = buf[d - 1 - i] - '0';
	++num[0];
	for(int i = 0; i < d && num[i] >= maxc; ++i)
	{
		num[i] -= maxc;
		++num[i + 1];
	}
	if(num[d])
		++d;
	if((ans += solve()) >= mod)
		ans -= mod;
	printf("%d\n", ans);
	return 0;
}
