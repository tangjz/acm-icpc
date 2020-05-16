#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e6 + 1, mod = 998244353;
int n, fct, prd, ans;
int main() {
	scanf("%d", &n);
	fct = 1;
	for(int i = 1; i <= n; ++i)
		fct = (LL)fct * i % mod;
	ans = fct;
	prd = 1;
	for(int i = 1; i <= n; ++i) {
		prd = (LL)prd * (n - i + 1) % mod;
		(ans += fct) >= mod && (ans -= mod);
		(ans -= prd) < 0 && (ans += mod);
	}
	printf("%d\n", ans);
	return 0;
}