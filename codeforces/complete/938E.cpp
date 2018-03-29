#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e6 + 1, mod = (int)1e9 + 7;
int n, a[maxn], inv[maxn], ans;
int main() {
	scanf("%d%d", &n, a + 1);
	inv[1] = 1;
	for(int i = 2; i <= n; ++i) {
		scanf("%d", a + i);
		inv[i] = mod - (int)(mod / i * (LL)inv[mod % i] % mod);
	}
	sort(a + 1, a + n + 1);
	for(int i = n, j = i; i >= 1; i = j) {
		for( ; j >= 1 && a[i] == a[j]; --j);
		if(i < n)
			ans = (ans + (LL)a[i] * (i - j) % mod * inv[n - j]) % mod;
	}
	for(int i = 2; i <= n; ++i)
		ans = (LL)ans * i % mod;
	printf("%d\n", ans);
	return 0;
}
