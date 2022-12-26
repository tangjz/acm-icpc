#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)3e3 + 1, maxm = (int)1e4 + 1;
int n, m, lnk[maxn], tot, ord[maxn], dis[maxn], adt[maxn], ans[maxm];
struct Edge {
	int nxt, v;
} e[maxm << 1 | 1];
bool vis[maxm];
int main() {
	int szL, szR;
	scanf("%d%d%d", &szL, &szR, &m);
	n = szL + szR;
	for(int i = 1; i <= m; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		v += szL;
		e[i << 1] = (Edge){lnk[u], v};
		lnk[u] = i << 1;
		e[i << 1 | 1] = (Edge){lnk[v], u};
		lnk[v] = i << 1 | 1;
	}
	for(int i = 1; i <= n; ++i) {
		if(dis[i])
			continue;
		int seq[2][3] = {};
		tot = 0;
		dis[i] = 1;
		ord[tot++] = i;
		for(int j = 0; j < tot; ++j) {
			int u = ord[j], o = dis[u] & 1;
			if((++seq[o][0]) <= 2)
				seq[o][seq[o][0]] = u;
			for(int it = lnk[u]; it; it = e[it].nxt) {
				int v = e[it].v;
				if(dis[v])
					continue;
				vis[it >> 1] = 1;
				dis[v] = dis[u] + 1;
				ord[tot++] = v;
			}
		}
		if(seq[0][0] == 1 && seq[1][0] == 1) {
			puts("-1");
			return 0;
		}
		int o = seq[0][0] < seq[1][0];
		for(int j = 0; j < tot; ++j)
			if((dis[ord[j]] & 1) == o)
				++adt[ord[j]];
		for(int j = 1, k = seq[o][0] % 3; k != 0; ++j, (++k) == 3 && (k = 0))
			++adt[seq[o][j]];
		for(int j = tot - 1; j >= 0; --j) {
			int u = ord[j];
			for(int it = lnk[u]; it; it = e[it].nxt) {
				int v = e[it].v;
				if(dis[u] + 1 != dis[v] || !vis[it >> 1])
					continue;
				ans[it >> 1] = adt[v];
				(adt[u] -= ans[it >> 1]) < 0 && (adt[u] += 3);
			}
		}
	}
	for(int i = 1; i <= m; ++i)
		printf("%d%c", ans[i], " \n"[i == m]);
	return 0;
}
