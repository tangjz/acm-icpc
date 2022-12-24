#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 201, maxt = 5001;
int t, n, m, lim, ord[maxn], sz, idx[maxn];
LL ans;
inline int sgn(int x) {
	return (x > 0) - (x < 0);
}
struct Point {
	int x, y;
	void read() {
		scanf("%d%d", &x, &y);
	}
	void write() {
		printf("%d %d\n", x, y);
	}
	bool operator == (Point const &t) const {
		return x == t.x && (y == t.y);
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
	LL dot(Point const &t) const {
		return (LL)x * t.x + (LL)y * t.y;
	}
	bool site() const {
		return x < 0 || (!x && y < 0);
	}
	LL len2() const {
		return dot(*this);
	}
} p[maxn], q[maxn], out[maxn];
int rand15() {
	return rand() & 0x3FFF;
}
int rand30() {
	return rand15() << 15 | rand15();
}
void check2() {
	int sumx = 0, sumy = 0;
	static Point a[maxn];
	for(int i = 1; i <= n; ++i) {
		sumx += q[i].x;
		sumy += q[i].y;
	}
	for(int i = 1; i <= n; ++i)
		a[i] = (Point){q[i].x * n - sumx, q[i].y * n - sumy};
	sort(ord + 1, ord + n + 1, [&](int const &u, int const &v) {
		int su = a[u].site(), sv = a[v].site();
		if(su != sv)
			return su < sv;
		LL dt = a[u].det(a[v]);
		if(dt)
			return dt > 0;
		return a[u].len2() < a[v].len2();
	});
	for(int i = 1, j = i, o = 0; i <= n; i = j, o ^= 1) {
		for( ; j <= n && !a[ord[i]].det(a[ord[j]]); ++j);
		if(o)
			reverse(ord + i, ord + j);
	}
	LL area = q[ord[n]].det(q[ord[1]]);
	for(int i = 1; i < n; ++i)
		area += q[ord[i]].det(q[ord[i + 1]]);
	area = abs(area);
	if(ans > area) {
//		fprintf(stderr, "new 2: %lld\n", area);
		ans = area;
		sz = 0;
		for(int i = 1; i <= n; ++i) {
			out[i] = q[i];
			for( ; sz > 1 && !(q[idx[sz]] - q[idx[sz - 1]]).det(q[ord[i]] - q[idx[sz - 1]]); --sz);
			idx[++sz] = ord[i];
		}
	}
}
void check() {
	sort(ord + 1, ord + n + 1, [&](int const &u, int const &v) {
		return q[u] < q[v];
	});
	for(int i = 1; i < n; ++i)
		if(q[ord[i]] == q[ord[i + 1]])
			return;
	int tot = 0;
	static int stk[maxn];
	for(int i = 1; i <= n; ++i) {
		for( ; tot > 1 && (q[stk[tot]] - q[stk[tot - 1]]).det(q[ord[i]] - q[stk[tot - 1]]) <= 0; --tot);
		stk[++tot] = ord[i];
	}
	for(int i = n, tp = tot; i >= 1; --i) {
		for( ; tot > tp && (q[stk[tot]] - q[stk[tot - 1]]).det(q[ord[i]] - q[stk[tot - 1]]) <= 0; --tot);
		stk[++tot] = ord[i];
	}
	tot -= tot > 1;
	if(tot == 2)
		return;
	LL area = q[stk[tot]].det(q[stk[1]]);
	for(int i = 1; i < tot; ++i)
		area += q[stk[i]].det(q[stk[i + 1]]);
	area = abs(area);
	if(ans > area) {
//		fprintf(stderr, "new: %lld\n", area);
		ans = area;
		sz = tot;
		for(int i = 1; i <= sz; ++i)
			idx[i] = stk[i];
		for(int i = 1; i <= n; ++i)
			out[i] = q[i];
	}
	check2();
}
int main() {
	srand(time(0));
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d%d", &n, &m, &lim);
		int sumx = 0, sumy = 0;
		static int rnk[maxn];
		static Point a[maxn];
		for(int i = 1; i <= n; ++i) {
			p[i].read();
			sumx += p[i].x;
			sumy += p[i].y;
			rnk[i] = ord[i] = i;
		}
		for(int i = 1; i <= n; ++i)
			a[i] = (Point){p[i].x * n - sumx, p[i].y * n - sumy};
		sort(rnk + 1, rnk + n + 1, [&](int const &u, int const &v) {
			return a[u].len2() > a[v].len2();
		});
		ans = ~0ULL >> 1;
		for(int i = 1; i <= n; ++i)
			q[i] = p[i];
		check();
		for(int i = 0; i < 2 * maxt / 5; ++i) {
			for(int j = 1; j <= m; ++j)
				swap(ord[j], ord[j + rand() % (n - j + 1)]);
			for(int j = 1; j <= n; ++j)
				q[j] = p[j];
			for(int j = 1; j <= m; ++j) {
				int dis = (int)sqrtl(rand30() % (lim * lim));
				int x = rand() % (dis << 1 | 1) - dis;
				dis = (int)sqrtl(dis * dis - x * x);
				int y = rand() % (dis << 1 | 1) - dis;
				q[ord[j]] = p[ord[j]] - (Point){x, y};
			}
			check();
		}
//		for(int i = 0; i < maxt / 5; ++i) {
//			int dis = (int)sqrtl(rand30() % (lim * lim));
//			int x = rand30() % (dis << 1 | 1) - dis;
//			dis = (int)sqrtl(dis * dis - x * x);
//			int y = rand30() % (dis << 1 | 1) - dis;
//			memcpy(ord + 1, rnk + 1, n * sizeof(int));
//			rotate(ord + 1, ord + rand() % m + 1, ord + n + 1);
//			Point vec = (Point){-x, -y};
//			for(int j = 1; j <= n; ++j)
//				q[j] = p[j];
//			for(int j = 1; j <= m; ++j)
//				q[ord[j]] = p[ord[j]] - vec;
//			check();
//		}
		memcpy(ord + 1, rnk + 1, n * sizeof(int));
		for(int i = 0; i < 3 * maxt / 5; ++i) {
			for(int j = 1; j <= n; ++j)
				q[j] = p[j];
			for(int j = m; j >= 1; --j) {
				int o = rnk[j];
				double th = (double)a[o].x * a[o].x / (a[o].len2());
				LL dist = min(a[o].len2(), (LL)lim * lim * n * n) / n / n;
				int x = (sqrtl(dist * th) - rand() % (int)sqrtl(n)) * sgn(a[o].x);
				int y = (sqrtl(dist * (1 - th)) - rand() % (int)sqrtl(n)) * sgn(a[o].y);
				for( ; x * x + y * y > lim * lim; abs(x) < abs(y) ? (y -= sgn(y)) : (x -= sgn(x)));
				q[o] = p[o] - (Point){x, y};
			}
			check();
			for(int j = 1; j <= m; ++j)
				swap(ord[j], ord[j + rand() % (n - j + 1)]);
		}
		printf("%d\n", sz);
		for(int i = 1; i <= sz; ++i)
			printf("%d%c", idx[i], " \n"[i == sz]);
		for(int i = 1; i <= n; ++i)
			out[i].write();
	}
	return 0;
}
