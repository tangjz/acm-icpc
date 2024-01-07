#include <bits/stdc++.h>
using namespace std;
typedef unsigned int UL;
typedef long long LL;
typedef unsigned long long ULL;
typedef double DB;
typedef long double LDB;
const int maxn = (int)2e5 + 1, maxd = 26, mod = 998244353, INF = 0x3f3f3f3f;
const LL INFLL = 0x3f3f3f3f3f3f3f3fLL;
const DB pi = acos((DB)-1);

int main() {
	static int ifact[maxn];
	ifact[1] = 1;
	for(int i = 2; i < maxn; ++i)
		ifact[i] = mod - (int)(mod / i * (LL)ifact[mod % i] % mod);
	ifact[0] = 1;
	for(int i = 1; i < maxn; ++i)
		ifact[i] = (LL)ifact[i - 1] * ifact[i] % mod;
	int T = 1;
	// scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		int n;
		LL k;
		scanf("%d%lld", &n, &k);
		if(k >= n) {
			puts("0");
			continue;
		}
		auto mod_pow = [&mod](int x, int k) {
			int ret = 1;
			for( ; k > 0; x = (LL)x * x % mod, k >>= 1)
				if(k & 1)
					ret = (LL)ret * x % mod;
			return ret;
		};
		int ans = 0, m = n - k;
		for(int i = 0; i <= m; ++i) {
			int tmp = (LL)mod_pow(m - i, n) * ifact[m - i] % mod * ifact[i] % mod;
			(ans += i & 1 ? mod - tmp : tmp) >= mod && (ans -= mod);
		}
		for(int i = 0; i < m; ++i)
			ans = (LL)ans * (n - i) % mod;
		if(m < n)
			ans = (ans + ans) % mod;
		printf("%d\n", ans);
	}
	return 0;
}