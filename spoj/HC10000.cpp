#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int maxd = 61, mod = (int)1e9;

LL bin[maxd][maxd];
int a[maxd][maxd], b[maxd][maxd], c[maxd][maxd];
int sb[maxd][maxd], sc[maxd][maxd];

void prepare() {
	memset(bin, -1, sizeof bin);
	memset(a, -1, sizeof a);
	memset(b, -1, sizeof b);
	memset(c, -1, sizeof c);
	memset(sb, -1, sizeof sb);
	memset(sc, -1, sizeof sc);
	for(int i = 0; i < maxd; ++i) {
		a[i][0] = b[i][0] = b[i][i] = bin[i][0] = bin[i][i] = 1;
		sb[i][0] = a[i][i] = 0;
		c[i][i] = (1LL << i) % mod;
	}
}

inline void modInc(int &x, int y) {
	(x += y) >= mod && (x -= mod);
}
inline int modFix(LL x) {
	return x < mod ? x : x % mod;
}

inline LL binom(int m, int k) {
	LL &ret = bin[m][k];
	if(ret == -1)
		ret = binom(m - 1, k - 1) + binom(m - 1, k);
	return ret;
}

inline int B(int m, int k) {
	int &ret = b[m][k];
	if(ret == -1) {
		ret = B(m - 1, k - 1);
		modInc(ret, B(m - 1, k));
	}
	return ret;
}

inline int SB(int m, int k) {
	int &ret = sb[m][k];
	if(ret == -1) {
		ret = SB(m, k - 1);
		modInc(ret, B(m, k - 1));
	}
	return ret;
}

inline int A(int m, int k) {
	int &ret = a[m][k];
	if(ret == -1)
		ret = ((LL)B(m - 2, k - 1) * B(m - 1, k) + A(m - 1, k - 1) + A(m - 1, k)) % mod;
	return ret;
}

inline int C(int m, int k) {
	int &ret = c[m][k];
	if(ret == -1)
		ret = ((LL)(C(m - 1, m - 1) + SB(m - 1, k)) * B(m, k) + A(m, k)) % mod;
	return ret;
}

inline int SC(int m, int k) {
	int &ret = sc[m][k];
	if(ret == -1) {
		ret = C(m, k);
		if(k)
			modInc(ret, SC(m, k - 1));
	}
	return ret;
}

inline int calc(LL n) {
	if(n <= 4)
		return (n - 1) << 1 | (n == 1);
	int ans = 6, m = 2;
	LL mx = 8;
	for( ; mx < n; ++m, mx <<= 1)
		modInc(ans, SC(m, m));
	if(mx == n) {
		modInc(ans, SC(m, m));
		return ans;
	}
	int k = 0;
	for(mx >>= 1; (mx += binom(m, k)) < n; ++k);
	if(mx == n) {
		modInc(ans, SC(m, k));
		return ans;
	}
	if(k)
		modInc(ans, SC(m, k - 1));
	n -= mx - binom(m, k);
	ans = (ans + (LL)(C(m - 1, m - 1) + SB(m - 1, k)) * modFix(n)) % mod;
	while(n != binom(m, k)) {
		mx = binom(m - 1, k - 1);
		if(n <= mx) {
			--k;
		} else {
			n -= mx;
			ans = (ans + A(m - 1, k - 1) + (LL)B(m - 2, k - 1) * modFix(n)) % mod;
		}
		--m;
	}
	modInc(ans, A(m, k));
	return ans;
}

void solve() {
	LL n;
	scanf("%lld", &n);
	printf("%d\n", calc(n));
}

int main() {
	prepare();

	int T = 1;
	scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		// printf("Case #%d: ", Case);
		solve();
	}
	return 0;
}
