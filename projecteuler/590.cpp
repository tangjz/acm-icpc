#include <bits/stdc++.h>
typedef long long LL;
const int maxn = (int)5e4 + 1, maxm = 5087, maxe = 17, mod = (int)1e9, phi = (int)4e8;
int tot, pr[maxn], d[maxn], c[maxm][maxm], cnt[maxe];
struct Exp {
	int val;
	bool sp;
	Exp() {}
	Exp(int x) {
		val = x % phi;
		sp = x >= phi;
	}
	Exp(int x, bool y) {
		assert(x < phi);
		val = x;
		sp = y;
	}
	Exp operator * (Exp const &t) const {
		LL tmp = (LL)val * t.val;
		return (Exp){(int)(tmp % phi), sp || t.sp || tmp >= phi};
	}
} fct[maxe][maxm];
int mod_pow(int x, Exp ex) {
	int ret = 1, k = ex.sp ? ex.val + phi : ex.val;
	for( ; k > 0; k >>= 1, x = (LL)x * x % mod)
		(k & 1) && (ret = (LL)ret * x % mod);
	return ret;
}
int dfs(int dep, Exp sig) {
	if(dep <= 0)
		return mod_pow(2, sig);
	int ret = 0;
	for(int i = 0, sgn = 1; i <= cnt[dep]; ++i, sgn = -sgn)
		ret = (ret + (LL)sgn * c[cnt[dep]][i] * dfs(dep - 1, sig * fct[dep][i])) % mod;
	return ret < 0 ? ret + mod : ret;
}
int main() {
	for(int i = 2; i < maxn; ++i) {
		if(!d[i])
			pr[tot++] = d[i] = i;
		for(int j = 0, k; (k = i * pr[j]) < maxn; ++j) {
			d[k] = pr[j];
			if(d[i] == pr[j])
				break;
		}
	}
	pr[tot] = maxn;
	for(int i = 0; i < maxm; ++i) {
		c[i][0] = c[i][i] = 1;
		for(int j = 1; j < i; ++j)
			(c[i][j] = c[i - 1][j - 1] + c[i - 1][j]) >= mod && (c[i][j] -= mod);
	}
	int n;
	while(scanf("%d", &n) == 1) {
		int mx = 0;
		for(int i = 0; pr[i] <= n; ++i) {
			int ex = 0;
			for(int rem = n; rem >= pr[i]; rem /= pr[i], ++ex);
			for( ; mx < ex; cnt[++mx] = 0);
			++cnt[ex];
		}
		long long ways = 1;
		for(int i = 1; i <= mx; ways *= cnt[i++] + 1) {
			printf("%d%c", cnt[i], " \n"[i == mx]);
			Exp ex = Exp(1), tp = Exp(i);
			for(int j = 0; j <= cnt[i]; ++j, ex = ex * tp)
				fct[i][j] = ex;
			ex = Exp(1);
			tp = Exp(i + 1);
			for(int j = cnt[i]; j >= 0; --j, ex = ex * tp)
				fct[i][j] = fct[i][j] * ex;
		}
		printf("ways: %lld\n", ways);
		printf("ans: %d\n", dfs(mx, Exp(1)));
	}
	return 0;
}
