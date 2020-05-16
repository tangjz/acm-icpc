#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)3e5 + 1, mod[2] = {(int)1e9 + 7, (int)1e9 + 9};
int n, mx, c[maxn], f[maxn], g[maxn], inv[2][maxn];
bool check(int m) {
	for(int o = 0; o < 2; ++o) {
		int p = mod[o];
		for(int i = 0; i < m; ++i)
			f[i] = 0;
		for(int i = m, coeff = 1; i <= n; ++i) {
			f[i] = coeff;
			coeff = (LL)coeff * (i + 1) % p * inv[o][i - m + 1] % p;
		}
		for(int i = mx; i >= 1; --i) {
			g[i] = f[c[i]];
			for(int j = i + i; j <= mx; j += i)
				(g[i] -= g[j]) < 0 && (g[i] += p);
		}
		if(g[1])
			return 1;
	}
	return 0;
}
int main() {
	for(int o = 0; o < 2; ++o) {
		int p = mod[o];
		inv[o][1] = 1;
		for(int i = 2; i < maxn; ++i)
			inv[o][i] = p - (int)(p / i * (LL)inv[o][p % i] % p);
	}
	scanf("%d", &n);
	int r = 0;
	for(int i = 0; i < n; ++i) {
		int x;
		scanf("%d", &x);
		++c[x];
		r = __gcd(r, x);
		mx = max(mx, x);
	}
	if(r > 1) {
		puts("-1");
		return 0;
	}
	for(int i = 1; i <= mx; ++i)
		for(int j = i + i; j <= mx; j += i)
			c[i] += c[j];
	int L = 1, R = n;
	while(L < R) {
		int M = (L + R) >> 1;
		if(check(M)) {
			R = M;
		} else {
			L = M + 1;
		}
	}
	printf("%d\n", L);
	return 0;
}