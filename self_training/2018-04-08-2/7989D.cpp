#include <bits/stdc++.h>
using namespace std;
typedef double DB;
const int maxn = (int)1e5 + 1, INF = 0x3f3f3f3f;
const DB eps = 1e-12;
int n, pL[maxn], pR[maxn];
vector<int> e[maxn];
DB lim, qL[maxn], qR[maxn];
inline int dcmp(DB x) {
	return (x > eps) - (x < -eps);
} 
bool dfs(int u, int fa) {
	qL[u] = pL[u];
	qR[u] = pR[u];
	for(auto &v : e[u]) {
		if(v == fa)
			continue;
		if(!dfs(v, u))
			return 0;
		qL[u] = max(qL[u], qL[v] - lim);
		qR[u] = min(qR[u], qR[v] + lim);
	}
	return dcmp(qL[u] - qR[u]) <= 0;
}
int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; ++i) {
		char buf[11];
		scanf("%s", buf);
		if(buf[0] == '*') {
			pL[i] = -INF;
			pR[i] = INF;
		} else {
			sscanf(buf, "%d", pL + i);
			pR[i] = pL[i];
		}
	}
	for(int i = 1; i < n; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		--u;
		--v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	DB L = 0, R = 1e7;
	for(int i = 0; i < 100; ++i) {
		lim = L + (R - L) * 0.5;
		if(dfs(1, -1)) {
			R = lim;
		} else {
			L = lim;
		}
	}
	printf("%.20f\n", L);
	return 0;
}
