#include <bits/stdc++.h>
typedef long long LL;
const int maxn = (int)1e5 + 1;
int t, n, m, bit[maxn];
LL ans, adt;
int main() {
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		scanf("%d%d", &n, &m);
		ans = adt = 0;
		memset(bit, 0, (m + 1) * sizeof(int));
		for(int i = 1; i <= n; ++i) {
			adt += i / m;
			if(i % m > 0) {
				int pL = ((LL)i * i + 1) % m, pR = (pL + i - 1) % m;
				if(pL > pR)
					++adt;
				for(int j = pL + 1; j <= m; j += j & -j)
					++bit[j];
				for(int j = pR + 2; j <= m; j += j & -j)
					--bit[j];
			}
			for(int j = (LL)i * i * i % m + 1; j > 0; j -= j & -j)
				ans += bit[j];
			ans += adt;
		}
		printf("Case %d: %lld\n", Case, ans);
	}
	return 0;
}
