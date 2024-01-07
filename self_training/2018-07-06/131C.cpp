#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)5e4 + 1, maxd = 11, maxs = 1 << 10 | 1, mod = (int)1e9 + 7;
int n, m, tot, lnk[maxn], ord[maxn], fa[maxn], sz[maxn], col[maxn], msk[maxn];
struct Edge {
	int nxt, v;
} e[maxn << 1 | 1];
bool ban[maxn];
int bits[maxs], cnt[maxs], sum[maxs], tmp[maxs], res[maxd];
void bfs(int rt) {
	tot = 0;
	ord[tot++] = rt;
	for(int i = 0; i < tot; ++i) {
		int u = ord[i];
		for(int it = lnk[u]; it != -1; it = e[it].nxt) {
			int v = e[it].v;
			if(v == fa[u] || ban[v])
				continue;
			fa[v] = u;
			ord[tot++] = v;
		}
	}
}
int getRoot(int rt) {
	bfs(rt);
	int pos = -1, cnt = maxn;
	for(int i = tot - 1; i >= 0; --i) {
		int u = ord[i], mx = 0;
		sz[u] = 1;
		for(int it = lnk[u]; it != -1; it = e[it].nxt) {
			int v = e[it].v;
			if(v == fa[u] || ban[v])
				continue;
			sz[u] += sz[v];
			mx = max(mx, sz[v]);
		}
		mx = max(mx, tot - sz[u]);
		if(mx < cnt) {
			pos = u;
			cnt = mx;
		}
	}
	return pos;
}
void solve(int rt) {
	fa[rt] = -1;
	rt = getRoot(rt);
	ban[rt] = 1;
	memset(sum, 0, m * sizeof(int));
	msk[rt] = col[rt];
	++sum[msk[rt]];
	++res[bits[msk[rt]]];
	for(int it = lnk[rt]; it != -1; it = e[it].nxt) {
		int v = e[it].v;
		if(ban[v])
			continue;
		memset(cnt, 0, m * sizeof(int));
		fa[v] = rt;
		bfs(v);
		for(int i = 0; i < tot; ++i) {
			int u = ord[i];
			msk[u] = msk[fa[u]] | col[u];
			++cnt[msk[u]];
		}
		for(int i = 1; i < m; i <<= 1)
			for(int j = 0; j < m; ++j)
				if(i & j) {
					(cnt[j] += cnt[j - i]) >= mod && (cnt[j] -= mod);
					(sum[j] += sum[j - i]) >= mod && (sum[j] -= mod);
				}
		for(int i = 0; i < m; ++i)
			tmp[i] = (LL)cnt[i] * sum[i] % mod;
		for(int i = 1; i < m; i <<= 1)
			for(int j = 0; j < m; ++j)
				if(i & j) {
					(cnt[j] -= cnt[j - i]) < 0 && (cnt[j] += mod);
					(sum[j] -= sum[j - i]) < 0 && (sum[j] += mod);
					(tmp[j] -= tmp[j - i]) < 0 && (tmp[j] += mod);
				}
		for(int i = 0; i < m; ++i) {
			sum[i] += cnt[i];
			(res[bits[i]] += tmp[i]) >= mod && (res[bits[i]] -= mod);
		}
	}
	for(int it = lnk[rt]; it != -1; it = e[it].nxt) {
		int v = e[it].v;
		if(!ban[v])
			solve(v);
	}
}
int main() {
	int K;
	scanf("%d%d", &n, &K);
	m = 1 << K;
	memset(lnk + 1, -1, n * sizeof(int));
	for(int i = 1; i <= n; ++i) {
		scanf("%d", col + i);
		col[i] = 1 << (col[i] - 1);
	}
	for(int i = 1; i < n; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		e[tot] = (Edge){lnk[u], v};
		lnk[u] = tot++;
		e[tot] = (Edge){lnk[v], u};
		lnk[v] = tot++;
	}
	for(int i = 1; i < m; ++i)
		bits[i] = bits[i >> 1] + (i & 1);
	solve(1);
	int ans = 0;
	for(int i = K; i >= 0; --i)
		ans = (131LL * ans + res[i]) % mod;
	printf("%d\n", ans);
	return 0;
}
