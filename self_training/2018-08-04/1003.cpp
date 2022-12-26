#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 201;
const LL INF = 0x3f3f3f3f3f3f3f3fLL;
int t, n;
LL w[maxn][maxn], match[maxn], sx[maxn], sy[maxn], slack[maxn], pre[maxn];
bool vis[maxn];
void augment(int rt) {
	int cur = 0;
	match[0] = rt;
	memset(vis, 0, (n + 1) * sizeof(bool));
	memset(slack, 0x3f, (n + 1) * sizeof(LL));
	do {
		int nxt, u = match[cur];
		LL dt = INF;
		vis[cur] = 1;
		for(int v = 1; v <= n; ++v) {
			if(vis[v])
				continue;
			LL tmp = sx[u] + sy[v] - w[u][v];
			if(slack[v] > tmp) {
				slack[v] = tmp;
				pre[v] = cur;
			}
			if(slack[v] < dt) {
				dt = slack[v];
				nxt = v;
			}
		}
		for(int v = 0; v <= n; ++v)
			if(vis[v]) {
				sx[match[v]] -= dt;
				sy[v] += dt;
			} else
				slack[v] -= dt;
		cur = nxt;
	} while(match[cur]);
	for(int v = cur; v; v = pre[v])
		match[v] = match[pre[v]];
}
LL KM() {
	for(int i = 1; i <= n; ++i) {
		LL dt = 0;
		for(int j = 1; j <= n; ++j)
			dt = max(dt, w[i][j]);
		sx[i] = dt;
		sy[i] = match[i] = 0;
	}
	for(int i = 1; i <= n; ++i)
		augment(i);
	LL cost = 0;
	for(int i = 1; i <= n; ++i)
		cost += sx[i] + sy[i];
	return cost;
}
int main() {
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= n; ++j) {
				scanf("%I64d", w[i] + j);
				w[i][j] = -w[i][j];
			}
		printf("Case #%d: %I64d\n", Case, -KM());
	}
	return 0;
}
