/*
 * AC自动机+容斥，算出不包含任意一个串的答案，用26^m减 
 */
#include <cstdio>
const int maxn = 6001, maxlen = 101, maxsize = 26, mod = 10007;
struct AC
{
	int ch[maxsize], fail, last;
	bool val;
} trie[maxn];
int n, m, tot, que[maxn], l, r, f[maxlen][maxn], ans;
char s[maxlen];
void insert()
{
	scanf("%s", s);
	int now = 0;
	for(int i = 0; s[i]; ++i)
	{
		s[i] -= 'A';
		if(!trie[now].ch[s[i]]) trie[now].ch[s[i]] = ++tot;
		now = trie[now].ch[s[i]];
	}
	trie[now].val = 1;
}
void bfs()
{
	for(int i = 0; i < maxsize; ++i)
		if(trie[0].ch[i]) que[r++] = trie[0].ch[i];
	while(l != r)
	{
		int now = que[l++];
		for(int i = 0; i < maxsize; ++i)
			if(trie[now].ch[i])
			{
				int u = trie[now].ch[i], v = trie[now].fail;
				que[r++] = u;
				if(r >= maxn) r = 0;
				while(v && !trie[v].ch[i]) v = trie[v].fail;
				trie[u].fail = v = trie[v].ch[i];
				trie[u].last = trie[v].val ? v : trie[v].last;
			}
	}
}
int pow(int x, int k)
{
	int ret = 1;
	while(k)
	{
		if(k & 1) ret = ret * x % mod;
		x = x * x % mod;
		k >>= 1;
	}
	return ret;
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; ++i)
		insert();
	bfs();
	f[0][0] = 1;
	for(int i = 0; i < m; ++i)
		for(int j = 0; j <= tot; ++j)
			if(f[i][j])
				for(int k = 0; k < maxsize; ++k)
				{
					int v = j;
					while(v && !trie[v].ch[k]) v = trie[v].fail;
					v = trie[v].ch[k];
					if(!trie[v].val && !trie[v].last)
					{
						f[i + 1][v] += f[i][j];
						if(f[i + 1][v] >= mod) f[i + 1][v] -= mod;
					}
				}
	for(int i = 0; i <= tot; ++i)
	{
		ans += f[m][i];
		if(ans >= mod) ans -= mod;
	}
	ans = pow(maxsize, m) - ans;
	if(ans < 0) ans += mod;
	printf("%d\n", ans);
	return 0;
}
