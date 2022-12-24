#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e5 + 1, mod = (int)1e9 + 7;
int t, n, m, a[maxn], c[maxn], inv[maxn], ans;
int main() {
	inv[1] = 1;
	for(int i = 2; i < maxn; ++i)
		inv[i] = mod - (int)(mod / i * (LL)inv[mod % i] % mod);
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		for(int i = 0; i < n; ++i)
			scanf("%d", a + i);
		sort(a, a + n);
		m = 0;
		for(int i = 0; i < n; ++i)
			if(!m || a[m - 1] < a[i]) {
				a[m++] = a[i];
				c[m - 1] = 1;
			} else {
				++c[m - 1];
			}
		ans = 1;
		for(int i = 0; i < m; ++i) {
			for(int j = 1; c[i] >= 2; ++j, c[i] -= 2)
				ans = ans * (c[i] * (c[i] - 1LL) / 2) % mod * inv[j] % mod;
			if(c[i]) {
				ans = (LL)ans * c[i + 1] % mod;
				--c[i];
				--c[i + 1];
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}