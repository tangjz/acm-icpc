// luogu-judger-enable-o2
#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e5 + 1;
int n, lnk[maxn], deg[maxn], lim, f[maxn];
struct Edge {
	int nxt, v;
} e[maxn << 1 | 1];
bool dfs1(int u, int fa) {
	for(int it = lnk[u]; it; it = e[it].nxt)
		if(e[it].v != fa && !dfs1(e[it].v, u))
			return 0;
	static int mx[3];
	mx[0] = mx[1] = mx[2] = -1;
	for(int it = lnk[u]; it; it = e[it].nxt) {
		if(e[it].v == fa)
			continue;
		int tmp = f[e[it].v];
		if(mx[0] < tmp)
			swap(mx[0], tmp);
		if(mx[1] < tmp)
			swap(mx[1], tmp);
		if(mx[2] < tmp)
			swap(mx[2], tmp);
	}
	if(fa == -1) {
		if(mx[0] + mx[1] > lim || mx[0] + mx[2] + 1 > lim)
			return 0;
		f[u] = max(mx[0], 0);
	} else if(mx[0] > mx[1] && mx[0] + mx[1] + 1 <= lim)
		f[u] = mx[0];
	else if(mx[0] + mx[1] <= lim && mx[0] + mx[2] + 1 <= lim)
		f[u] = mx[0] + 1;
	else
		return 0;
	return f[u] <= lim;
}
bool dfs2(int u, int fa) {
	for(int it = lnk[u]; it; it = e[it].nxt)
		if(e[it].v != fa && !dfs2(e[it].v, u))
			return 0;
	static int tot, que[maxn];
	tot = 0;
	for(int it = lnk[u]; it; it = e[it].nxt)
		if(e[it].v != fa)
			que[tot++] = f[e[it].v];
	if(fa == -1) {
		sort(que, que + tot);
		f[u] = que[tot - 1];
		if(tot & 1)
			--tot;
		for(int i = 0, j = tot - 1; i < j; ++i, --j)
			if(que[i] + que[j] > lim)
				return 0;
	} else {
		if(deg[u] & 1)
			que[tot++] = 0;
		sort(que, que + tot);
		int L = 0, R = tot - 1;
		while(L < R) {
			int M = (L + R) >> 1;
			bool chk = 1;
			for(int i = 0, j = tot - 1; i < j; ++i, --j) {
				i += i == M;
				j -= j == M;
				if(que[i] + que[j] > lim) {
					chk = 0;
					break;
				}
			}
			if(chk) {
				R = M;
			} else {
				L = M + 1;
			}
		}
		for(int i = 0, j = tot - 1; i < j; ++i, --j) {
			i += i == L;
			j -= j == L;
			if(que[i] + que[j] > lim)
				return 0;
		}
		f[u] = que[L] + 1;
	}
	return f[u] - (fa == -1) <= lim;
}
int dsu[maxn];
int dsu_find(int x) {
	return dsu[x] < 0 ? x : (dsu[x] = dsu_find(dsu[x]));
}
bool dsu_merge(int u, int v) {
	u = dsu_find(u);
	v = dsu_find(v);
	if(u == v)
		return 0;
	if(dsu[u] < dsu[v])
		swap(u, v);
	dsu[v] -= dsu[u] == dsu[v];
	dsu[u] = v;
	return 1;
}
int main() {
	while(scanf("%d", &n) == 1) {
	assert(1 <= n && n <= (int)1e5);
	memset(dsu + 1, -1, n * sizeof(int));
	for(int i = 1; i < n; ++i) {
		int u, v;
		assert(scanf("%d%d", &u, &v) == 2 && 1 <= u && u <= n && 1 <= v && v <= n);
		if(u == v) {
			for(int j = 1; j < n; ++j)
				printf("%d %d\n", u, v);
		}
		assert(dsu_merge(u, v));
		e[i << 1] = (Edge){lnk[u], v};
		lnk[u] = i << 1;
		++deg[u];
		e[i << 1 | 1] = (Edge){lnk[v], u};
		lnk[v] = i << 1 | 1;
		++deg[v];
	}
	int cnt = 0, L, R;
	for(int i = 1; i <= n; ++i)
		cnt += deg[i] & 1;
	printf("%d\n", cnt / 2);
	for(L = 0, R = n - 1; L < R; ) {
		lim = (L + R) >> 1;
		if(dfs1(1, -1)) {
			R = lim;
		} else {
			L = lim + 1;
		}
	}
	printf("%d\n", L);
	for(L = 1, R = n - 1; L < R; ) {
		lim = (L + R) >> 1;
		if(dfs2(1, -1)) {
			R = lim;
		} else {
			L = lim + 1;
		}
	}
	printf("%d\n", L + 1);
	memset(lnk + 1, 0, n * sizeof(int));
	memset(deg + 1, 0, n * sizeof(int));
	}
	return 0;
}