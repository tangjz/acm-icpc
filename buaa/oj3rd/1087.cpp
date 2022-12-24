#include <cstdio>
#include <cstring>
const int maxn = 1010, maxw = 50, maxsize = 10, maxs = 33;
int n, m, tot;
struct AC
{
	int ch[maxsize], fail, last, val;
} trie[maxw];
void insert(int no)
{
	int x, now = 0, len = 0, num[10] = {};
	scanf("%d", &x);
	while(x)
	{
		num[len++] = x % 10;
		x /= 10;
	}
	for(int i = len - 1; i >= 0; --i)
	{
		if(!trie[now].ch[num[i]])
			trie[now].ch[num[i]] = ++tot;
		now = trie[now].ch[num[i]];
	}
	trie[now].val = no;
}
void build()
{
	int que[maxn], l = 0, r = 0;
	for(int i = 0; i < maxsize; ++i)
		if(trie[0].ch[i])
			que[r++] = trie[0].ch[i];
	while(l != r)
		for(int i = 0, now = que[l++]; i < maxsize; ++i)
			if(trie[now].ch[i])
			{
				int u = trie[now].ch[i], v = trie[now].fail;
				que[r++] = u;
				if(r >= maxw)
					r = 0;
				while(v && !trie[v].ch[i])
					v = trie[v].fail;
				trie[u].fail = v = trie[v].ch[i];
				trie[u].last = trie[v].val ? v : trie[v].last;
				trie[u].val = trie[u].val ? trie[u].val : trie[trie[u].last].val;
			}
}
int SD(int o, int r, int z)
{
	return (o * maxn + r) * maxs + z;
}
void DS(const int &id, int &s, int &t, int &q)
{
	s = id / maxs / maxn;
	t = id / maxs % maxn;
	q = id % maxs;
}
int l, r, que[maxw * maxn * maxs + 123], pre[maxw * maxn * maxs + 123][2], ans[maxw * maxn * maxs + 123], len;
bool f[maxw][maxn][maxs], flag;
int main()
{
	while(scanf("%d%d", &n, &m) == 2)
	{
		int maxk = 1 << m;
		tot = 0;
		memset(trie, 0, sizeof trie);
		for(int i = 1; i <= m; ++i)
			insert(i);
		build();
		memset(f, 0, sizeof f);
		l = r = flag = 0;
		f[0][0][0] = 1;
		que[r++] = SD(0, 0, 0);
		while(l < r)
		{
			int i, j, k;
			DS(que[l], i, j, k);
			for(int t = 0; t < maxsize; ++t)
			{
				int v = i, jj = (j * 10 + t) % n, kk = k;
				while(v && !trie[v].ch[t])
					v = trie[v].fail;
				if(trie[v].ch[t])
					v = trie[v].ch[t];
				for(int vv = v; trie[vv].val; vv = trie[vv].last)
					kk |= 1 << trie[vv].val - 1;
				if(!jj && kk + 1 == maxk)
				{
					pre[r][0] = l;
					pre[r][1] = t;
					que[r] = SD(v, jj, kk);
					flag = 1;
					break;
				}
				if(!f[v][jj][kk])
				{
					pre[r][0] = l;
					pre[r][1] = t;
					que[r++] = SD(v, jj, kk);
					f[v][jj][kk] = 1;
				}
				for(int vv = v; trie[vv].val; vv = trie[vv].last)
					if(!f[vv][jj][kk])
					{
						pre[r][0] = l;
						pre[r][1] = t;
						que[r++] = SD(vv, jj, kk);
						f[vv][jj][kk] = 1;
					}
			}
			if(flag)
				break;
			++l;
		}
		if(flag)
		{
			int i, j, k, jj;
			len = 0;
			while(r > 0)
			{
				ans[len++] = pre[r][1];
				r = pre[r][0];
			}
			for(i = len - 1; i >= 0; --i)
				printf("%d", ans[i]);
			putchar('\n');
		}
		else
			puts("-1");
	}
	return 0;
}
