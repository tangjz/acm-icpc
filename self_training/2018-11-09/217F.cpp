#include <bits/stdc++.h>
using namespace std;
typedef double DB;
typedef long long LL;
const int maxn = (int)1e5 + 1, maxm = (int)2e5 + 1;
const DB eps = 1e-6, rate = (sqrtl(5) + 1) / 2;
int n, m, dsu[maxn], ord[maxm];
struct Edge {
	int u, v, a, b;
	LL c;
	void read() {
		scanf("%d%d%d%d%lld", &u, &v, &a, &b, &c);
	}
	DB get(DB t) const {
		return (a * t + b) * t + c;
	}
} e[maxm];
DB w[maxm];
int dsu_find(int x) {
	return dsu[x] < 0 ? x : (dsu[x] = dsu_find(dsu[x]));
}
DB calc(DB t) {
	DB ret = 0;
	int tot = 0;
	for(int i = 0; i < m; ++i) {
		w[i] = e[i].get(t);
		if(w[i] > 0)
			ord[tot++] = i;
	}
	sort(ord, ord + tot, [&](int const &u, int const &v) {
		return w[u] > w[v];
	});
	memset(dsu + 1, -1, n * sizeof(int));
	for(int i = 0; i < tot; ++i) {
		int u = dsu_find(e[ord[i]].u);
		int v = dsu_find(e[ord[i]].v);
		if(u != v) {
			ret += w[ord[i]];
			if(dsu[u] < dsu[v])
				swap(u, v);
			dsu[v] -= dsu[u] == dsu[v];
			dsu[u] = v;
		}
	}
	return ret;
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0; i < m; ++i)
		e[i].read();
	int tL, tR;
	LL w;
	scanf("%d%d%lld", &tL, &tR, &w);
	DB L = tL, R = tR, pL, pM, pR;
	while(1) {
		DB ML = R - (R - L) / rate, fL = calc(ML);
		if(fL < w) {
			pM = ML;
			break;
		}
		DB MR = L + (R - L) / rate, fR = calc(MR);
		if(fR < w) {
			pM = MR;
			break;
		}
		if(fL < fR) {
			R = MR;
		} else {
			L = ML;
		}
	}
	L = tL;
	R = pM;
	while((R - L) / (tR - tL) >= eps) {
		DB M = (L + R) / 2, fM = calc(M);
		if(fM < w) {
			R = M;
		} else {
			L = M;
		}
	}
	pL = L;
	L = pM;
	R = tR;
	while((R - L) / (tR - tL) >= eps) {
		DB M = (L + R) / 2, fM = calc(M);
		if(fM < w) {
			L = M;
		} else {
			R = M;
		}
	}
	pR = L;
	printf("%.5f\n", 1 - (pR - pL) / (tR - tL));
	return 0;
}
