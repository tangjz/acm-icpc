#include <cstdio>
#include <cstring>
#include <algorithm>
typedef long long LL;
const int maxn = 20, maxs = 160, seed = 487237, delta = 1011807, mod = 1 << maxn;
int sz[mod], nxt[mod], lnk[mod], tot, seq[mod];
struct Edge
{
	int nxt, v;
} e[mod];
void addEdge(int u, int v)
{
	e[tot] = (Edge){lnk[u], v};
	lnk[u] = tot++;
}
int main()
{
	nxt[0] = delta;
	for(int i = 1; i < mod; ++i)
	{
		sz[i] = sz[i >> 1] + (i & 1);
		nxt[i] = ((LL)seed * i + delta) & (mod - 1);
	}
	int val = 0, mask = 0;
	for(int i = 0; i < maxn; ++i)
	{
		mask = (mask << 1) | (sz[val] & 1);
		val = nxt[val];
	}
	memset(lnk, -1, sizeof lnk);
	addEdge(mask, val);
	for(int i = 1; i < mod; ++i)
	{
		mask = (mask << 1) | (sz[val] & 1);
		if(mask >= mod)
			mask -= mod;
		val = nxt[val];
		addEdge(mask, val);
	}
	int pre, cur;
	mask = 0;
	scanf("%d", &pre);
	for(int i = 0; i < maxn; ++i)
	{
		printf("%d\n", 1);
		fflush(stdout);
		scanf("%d", &cur);
		if(cur == -1)
			return 0;
		mask = mask << 1 | (cur > pre);
		pre = cur;
	}
	tot = 0;
	for(int it = lnk[mask]; it != -1; it = e[it].nxt)
		seq[tot++] = e[it].v;
	for(int tt = 0; tt < 200; ++tt)
	{
		int tcnt = 0;
		for(int i = 0; i < tot; ++i)
			if(sz[seq[i]] & 1)
				++tcnt;
		if(tcnt == tot)
			printf("%d\n", pre);
		else
			printf("%d\n", 1);
		fflush(stdout);
		scanf("%d", &cur);
		if(cur == -1)
			break;
		tcnt = 0;
		for(int i = 0; i < tot; ++i)
			if((sz[seq[i]] & 1) == (pre < cur))
				seq[tcnt++] = seq[i];
		tot = tcnt;
		for(int i = 0; i < tot; ++i)
			seq[i] = nxt[seq[i]];
		pre = cur;
	}
	return 0;
}
