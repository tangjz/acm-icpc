#include <cstdio>
#include <cmath>

constexpr int N = 1600;
constexpr double inf = 1e16;

int n, m, k, v1 ,v2, a[29];
int u, v, x[N + 9], y[N + 9], p[N + 9];
double r[N + 9][N + 9];
bool use[N + 9];
double s[N + 9], ans;
int ptr, stk[N * N + 9];

double sqr(double x) {
	return x * x;
}

double dis(int i, int j) {
	return std::sqrt(sqr(x[i] - x[j]) + sqr(y[i] - y[j]));
}

int main() {
	scanf("%d%d%d%d%d", &n, &m, &k, &v1, &v2);
	for (int i = 1; i <= n; ++i) scanf("%d%d", x + i, y + i);
	for (int i = 1; i <= n; ++i)
		for (int j = i + 1; j <= n; ++j)
			r[i][j] = r[j][i] = dis(i, j) / v2;
	while (m--) {
		scanf("%d%d", &u, &v);
		r[u][v] = r[v][u] = dis(u, v) / v1;
	}
	for (int i = 1; i <= k; ++i) scanf("%d", a + i);
	a[0] = 1, a[k + 1] = n;
	for (int i = 0; i <= k; ++i) {
		for (u = 0; u <= n; ++u) {
			use[u] = false;
			s[u] = inf;
		}
		s[a[i + 1]] = 0;
		for (int j = 1; j <= n; ++j) {
			u = 0;
			for (v = 1; v <= n; ++v) {
				if (!use[v] && s[u] > s[v]) u = v;
			}
			use[u] = true;
			for (v = 1; v <= n; ++v) {
				if (s[v] > s[u] + r[u][v]) {
					s[v] = s[u] + r[u][v];
					p[v] = u;
				}
			}
		}
		for (u = a[i]; u != a[i + 1]; u = p[u]) stk[ptr++] = u;
		ans += s[a[i]];
	}
	printf("%.8f\n", ans);
	for (int i = 0; i < ptr; ++i) printf("%d ", stk[i]);
	printf("%d\n", n);
	return 0;
}
