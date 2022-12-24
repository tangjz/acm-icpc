#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
const int maxn = (int)2e3 + 1, mod = (int)1e9 + 7;
int n, a[maxn], b[maxn], inv[maxn];
int main() {
	scanf("%d%d", &n, a + 0);
	for(int i = 1, prd = 1; i < n; ++i) {
		scanf("%d", a + i);
		prd = (LL)prd * i % mod;
		a[i] = (LL)a[i] * prd % mod;
	}
	inv[1] = 1;
	for(int i = 2; i <= n; ++i)
		inv[i] = mod - (int)(mod / i * (LL)inv[mod % i] % mod);
	b[0] = 1;
	for(int i = 1; i < n; ++i) {
		b[i] = inv[i + 1];
		for(int j = 1; j < i; ++j)
			b[i] = (LL)(b[i] + b[j]) * inv[i + 1 - j] % mod;
		if(b[i])
			b[i] = mod - b[i];
	}
	(++b[1]) == mod && (b[1] = 0);
	printf("%d", a[0]);
	for(int i = 1, ivs = 1; i <= n; ++i) {
		LL tmp = 0;
		for(int j = i - 1, k = 0; j < n; ++j, ++k) {
			tmp += (LL)a[j] * b[k];
			if(tmp < 0)
				tmp = (ULL)tmp % mod;
		}
		ivs = (LL)ivs * inv[i] % mod;
		int res = (tmp < mod ? tmp : tmp % mod) * ivs % mod;
		printf(" %d", res);
	}
	puts("");
	return 0;
}