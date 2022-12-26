#include <bits/stdc++.h>
using namespace std;
const int maxn = 501, maxm = (int)2.5e5 + 1;
const double pi = acos(-1), eps = 1e-9, INF = 1e9;

struct Point {
	int x, y;
	void read() {
		scanf("%d%d", &x, &y);
	}
	Point operator - (Point const &t) const {
		return (Point){x - t.x, y - t.y};
	}
	bool operator < (Point const &t) const {
		int sgn = onLeft() - t.onLeft();
		return sgn ? sgn < 0 : det(t) > 0;
	}
	bool onLeft() const {
		return x < 0 || (!x && y < 0);
	}
	int dot(Point const &t) const {
		return x * t.x + y * t.y;
	}
	int det(Point const &t) const {
		return x * t.y - y * t.x;
	}
};

double solve() {
	int n, m = 0;
	static int ord[maxm], dot[maxn][maxn], det[maxn][maxn];
	static Point p[maxn], e[maxm];
	static pair<int, int> edges[maxm];
	static mt19937_64 rnd(random_device{}());

	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		p[i].read();
	shuffle(p, p + n, rnd);
	// no identical points
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j) {
			if(i == j) {
				dot[i][j] = det[i][j] = 0;
				continue;
			}
			e[m++] = p[j] - p[i];
			dot[i][j] = i < j ? e[m - 1].dot(e[m - 1]) : dot[j][i];
			det[i][j] = i < j ? p[i].det(p[j]) : -det[j][i];
		}
	// no collinear edges
	iota(ord, ord + m, 0);
	sort(ord, ord + m, [&](int const &u, int const &v) {
		return e[u] < e[v];
	});
	for(int i = 0; i < m; ++i) {
		edges[i] = {ord[i] / (n - 1), ord[i] % (n - 1)};
		edges[i].second += edges[i].second >= edges[i].first;
	}

	double L = 0, upp = n / (2 * pi);
	for(int i = 0; i < n; ++i) {
		double M = L + eps, R = upp;
		auto check = [&]() -> bool {
			static double dp[maxn];
			for(int u = 0; u < n; ++u)
				dp[u] = -INF;
			dp[i] = 0;
			for(int j = 0; j < m; ++j) {
				int &u = edges[j].first, &v = edges[j].second;
				double &lft = dp[v], rht = dp[u] + det[u][v] - M * dot[u][v];
				lft < rht && (lft = rht);
				if(v == i && lft > 0)
					return 1;
			}
			return 0;
		};
		if(M > R || !check())
			continue;
		while(R - L >= eps) {
			M = (L + R) / 2;
			if(check()) {
				L = M;
			} else {
				R = M;
			}
		}
	}
	return L / 2;
}

int main() {
	int T;
	scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		printf("%.20e\n", solve());
	}
	return 0;
}
