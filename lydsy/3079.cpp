#include <bits/stdc++.h>
typedef long long LL;
const int maxk = (int)1e3 + 1, mod = (int)1e9 + 7;
int n, k, fct[maxk], rem[maxk], gcd[maxk][maxk], f[maxk][maxk];
int F(int m, int k, int d) { // dist x[1..k] in [0, n), m | sum(x[1..k-1]) + d x[k]
	int com = m < n ? gcd[m][d] : rem[d];
	if(k == 1)
		return n / m * com;
	if(m == 1)
		return fct[k];
	if(m < n && d == 1 && f[m][k])
		return f[m][k] - 1;
	int res = (n / m * com * (LL)F(com, k - 1, 1) - (k - 1LL) * F(m, k - 1, d + 1)) % mod;
	if(res < 0)
		res += mod;
	if(m < n && d == 1 && !f[m][k])
		f[m][k] = res + 1;
	return res;
}
int main() {
	scanf("%d%d", &n, &k);
	if(n < k) {
		puts("0");
		return 0;
	}
	fct[0] = 1;
	for(int i = 1; i <= k; ++i) {
		fct[i] = (LL)fct[i - 1] * (n - i + 1LL) % mod;
		gcd[0][i] = i;
	}
	for(int i = 1; i <= k; ++i)
		for(int j = 0; j <= k; ++j)
			gcd[i][j] = i > j ? gcd[j][i] : gcd[i][j - i];
	int ivs = rem[1] = 1;
	for(int i = 2; i <= k; ++i) {
		rem[i] = mod - (int)(mod / i * (LL)rem[mod % i] % mod);
		ivs = (LL)ivs * rem[i] % mod;
	}
	for(int i = 1; i <= k; ++i)
		rem[i] = gcd[n % i][i];
	printf("%d\n", (int)((LL)F(n, k, 1) * ivs % mod));
	return 0;
}
