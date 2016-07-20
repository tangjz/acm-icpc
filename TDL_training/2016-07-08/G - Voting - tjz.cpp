#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 10010, maxp = 4, maxt = 21, maxo = 1771;

int n, m, p, f[maxn][maxp];
vector<int> e[maxn];

typedef struct { int a, b, c; } Status;
int idx[maxt][maxt][maxt];
Status status[maxo];

typedef struct { int pre, val; } Node;
int tot, lnk[maxn], nxt[maxn];
Node h[maxn][maxo];
inline void upd(Node a[], int x, Node b[], int y, int val)
{
	if(a[x].val == -1 || a[x].val > b[y].val + val)
		a[x] = (Node){y, b[y].val + val};
}
inline void upd(int &x, int y)
{
	if(x == -1 || x > y)
		x = y;
}
void dfs(int u)
{
	if(!e[u].size())
	{
		// printf("%d : %d %d %d %d\n", u, f[u][0], f[u][1], f[u][2], f[u][3]);
		return;
	}
	for(vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it)
	{
		int &v = *it;
		dfs(v);
		Node *pre_h = h[lnk[u]], *cur_h = h[tot];
		for(int i = 0; i < maxo; ++i)
		{
			if(pre_h[i].val == -1 || p == 2 && status[i].c > 0)
				continue;
			int a = status[i].a, b = status[i].b, c = status[i].c;
			if(f[v][0] != -1)
				upd(cur_h, idx[a][b][c], pre_h, i, f[v][0]);
			if(f[v][1] != -1)
				upd(cur_h, idx[a + 1][b][c], pre_h, i, f[v][1]);
			if(f[v][2] != -1)
				upd(cur_h, idx[a][b + 1][c], pre_h, i, f[v][2]);
			if(p == 3 && f[v][3] != -1)
				upd(cur_h, idx[a][b][c + 1], pre_h, i, f[v][3]);
		}
		nxt[tot] = lnk[u];
		lnk[u] = tot++;
	}
	Node *cur_h = h[lnk[u]];
	for(int i = 0; i < maxo; ++i)
	{
		if(cur_h[i].val == -1 || p == 2 && status[i].c > 0)
			continue;
		int a = status[i].a, b = status[i].b, c = status[i].c;
		int mx = max(a, max(b, c)), cnt = (mx == a) + (mx == b) + (mx == c);
		if(cnt > 1)
			upd(f[u][0], cur_h[i].val);
		else if(mx == a)
			upd(f[u][1], cur_h[i].val);
		else if(mx == b)
			upd(f[u][2], cur_h[i].val);
		else if(p == 3)
			upd(f[u][3], cur_h[i].val);
	}
	// printf("%d : %d %d %d %d\n", u, f[u][0], f[u][1], f[u][2], f[u][3]);
}

pair<int, int> out[maxn];
void pfs(int u, int sel)
{
	if(!e[u].size())
	{
		if(f[u][sel])
			out[tot++] = make_pair(u, sel);
		return;
	}
	int cur_pos = -1, it = lnk[u];
	Node *cur_h = h[lnk[u]], *pre_h;
	for(int i = 0; i < maxo && cur_pos == -1; ++i)
	{
		if(cur_h[i].val == -1 || p == 2 && status[i].c > 0)
			continue;
		int a = status[i].a, b = status[i].b, c = status[i].c;
		int mx = max(a, max(b, c)), cnt = (mx == a) + (mx == b) + (mx == c);
		if(sel == 0)
		{
			if(cnt > 1 && cur_h[i].val == f[u][sel])
				cur_pos = i;
		}
		else if(sel == 1)
		{
			if(cnt == 1 && mx == a && cur_h[i].val == f[u][sel])
				cur_pos = i;
		}
		else if(sel == 2)
		{
			if(cnt == 1 && mx == b && cur_h[i].val == f[u][sel])
				cur_pos = i;
		}
		else if(p == 3)
		{
			if(cnt == 1 && mx == c && cur_h[i].val == f[u][sel])
				cur_pos = i;
		}
	}
	reverse(e[u].begin(), e[u].end());
	for(vector<int>::iterator iter = e[u].begin(); iter != e[u].end(); ++iter)
	{
		cur_h = h[it];
		pre_h = h[nxt[it]];
		int pre_pos = cur_h[cur_pos].pre;
		int a = status[cur_pos].a - status[pre_pos].a;
		int b = status[cur_pos].b - status[pre_pos].b;
		int c = status[cur_pos].c - status[pre_pos].c;
		if(!a && !b && !c)
			pfs(*iter, 0);
		else if(a)
			pfs(*iter, 1);
		else if(b)
			pfs(*iter, 2);
		else if(p == 3)
			pfs(*iter, 3);
		it = nxt[it];
		cur_pos = pre_pos;
	}
}
int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	// init status
	for(int i = 0; i < maxt; ++i)
		for(int j = 0; i + j < maxt; ++j)
			for(int k = 0; i + j + k < maxt; ++k)
			{
				status[tot] = (Status){i, j, k};
				idx[i][j][k] = tot++;
			}
	// init data
	scanf("%d%d%d", &n, &m, &p);
	memset(f, -1, sizeof f);
	for(int i = 1, x; i <= n; ++i)
	{
		scanf("%d", &x);
		for(int j = 0; j <= p; ++j)
			f[i][j] = j == x ? 0 : 1;
	}
	for(int i = 1, s, x; i <= m; ++i)
	{
		scanf("%d", &s);
		while(s--)
		{
			scanf("%d", &x);
			x = x < 0 ? n - x : x;
			e[n + i].push_back(x);
			// printf("%d -> %d\n", n + i, x);
		}
	}
	// dp
	tot = 1;
	memset(h, -1, sizeof h);
	h[0][0].val = 0;
	// memset(lnk, -1, sizeof lnk);
	dfs(n + 1);
	// output
	tot = 0;
	pfs(n + 1, 1);
	printf("%d\n", f[n + 1][1]);
	for(int i = 0; i < tot; ++i)
		printf("%d %d\n", out[i].first, out[i].second);
	return 0;
}
