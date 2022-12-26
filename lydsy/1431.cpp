#include <bits/stdc++.h>
using namespace std;
typedef double DB;
const int maxn = 201, maxm = 1201, maxt = 100;
const DB rate = (sqrtl(5) + 1) / 2;
int n, m, dsu[maxn], ord[maxm];
struct Edge {
	int u, v, a, b;
	void read() {
		scanf("%d%d%d%d", &u, &v, &a, &b);
	}
	DB get(DB t) const {
		return a * t + b;
	}
} e[maxm];
DB w[maxm];
bool cmp(int const &u, int const &v) {
	return w[u] < w[v];
}
int dsu_find(int x) {
	return dsu[x] < 0 ? x : (dsu[x] = dsu_find(dsu[x]));
}
DB calc(DB t) {
	DB ret = 0;
	for(int i = 0; i < m; ++i) {
		w[i] = e[i].get(t);
		ord[i] = i;
	}
	sort(ord, ord + m, cmp);
	memset(dsu, -1, n * sizeof(int));
	for(int i = 0; i < m; ++i) {
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
	int tL, tR;
	scanf("%d%d%d%d", &n, &m, &tL, &tR);
	for(int i = 0; i < m; ++i)
		e[i].read();
	DB L = tL, R = tR;
	for(int i = 0; i < maxt; ++i) {
		DB ML = R - (R - L) / rate, fL = calc(ML);
		DB MR = L + (R - L) / rate, fR = calc(MR);
		if(fL < fR) {
			L = ML;
		} else {
			R = MR;
		}
	}
	printf("%.3f\n", calc(L));
	return 0;
}
