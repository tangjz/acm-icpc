#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e6 + 1, mod = (int)1e9 + 7;

int inv[maxn], sum[maxn];

inline int mod_inv(int x) {
	assert(x);
	return x < maxn ? inv[x] : (mod - (int)(mod / x * (LL)mod_inv(mod % x) % mod));
}

int solve1(int n, int m, int t) {
	int ret = (((LL)m * m - 1) * n * 3 - ((LL)m * m * m - 1) % mod * (t + 1)) % mod * t % mod * mod_inv(6) % mod;
	return ret < 0 ? ret + mod : ret;
}

int solve2(int n, int t) {
	int ret = ((LL)n * n * n % mod * sum[t] + (t + 1LL - n * 3) * t) % mod * mod_inv(6) % mod;
	return ret < 0 ? ret + mod : ret;
}

int solve(int n, int m) {
	int ret = solve2(n, n), pos = (n - 1) / m;
	if(pos >= 1)
		ret = (ret + solve1(n, m, pos) - solve2(n, pos)) % mod;
	ret = (((LL)n * n - 1) * (m - 1) % mod * mod_inv(2) - ret) % mod;
	return ret < 0 ? ret + mod : ret;
}

double foo(int a, int b, int c, int d, int lim = (int)1e7) {
	mt19937_64 rnd(time(NULL));
	double sum = 0, cnt = 0;
	while(cnt < lim) {
		double p = (double)rnd() / (1LL << 32) / (1LL << 32) * (b - a) + a;
		double q = (double)rnd() / (1LL << 32) / (1LL << 32) * (d - c) + c;
		while(p >= q)
			p -= q;
		while(p < 0)
			p += q;
		sum += p;
		++cnt;
	}
	return sum / cnt;
}

int main() {
	inv[1] = sum[1] = 1;
	for(int i = 2; i < maxn; ++i) {
		inv[i] = mod - (int)(mod / i * (LL)inv[mod % i] % mod);
		sum[i] = (sum[i - 1] + (LL)inv[i] * inv[i]) % mod;
		assert((LL)inv[i] * i % mod == 1);
	}
	int t;
	scanf("%d", &t);
	while(t--) {
		int a, b, c, d;
		scanf("%d%d%d%d", &a, &b, &c, &d);
		int ans = ((LL)solve(b, d) + solve(a, c) - solve(a, d) - solve(b, c)) * mod_inv((LL)(b - a) * (d - c) % mod) % mod;
		printf("%d\n", ans < 0 ? ans + mod : ans);
	}
	return 0;
}