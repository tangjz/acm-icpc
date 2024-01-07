#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e6 + 1, mod = (int)1e9 + 7;
int n, m, tot;
pair<int, int> seg[maxn];
inline void addSegment(int L, int R) {
	if(tot && seg[tot - 1].second + 1 == L) {
		seg[tot - 1].second = R;
	} else {
		seg[tot++] = make_pair(L, R);
	}
}
inline int calc(int n) {
	static bool enabled = 0;
	static int f[maxn] = {};
	if(n < maxn) {
		if(!enabled) {
			int upp = min(::n + ::m + 1, maxn);
			for(int i = 1; i < upp; ++i)
				for(int j = i; j < upp; j += i)
					(f[j] += i) >= mod && (f[j] -= mod);
			for(int i = 1; i < upp; ++i)
				(f[i] += f[i - 1]) >= mod && (f[i] -= mod);
			enabled = 1;
		}
		return f[n];
	} else {
		int ret = 0;
		for(int i = 1, j; i <= n; i = j + 1) {
			int p = n / i;
			j = n / p;
			ret = (ret + ((LL)i + j) * (j - i + 1) / 2 % mod * p) % mod;
		}
		return ret;
	}
}
int main() {
	scanf("%d%d", &n, &m);
	if(n > m)
		swap(n, m);
	for(int i = 1, j; i <= m; i = j + 1) {
		int p = n / i, q = m / i, r = (n + m) / (p + q + 1);
		j = p ? min(n / p, m / q) : m / q;
		if(i <= r)
			addSegment(i, min(j, r));
	}
	addSegment(m + 1, m + n);
	int ans = 0;
	for(int i = 0; i < tot; ++i) {
		(ans += calc(seg[i].second)) >= mod && (ans -= mod);
		(ans -= calc(seg[i].first - 1)) < 0 && (ans += mod);
	}
	printf("%d\n", ans);
	return 0;
}