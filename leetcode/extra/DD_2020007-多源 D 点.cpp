#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e5 + 1;
int n, lim, tot, ord[maxn], par[maxn];
vector<int> e[maxn];
bool ban[maxn], sp[maxn], ans[maxn];
void bfs(int rt) { // par[rt] was set
	tot = 0;
	ord[tot++] = rt;
	for(int i = 0; i < tot; ++i) {
		int u = ord[i];
		for(int v: e[u])
			if(v != par[u] && !ban[v]) {
				par[v] = u;
				ord[tot++] = v;
			}
	}
}
int getRoot(int rt) {
	int pos = -1, cnt = maxn;
	static int sz[maxn];
	bfs(rt);
	for(int i = tot - 1; i >= 0; --i) {
		int u = ord[i], mx = 0;
		sz[u] = 1;
		for(int v: e[u])
			if(v != par[u] && !ban[v]) {
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
void dfs(int rt) {
	par[rt] = -1;
	rt = getRoot(rt);
	ban[rt] = 1;
    int qtot = 0;
    static int dis[maxn], pre[maxn], suf[maxn];
    dis[rt] = 0;
    for(int u: e[rt]) {
        if(ban[u])
            continue;
        pre[qtot] = -1;
        par[u] = rt;
        bfs(u);
        for(int i = 0; i < tot; ++i) {
            int u = ord[i], p = par[u];
            dis[u] = dis[p] + 1;
            if(sp[u])
                pre[qtot] = max(pre[qtot], dis[u]);
        }
        suf[qtot] = pre[qtot];
        ++qtot;
    }
    for(int i = 1; i < qtot; ++i)
        pre[i] = max(pre[i - 1], pre[i]);
    for(int i = qtot - 2; i >= 0; --i)
        suf[i] = max(suf[i], suf[i + 1]);
    if(!sp[rt] && pre[qtot - 1] > lim)
        ans[rt] = 0;
    int qidx = 0;
	for(int u: e[rt]) {
		if(ban[u])
			continue;
        int upp = sp[rt] ? 0 : -1;
        if(qidx > 0)
            upp = max(upp, pre[qidx - 1]);
        if(qidx < qtot - 1)
            upp = max(upp, suf[qidx + 1]);
        ++qidx;
        if(upp == -1)
            continue;
        par[u] = rt;
        bfs(u);
        for(int i = 0; i < tot; ++i) {
            int u = ord[i];
            if(dis[u] + upp > lim)
                ans[u] = 0;
        }
	}
	for(int u: e[rt])
		if(!ban[u])
			dfs(u);
}
int main() {
    int m;
    assert(scanf("%d%d%d", &n, &m, &lim) == 3);
    assert(1 <= min(n, min(m, lim)) && max(n, max(m, lim)) <= 100000);
    while(m--) {
        int x;
        assert(scanf("%d", &x) == 1);
        assert(1 <= x && x <= n);
        sp[x] = 1;
    }
    for(int i = 2, x; i <= n; ++i) {
        assert(scanf("%d", &x) == 1);
        assert(1 <= x && x <= n);
        e[i].push_back(x);
        e[x].push_back(i);
    }
    for(int i = 1; i <= n; ++i)
        ans[i] = 1;
    dfs(1);
    int cnt = 0;
    for(int i = 1; i <= n; ++i)
        cnt += ans[i];
    printf("%d\n", cnt);
	return 0;
}
