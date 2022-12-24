#include <cstdio>
#include <algorithm>
typedef long long LL;
const int maxn = 100001;
int t, n, a[maxn];
LL m, v;
bool check(LL sta) {
	if(m <= n << 1) {
		LL mx = sta, c = sta;
		for(int i = 0, j = 0; i < m; ++i, (++j) == n && (j = 0)) {
			c = std::max(c + a[j], 0LL);
			mx = std::max(mx, c);
		}
		return mx >= v;
	}
	LL mx = sta, c1 = sta;
	for(int i = 0; i < n; ++i) {
		c1 = std::max(c1 + a[i], 0LL);
		mx = std::max(mx, c1);
	}
	if(mx >= v)
		return 1;
	LL c2 = c1;
	for(int i = 0; i < n; ++i)
		c2 = std::max(c2 + a[i], 0LL);
	if(c1 >= c2)
		return 0;
	LL tim = m / n;
	int r = m % n;
	if(tim - 1 >= (v - c1 - 1) / (c2 - c1) + 1)
		return 1;
	LL c = c1 + (tim - 2) * (c2 - c1);
	for(int i = 0; i < r; ++i)
		c = std::max(c + a[i], 0LL);
	for(int i = 0, j = r; i < n; ++i, (++j) == n && (j = 0)) {
		c = std::max(c + a[j], 0LL);
		mx = std::max(mx, c);
	}
	return mx >= v;
}
int main() {
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		scanf("%d%lld%lld", &n, &v, &m);
		for(int i = 0; i < n; ++i)
			scanf("%d", a + i);
		LL L = 0, R = v;
		while(L < R) {
			LL M = (L + R) >> 1;
			if(check(M)) {
				R = M;
			} else {
				L = M + 1;
			}
		}
		printf("Case #%d: %lld\n", Case, L);
	}
	return 0;
}
