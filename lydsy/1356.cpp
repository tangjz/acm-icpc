#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 1501, maxm = 1124251;
int n, m, x[maxn], y[maxn];
LL ans;
struct Node {
	LL len2;
	int x, y, u, v;
	bool operator == (Node const &t) const {
		return len2 == t.len2 && x == t.x && y == t.y;
	}
	bool operator < (Node const &t) const {
		return len2 != t.len2 ? len2 < t.len2 : (x != t.x ? x < t.x : y < t.y);
	}
} seq[maxm];
inline LL sqr(int dt) {
	return (LL)dt * dt;
}
int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; ++i) {
		scanf("%d%d", x + i, y + i);
		for(int j = 0; j < i; ++j)
			seq[m++] = (Node){sqr(x[i] - x[j]) + sqr(y[i] - y[j]), x[i] + x[j], y[i] + y[j], j, i};
	}
	sort(seq, seq + m);
	for(int i = 0; i < m; ) {
		for(int j = i; i < m && seq[i] == seq[j]; ++i) {
			int o = seq[i].u;
			for(int k = j; k < i; ++k) {
				int p = seq[k].u, q = seq[k].v;
				ans = max(ans, abs((LL)(x[p] - x[o]) * (y[q] - y[o]) - (LL)(x[q] - x[o]) * (y[p] - y[o])));
			}
		}
	}
	printf("%lld\n", ans);
	return 0;
}
