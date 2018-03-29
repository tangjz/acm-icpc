#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int mod = (int)1e9 + 7;
LL n;
int main() {
	scanf("%lld", &n);
	int ans = n % mod * (n - 2) % mod, x = (mod + 1) >> 1;
	for(--n; n > 0; n >>= 1, x = (LL)x * x % mod)
		(n & 1) && (ans = (LL)ans * x % mod);
	printf("%d\n", ans);
	return 0;
}
