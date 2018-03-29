#include <cstdio>
typedef long long LL;
const int maxn = 2000001, maxm = 23, maxe = 65, INF = ~0u >> 1;
int t, tot, d[maxn], pr[maxn], tr[maxe][maxe], ex[maxe];
LL ans;
inline int min(int a, int b, int c) {
	return a < b ? (a < c ? a : c) : (b < c ? b : c);
}
struct Factor {
	LL value;
	int cnt, p[maxm], e[maxm];
	void init(int delta = 1) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		u *= delta;
		value = (LL)u * v * w;
		cnt = 0;
		while(1) {
			int pp = min(d[u], d[v], d[w]);
			if(pp == INF)
				break;
			e[cnt] = 0;
			for( ; d[u] == pp; u /= pp, ++e[cnt]);
			for( ; d[v] == pp; v /= pp, ++e[cnt]);
			for( ; d[w] == pp; w /= pp, ++e[cnt]);
			p[cnt++] = pp;
		}
	}
} N, M, S;
void pfs(int dep, LL val, int sgn) {
	if(!sgn)
		return;
	if(dep == N.cnt) {
		ans += M.value / val * sgn;
		return;
	}
	pfs(dep + 1, val, sgn * tr[ex[dep]][0]);
	for(int i = 1; i <= N.e[dep]; ++i)
		pfs(dep + 1, val *= N.p[dep], sgn * tr[ex[dep]][i]);
}
void dfs(int dep, LL val) {
	if(val > N.value)
		return;
	if(dep == S.cnt) {
		++ans;
		return;
	}
	dfs(dep + 1, val);
	for(int i = 1; i <= S.e[dep]; ++i)
		dfs(dep + 1, val *= S.p[dep]);
}
int main() {
	d[1] = INF;
	for(int i = 2; i < maxn; ++i) {
		if(!d[i])
			pr[tot++] = d[i] = i;
		for(int j = 0, k; (k = i * pr[j]) < maxn; ++j) {
			d[k] = pr[j];
			if(d[i] == pr[j])
				break;
		}
	}
	for(int i = 0; i < maxe; ++i)
		for(int j = 0; j < maxe; ++j)
			for(int k = 0; k <= i && k <= j; ++k)
				tr[i][j] += (k == j) - (k == j - 1);
	scanf("%d", &t);
	while(t--) {
		N.init();
		M.init();
		S.init(2);
		for(int i = 0, j = 0; i < N.cnt; ++i) {
			for( ; j < S.cnt && S.p[j] < N.p[i]; ++j);
			ex[i] = j < S.cnt && S.p[j] == N.p[i] ? S.e[j] : 0;
		}
		ans = 0;
		pfs(0, 1, 1);
		dfs(0, 1);
		printf("%I64d\n", ans);
	}
	return 0;
}
