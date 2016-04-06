#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 300001, maxs = 26;
int t, n, pos[maxn], tot, in[maxn], out[maxn], seg[maxn << 1], ans;
struct Trie
{
	int fa, ch[maxs], fail;
} e[maxn];
char str[maxn];
void insert(int idx)
{
	int o = 0;
	scanf("%s", str);
	for(int i = 0; str[i]; ++i)
	{
		str[i] -= 'a';
		if(!e[o].ch[str[i]])
		{
			memset(e + tot, 0, sizeof(e[0]));
			e[o].ch[str[i]] = tot;
			e[tot++].fa = o;
		}
		o = e[o].ch[str[i]];
	}
	pos[idx] = o;
}
void build()
{
	int *que = in, L = 0, R = 0;
	for(int i = 0; i < maxs; ++i)
		if(e[0].ch[i])
			que[R++] = e[0].ch[i];
	while(L < R)
	{
		int &u = que[L++];
		for(int i = 0; i < maxs; ++i)
		{
			if(!e[u].ch[i])
				continue;
			int &v = e[u].ch[i], k = e[u].fail;
			while(k && !e[k].ch[i])
				k = e[k].fail;
			e[v].fail = k = e[k].ch[i];
			que[R++] = v;
		}
	}
}
vector<int> g[maxn];
void dfs(int u)
{
	in[u] = ++tot;
	for(vector<int>::iterator it = g[u].begin(); it != g[u].end(); ++it)
		dfs(*it);
	out[u] = tot;
}
inline void upd(int &x, int y)
{
	if(x < y)
		x = y;
}
inline int seg_idx(int L, int R)
{
	return L + R | L != R;
}
void update(int L, int R, int l, int r, int x)
{
	int o = seg_idx(L, R);
	if(l <= L && R <= r)
	{
		upd(seg[o], x);
		return;
	}
	int M = L + R >> 1;
	if(l <= M)
		update(L, M, l, r, x);
	if(r > M)
		update(M + 1, R, l, r, x);
}
int query(int L, int R, int x)
{
	int o = seg_idx(L, R);
	if(L == R)
		return seg[o];
	int M = L + R >> 1;
	return max(x <= M ? query(L, M, x) : query(M + 1, R, x), seg[o]);
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		tot = 0;
		memset(e + (tot++), 0, sizeof(e[0]));
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i)
			insert(i);
		build();
		for(int i = 0; i < tot; ++i)
			g[i].clear();
		for(int i = 1; i < tot; ++i)
			g[e[i].fail].push_back(i);
		tot = 0;
		dfs(0);
		ans = 0;
		memset(seg, 0, (tot + 1 << 1) * sizeof(int));
		for(int i = 1; i <= n; ++i)
		{
			int mx = 0;
			for(int j = pos[i]; j; j = e[j].fa)
				upd(mx, query(1, tot, in[j]));
			upd(ans, ++mx);
			update(1, tot, in[pos[i]], out[pos[i]], mx);
		}
		printf("%d\n", ans);
	}
	return 0;
}
