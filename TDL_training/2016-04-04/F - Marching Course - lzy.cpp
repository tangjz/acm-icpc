#include <cstdio>

#define N 200

struct Edge{int v,d,s;Edge *x;} E[N * N + 9], *e, *lnk[N + 9];

int n, m, P, u, v, d, s;
double f[1009][N + 9];

void add(int u, int v, int d, int s) {
	e->v = v, e->d = d, e->s = s, e->x = lnk[u], lnk[u] = e++;
}

void upd(double &a, double b) {
	if (a < b) a = b;
}
int main() {
	scanf("%d%d%d", &n, &m, &P);
	e = E;
	while (m--) {
		scanf("%d%d%d%d", &u, &v, &d, &s);
		add(u, v, d, s);
		add(v, u, d, s);
	}
	for (int t = 0; t <= P; ++t)
		for (u = 1; u <= n; ++u)
			f[t][u] = -1e9;
	f[0][1] = 0;
	for (int t = 0; t < P; ++t) {
		for (u = 1; u <= n; ++u) {
			for (Edge *p = lnk[u]; p; p = p -> x) {
				if (t + 2 * p->d <= P) {
					upd(f[t + 2 * p->d][p->v], f[t][u] + 2 * p->s);
				} else {
					upd(f[P][p->v], f[t][u] + (double)(P - t) * p->s / p->d);
				}
			}
		}
	}
	double ans = 0;
	for (u = 1; u <= n; ++u) upd(ans, f[P][u]);
	printf("%.6f\n", ans);
	return 0;
}
