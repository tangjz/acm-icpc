#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 121, mod = 998244353;
int n, g[2][maxn];
LL que[maxn], f[2][maxn];
int main() {
	scanf("%lld", &que[0]);
	n = 1;
	for(int i = 0; i < n; ++i) {
		LL tmp = (que[i] + 1) >> 1;
		if(tmp && que[n - 1] > tmp)
			que[n++] = tmp;
		tmp = que[i] - tmp;
		if(tmp && que[n - 1] > tmp)
			que[n++] = tmp;
	}
	g[0][n - 1] = 1;
	for(int i = n - 2, j = n - 1, k = n - 1; i >= 0; --i) {
		LL lft = que[i] >> 1, rht = que[i] - lft;
		for( ; que[k] < lft; --k);
		for( ; que[j] < rht; --j);
		LL jv = max(f[0][j], f[1][j]);
		int jw = (jv == f[0][j] ? g[0][j] : 0) + (jv == f[1][j] ? g[1][j] : 0);
		LL kv = max(f[0][k], f[1][k]);
		int kw = (kv == f[0][k] ? g[0][k] : 0) + (kv == f[1][k] ? g[1][k] : 0);
		f[0][i] = jv + kv;
		g[0][i] = (LL)jw * kw % mod;
		LL jjv = f[0][j] + kv + 1;
		int jjw = (LL)g[0][j] * kw % mod;
		LL kkv = jv + f[0][k] + 1;
		int kkw = (LL)jw * g[0][k] % mod;
		f[1][i] = max(jjv, kkv);
		(g[1][i] = (jjv == f[1][i] ? jjw : 0) + (kkv == f[1][i] ? kkw : 0)) >= mod && (g[1][i] -= mod);
	}
	LL ans = max(f[0][0], f[1][0]);
	int ways = (ans == f[0][0] ? g[0][0] : 0) + (ans == f[1][0] ? g[1][0] : 0);
	ways >= mod && (ways -= mod);
	printf("%lld %d\n", ans, ways);
	return 0;
}
