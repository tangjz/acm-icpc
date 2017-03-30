#include <cstdio>
#include <bitset>
#include <vector>
#include <algorithm>
typedef std::pair<int, int> Edge;
const int maxn = 5001, INF = 0x3f3f3f3f;
int n, m, t, deg[maxn], que[maxn], L, R, sz, out[maxn];
std::vector<Edge> e[maxn];
struct Node {
	int val, pre;
	Node() : val(INF), pre(0) {}
	Node(int val, int pre) : val(val), pre(pre) {}
	void upd(Node const &t) {
		if(val > t.val) {
			val = t.val;
			pre = t.pre;
		}
	}
} f[maxn][maxn];
int main()
{
	scanf("%d%d%d", &n, &m, &t);
	while(m--)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		e[u].push_back(std::make_pair(v, w));
		++deg[v];
	}
	for(int i = 1; i <= n; ++i)
		if(!deg[i])
			que[R++] = i;
	while(L < R)
	{
		int u = que[L++];
		for(std::vector<Edge>::iterator it = e[u].begin(); it != e[u].end(); ++it)
		{
			int v = it -> first;
			if(!(--deg[v]))
				que[R++] = v;
		}
	}
	f[1][1] = Node(0, 0);
	for(int o = 0; o < R; ++o)
	{
		int u = que[o];
		for(std::vector<Edge>::iterator it = e[u].begin(); it != e[u].end(); ++it)
		{
			int v = it -> first, w = it -> second;
			for(int i = 1; i <= n; ++i)
			{
				if(f[u][i].val == INF)
					continue;
				f[v][i + 1].upd(Node(f[u][i].val + w, u));
			}
		}
	}
	for(int i = n; i >= 1; --i)
		if(f[n][i].val <= t)
		{
			sz = i;
			break;
		}
	for(int i = n, j = sz; j > 0; i = f[i][j].pre, --j)
		out[j] = i;
	printf("%d\n", sz);
	for(int i = 1; i <= sz; ++i)
		printf("%d%c", out[i], " \n"[i == sz]);
	return 0;
}
