#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e5 + 1;
int t, mx, n, m, dt, a[maxn], b[maxn];
int solve(int n) {
	int ret = 0;
	for(int i = 0; i < m; ++i) {
		int pre = i < n ? 1 : b[i - n];
		int cur = b[i];
		ret += pre + dt < cur;
	}
	for(int i = 0; i < n; ++i) {
		int pre = b[m - 1 - i];
		int cur = mx;
		ret += pre + dt < cur;
	}
	return ret;
}
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d%d%d", &mx, &n, &m, &dt);
		for(int i = 0; i < n; ++i)
			scanf("%d", a + i);
		sort(a, a + n);
		for(int i = 0; i < m; ++i)
			scanf("%d", b + i);
		sort(b, b + m);
		int L = 1, R = min(n, m), M;
		M = solve(L);
		if(M > 0) {
			long long ans = (long long)M * a[0];
			for(int i = 1; i < n; ++i)
				ans += a[i];
			printf("%lld\n", ans);
			continue;
		}
		while(L < R) {
			M = (L + R + 1) >> 1;
			if(solve(M)) {
				R = M - 1;
			} else {
				L = M;
			}
		}
		long long ans = 0;
		for(int i = 0; i < n - L; ++i)
			ans += a[i];
		printf("%lld\n", ans);
	}
	return 0;
}
