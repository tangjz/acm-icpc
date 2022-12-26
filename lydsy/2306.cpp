#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)101;
int n, m, s;
double p, w[maxn], f[maxn][maxn][maxn];
pair<int, int> e[maxn];
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i)
		scanf("%lf", w + i);
	scanf("%d%lf", &s, &p);
	for(int i = 1; i <= m; ++i)
		scanf("%d%d", &e[i].first, &e[i].second);
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j)
			f[0][i][j] = i == j ? 0 : -1;
	for(int i = 1; i <= n; ++i) {
		double (*cf)[maxn] = f[i], (*pf)[maxn] = f[i - 1];
		for(int u = 1; u <= n; ++u)
			for(int v = 1; v <= n; ++v)
				cf[u][v] = -1;
		for(int j = 1; j <= m; ++j) {
			int u = e[j].first, v = e[j].second;
			for(int k = 1; k <= n; ++k)
				if(pf[v][k] >= 0) {
					double tmp = w[v] + p * pf[v][k];
					if(cf[u][k] < tmp)
						cf[u][k] = tmp;
				}
		}
	}
	double ans = 0;
	for(int u = 1; u <= n; ++u) {
		double pp = 1, adt = 0;
		for(int i = 1; i <= n; ++i) {
			pp *= p;
			if(f[i][u][u] >= 0) {
				double tmp = f[i][u][u] / (1 - pp);
				if(adt < tmp)
					adt = tmp;
			}
		}
		pp = 1;
		for(int i = 0; i <= n; ++i) {
			if(f[i][s][u] >= 0) {
				double tmp = w[s] + p * (f[i][s][u] + pp * adt);
				if(ans < tmp)
					ans = tmp;
			}
			pp *= p;
		}
	}
	printf("%.1f\n", ans);
	return 0;
}
