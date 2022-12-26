#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)2e3 + 9, mod = (int)1e9 + 7;
int n, m, fact[maxn], iact[maxn];
int main() {
	iact[1] = 1;
	for(int i = 2; i < maxn; ++i)
		iact[i] = mod - (int)(mod / i * (LL)iact[mod % i] % mod);
	fact[0] = iact[0] = 1;
	for(int i = 1; i < maxn; ++i) {
		fact[i] = (LL)fact[i - 1] * i % mod;
		iact[i] = (LL)iact[i - 1] * iact[i] % mod;
	}
	while(scanf("%d%d", &n, &m) == 2) {
		int ways = (LL)fact[n + m + 1] * fact[n + m] % mod * iact[n + 1] % mod * iact[n] % mod * iact[m + 1] % mod * iact[m] % mod;
		printf("%d\n", ways);
	}
	return 0;
}
