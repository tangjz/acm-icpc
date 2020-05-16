#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 201, maxm = 51;
const LL INF = 0x3f3f3f3f3f3f3f3fLL;
int n, m, qtot, etot;
struct Point {
	int x, y;
	void read() {
		scanf("%d%d", &x, &y);
	}
	bool operator < (Point const &t) const {
		return x < t.x || (x == t.x && y < t.y);
	}
	Point operator - (Point const &t) const {
		return (Point){x - t.x, y - t.y};
	}
	LL det(Point const &t) const {
		return (LL)x * t.y - (LL)y * t.x;
	}
	int site() const {
		return x < 0 || (!x && y < 0);
	}
} p[maxn], q[maxn];
bool cmp(Point const &u, Point const &v) {
	int sU = u.site(), sV = v.site();
	return sU < sV || (sU == sV && u.det(v) > 0);
}
struct Edge {
	int u, v;
	Point vec;
	bool operator < (Edge const &t) const {
		return cmp(vec, t.vec);
	}
} e[maxn * (maxn >> 1)];
LL f[maxn][maxm], ans;
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; ++i)
		p[i].read();
	sort(p, p + n);
	for(int o = 0; o < n; ++o) {
		qtot = etot = 0;
		for(int i = o; i < n; ++i)
			q[qtot++] = p[i] - p[o];
		sort(q + 1, q + qtot, cmp);
		for(int i = 1; i < qtot; ++i) {
			e[etot++] = (Edge){0, i, q[i] - q[0]};
			for(int j = i + 1, k = i; j < qtot; ++j)
				if((q[j] - q[i]).det(q[k] - q[i]) <= 0) {
					e[etot++] = (Edge){i, j, q[j] - q[i]};
					k = j;
				}
			e[etot++] = (Edge){i, 0, q[0] - q[i]};
		}
		sort(e, e + etot);
		for(int i = 0; i < qtot; ++i)
			for(int j = 0; j <= m; ++j)
				f[i][j] = -INF;
		f[0][0] = 0;
		for(int i = 0; i < etot; ++i) {
			int u = e[i].u, v = e[i].v;
			for(int j = 1; j <= m; ++j) {
				LL tp = f[u][j - 1] + q[u].det(q[v]);
				f[v][j] < tp && (f[v][j] = tp);
			}
		}
		ans < f[0][m] && (ans = f[0][m]);
	}
	printf("%lld.%c0\n", ans >> 1, "05"[ans & 1]);
	return 0;
}
