#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int mod = 998244353;
int n, f0, f1, f2, c0, c1, c2, ans;
int main() {
	scanf("%d", &n);
	if(n == 1) {
		puts("0");
		return 0;
	}
	f0 = f2 = c1 = ans = 1;
	c0 = 3;
	c2 = 6;
	for(int i = 3; i <= n; ++i) {
		f0 = ((LL)c0 * f1 + (LL)c1 * f0) % mod * c2 % mod;
		swap(f0, f1);
		swap(f1, f2);
		(ans += f2) >= mod && (ans -= mod);
		if(i == n)
			break;
		c2 = (c2 + (3LL * i - 1) * i / 2) % mod;
		(c1 += c0) >= mod && (c1 -= mod);
		c0 += 2;
	}
	printf("%d\n", ans);
	return 0;
}