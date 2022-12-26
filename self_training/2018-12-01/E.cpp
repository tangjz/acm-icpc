#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e6 + 1;
int t, n;
LL m, dt[maxn], low[maxn], upp[maxn];
bool check(LL tot) {
	low[0] = upp[0] = m;
	for(int i = 1; i < n; ++i) {
		low[i] = m - min(tot - m - max(dt[i] - upp[i - 1], 0LL), m);
		upp[i] = m - max(dt[i] - (m - low[i - 1]), 0LL);
		if(low[i] > upp[i])
			return 0;
	}
	return m - low[n - 1] >= dt[0];
}
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d%lld", &n, &m);
		LL L = m, R = m;
		for(int i = 0; i < n; ++i) {
			scanf("%lld", dt + i);
			L = max(L, m + dt[i]);
			R = max(R, m + dt[i] + dt[i]);
		}
		if(R + R > L + L + L) {
			puts("-1");
			continue;
		}
		while(L < R) {
			LL M = (L + R) >> 1;
			if(check(M)) {
				R = M;
			} else {
				L = M + 1;
			}
		}
		printf("%lld\n", L);
	}
	return 0;
}