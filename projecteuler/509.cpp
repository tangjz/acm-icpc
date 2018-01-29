#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxm = 5, maxs = 65, mod = 1234567890;
int f[maxm][maxs];
int main() {
	LL n;
	while(scanf("%lld", &n) == 1) {
		int mx = 1;
		memset(f, 0, sizeof f);
		for(int i = 0; 1LL << i <= n; ++i)
			for(f[1][i] = (((n >> i) + 1) >> 1) % mod; mx <= i; mx <<= 1);
		for(int i = 0; i < mx; ++i)
			for(int j = 0; j < mx; ++j)
				f[2][i] = (f[2][i] + (LL)f[1][j] * f[1][i ^ j]) % mod;
		for(int i = 0; i < mx; ++i)
			for(int j = 0; j < mx; ++j)
				f[3][i] = (f[3][i] + (LL)f[2][j] * f[1][i ^ j]) % mod;
		LL ans = 0;
		for(int i = 1; i < mx; ++i)
			ans += f[3][i];
		printf("%lld\n", ans % mod);	
	}
	return 0;
}
