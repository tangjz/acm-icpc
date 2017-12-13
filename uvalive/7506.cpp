#include <cmath>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
typedef double DB;
const int maxn = 201, maxm = 50001, maxq = 51;
int t, n, q, kk, w[maxn], sw, p[maxn], sz[maxn], size, ff[maxn], rt, tot, sum, seq[maxn], nxt[maxn];
DB c[maxq][maxq], pp[maxq], qq[maxq], f[maxn][maxm], s[maxm];
std::vector<int> e[maxn];
bool vis[maxn];
void find_center(int u, int fa) {
	sz[u] = 1;
	ff[u] = 0;
	for(std::vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it) {
		int v = *it;
		if(!vis[v] && v != fa) {
			find_center(v, u);
			sz[u] += sz[v];
			ff[u] = std::max(ff[u], sz[v]);
		}
	}
	ff[u] = std::max(ff[u], size - sz[u]);
	if(ff[u] < ff[rt])
		rt = u;
}
void get_order(int u, int fa) {
	int now = tot++;
	sum += w[u];
	seq[now] = u;
	for(std::vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it) {
		int v = *it;
		if(!vis[v] && v != fa)
			get_order(v, u);
	}
	nxt[now] = tot;
}
void solve(int u) {
	rt = 0;
	ff[0] = size;
	find_center(u, -1);
	u = rt;
	tot = sum = 0;
	get_order(u, -1);
	for(int i = 0; i <= tot; ++i)
		for(int j = 0; j <= sum; ++j)
			f[i][j] = 0;
	f[0][0] = 1;
	sum = 0;
	for(int i = 0; i < tot; ++i) {
		DB pr = (DB)p[seq[i]] / 100;
		for(int j = 0; j <= sum; ++j) {
			if(i)
				f[nxt[i]][j] += f[i][j];
			f[i + 1][j] += f[i][j] * (1 - pr);
			f[i + 1][j + w[seq[i]]] += f[i][j] * pr;
		}
		sum += w[seq[i]];
	}
	for(int i = 0; i <= sum; ++i)
		s[i] += f[tot][i];
	vis[u] = 1;
	for(std::vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it) {
		int v = *it;
		if(!vis[v]) {
			size = sz[v];
			solve(v);
		}
	}
}
int main() {
	for(int i = 0; i < maxq; ++i) {
		c[i][0] = c[i][i] = 1;
		for(int j = 1; j < i; ++j)
			c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
	}
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		scanf("%d%d%d", &n, &q, &kk);
		for(int i = 1; i <= n; ++i)
			std::vector<int>().swap(e[i]);
		for(int i = 1; i < n; ++i) {
			int u, v;
			scanf("%d%d", &u, &v);
			e[u].push_back(v);
			e[v].push_back(u);
		}
		sw = 0;
		for(int i = 1; i <= n; ++i) {
			scanf("%d", w + i);
			sw += w[i];
		}
		for(int i = 1; i <= n; ++i)
			scanf("%d", p + i);
		for(int i = 0; i <= sw; ++i)
			s[i] = 0;
		memset(vis + 1, 0, n * sizeof(bool));
		size = n;
		solve(1);
		for(int i = sw; i > 0; --i)
			s[i - 1] += s[i];
		DB ans = 0;
		for(int i = 1; i <= sw; ++i) {
			DB cur = 0;
			s[i] /= s[0];
			pp[0] = qq[0] = 1;
			for(int j = 1; j <= q; ++j) {
				pp[j] = pp[j - 1] * s[i];
				qq[j] = qq[j - 1] * (1 - s[i]);
			}
			for(int j = 0; j < kk; ++j)
				cur += pp[q - j] * qq[j] * c[q][j];
			ans += cur;
		}
		printf("Case #%d: %.10f\n", Case, (double)ans);
	}
	return 0;
}
