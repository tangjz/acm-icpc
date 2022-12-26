// (n+1)k - p * C(k+1, 2)
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e5 + 1, maxs = (int)2e5 + 1, mod = 998244353;
int tot, pr[maxn], d[maxn], c[2][maxn], cnt, f[2][maxs];
LL n, fct[maxs], sq[maxs];
inline void mod_inc(int &x, int y) {
	(x += y) >= mod && (x -= mod);
}
inline LL iSqrt(LL x) {
	LL r;
	for(r = (int)sqrtl(x); r * r <= x; ++r);
	for( ; r * r > x; --r);
	return r;
}
int main() {
	scanf("%lld", &n);
	int sqN = iSqrt(n);
	assert(sqN < maxn);
	d[1] = 1;
	for(int i = 2; i <= sqN; ++i) {
		c[0][i] = c[0][i - 1];
		c[1][i] = c[1][i - 1];
		if(!d[i]) {
			pr[tot++] = d[i] = i;
			++c[0][i];
			mod_inc(c[1][i], i);
		}
		for(int j = 0, k; (k = i * pr[j]) <= sqN; ++j) {
			d[k] = pr[j];
			if(d[i] == pr[j])
				break;
		}
	}
	for(int i = 1; i <= sqN; ++i)
		fct[++cnt] = i;
	for(int i = sqN - (n / sqN == sqN); i >= 1; --i)
		fct[++cnt] = n / i;
	for(int i = 1; i <= cnt; ++i) {
		sq[i] = iSqrt(fct[i]);
		f[0][i] = fct[i] % mod;
		f[1][i] = f[0][i] * (f[0][i] + 1LL) / 2 % mod;
	} //int ctr = 0;
	for(int i = 0; i < tot; ++i) { //printf("#%d (%d): ", i + 1, pr[i]);
		for(int j = cnt; j >= 1; --j) { //++ctr;
			LL nxt = fct[j] / pr[i];
			if(nxt < pr[i])
				break;
			int pos = nxt <= sqN ? nxt : cnt - n / nxt + 1;
			int v0 = f[0][pos], v1 = f[1][pos];
			if(i && pr[i - 1] > sq[pos]) {
				mod_inc(v0, c[0][sq[pos]]);
				mod_inc(v0, mod - c[0][pr[i - 1]]);
				mod_inc(v1, c[1][sq[pos]]);
				mod_inc(v1, mod - c[1][pr[i - 1]]);
			}
			v1 = (LL)v1 * pr[i] % mod;
			mod_inc(f[0][j], mod - v0);
			mod_inc(f[1][j], mod - v1);
			//printf(" (%lld: %d, %d)", fct[j], f[0][j], f[1][j]);
		} //printf("\n");
	} //fprintf(stderr, "ctr: %d, cnt: %d\n", ctr, cnt);
	for(int i = 1; i <= cnt; ++i) {
		mod_inc(f[0][i], c[0][sq[i]]);
		mod_inc(f[1][i], c[1][sq[i]]);
		//printf("#%d (%lld): %d %d\n", i, fct[i], f[0][i], f[1][i]);
	}
	int ans = 0;
	for(LL i = 2, j, k; i <= n; i = j + 1) {
		k = n / i;
		j = n / k;
		int pos = j <= sqN ? j : cnt - k + 1;
		int v0 = f[0][pos] - f[0][pos - 1], v1 = f[1][pos] - f[1][pos - 1];
		//printf("k=%lld, [%lld, %lld]: %d %d\n", k, i, j, v0 < 0 ? v0 + mod : v0, v1 < 0 ? v1 + mod : v1);
		k %= mod;
		ans = (ans + (n + 1) % mod * k % mod * v0 - k * (k + 1LL) / 2 % mod * v1) % mod;
	}
	for(int i = 0; i < tot; ++i)
		for(LL val = (LL)pr[i] * pr[i]; val <= n; val *= pr[i]) {
			int adt = n / val % mod;
			//printf("p^e=%lld, k=%lld\n", val, n / val);
			ans = (ans + (n + 1) % mod * adt - adt * (adt + 1LL) / 2 % mod * (val % mod)) % mod;
		}
	printf("%d\n", ans < 0 ? ans + mod : ans);
	return 0;
}
