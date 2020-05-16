#include <bits/stdc++.h>
typedef long long LL;
typedef double DB;
const int maxn = 51, maxd = 1 << 16 | 1, maxt = (int)1e6;
int n, k, m, bits[maxd];
LL sum, c[maxn][maxn], msk[maxn];
DB ans;
char buf[maxn];
inline int randL() {
	return RAND_MAX == 0x7FFF ? rand() << 15 | rand() : rand();
}
inline LL randLL() {
	return RAND_MAX == 0x7FFF ? (LL)randL() << 30 | randL() : (LL)randL() << 31 | randL();
}
inline int popcount(unsigned x) {
	return bits[x >> 16] + bits[x & 65535];
}
inline int popcount(LL x) { // assume that x < 2^63
	return popcount((unsigned)(x >> 32)) + popcount((unsigned)x);
}
int main() {
	freopen("close.in", "r", stdin);
	freopen("close.out", "w", stdout);
	for(int i = 0; i < maxn; ++i) {
		c[i][0] = c[i][i] = 1;
		for(int j = 1; j < i; ++j)
			c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
	}
	for(int i = 1; i < maxd; ++i)
		bits[i] = bits[i >> 1] + (i & 1);
	srand(time(0));
	scanf("%d%d%d", &n, &k, &m);
	for(int i = 0; i < k; ++i) {
		scanf("%s", buf);
		for(int j = 0; j < n; ++j)
			msk[i] |= (LL)(buf[j] == '1') << j;
	}
	for(int i = 0; i < m; ++i)
		sum += c[n][i];
	for(int i = 0; i < maxt; ++i) {
		int idx = rand() % k, dif;
		LL rnk = randLL() % sum, val = msk[idx];
		for(dif = 0; rnk >= c[n][dif]; rnk -= c[n][dif++]);
		for(int j = n - 1; dif && j >= 0; --j)
			if(rnk >= c[j][dif]) {
				val ^= 1LL << j;
				rnk -= c[j][dif--];
			}
		for(int j = 0; j < k; ++j)
			dif += popcount(msk[j] ^ val) < m;
		ans += 1.0 / dif;
	}
	printf("%.10e\n", ans / maxt * sum * k);
	return 0;
}
