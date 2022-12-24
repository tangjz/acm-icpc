#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int maxn = (int)1e6 + 1, mod = 998244353;

int bin[5][maxn];

void prepare() {
	for(int i = 0; i < maxn; ++i)
		bin[0][i] = 1;
	for(int i = 1; i < 5; ++i)
		for(int j = i; j < maxn; ++j)
			(bin[i][j] = bin[i - 1][j - 1] + bin[i][j - 1]) >= mod && (bin[i][j] -= mod);
}

void solve() {
	int n, m;
	scanf("%d%d", &n, &m);
	int aL = bin[4][n], aR = (LL)bin[2][n] * bin[2][n] % mod;
	int bL = bin[4][m], bR = (LL)bin[2][m] * bin[2][m] % mod;
	int res = ((LL)aR * bR - (LL)(aR - aL) * (bR - bL)) % mod;
	printf("%d\n", res < 0 ? res + mod : res);
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