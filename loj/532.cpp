#include <bits/stdc++.h>
const int maxn = (int)1e6 + 1, mod = (int)1e9 + 7;
typedef long long LL;
int sta, len, mx, p[maxn], f[maxn], g[maxn];
double coeff[maxn + 2];
void find_circle() {
	int A, B, C, X;
	scanf("%d%d%d%d", &A, &B, &C, &X);
	for(int i = 1; ; ++i) {
		X = ((LL)A * X + B) % C + 1;
		mx = std::max(mx, X);
		if(p[X]) {
			sta = p[X];
			len = i - p[X];
			break;
		}
		p[X] = i;
	}
}
void count_times(int f[]) {
	LL L, R;
	scanf("%lld%lld", &L, &R);
	for(int i = 1; i <= mx; ++i)
		if(p[i] >= sta)
			f[i] = (f[i - 1] + (R >= p[i] ? (R - p[i]) / len + 1 : 0) - (L > p[i] ? (L - 1 - p[i]) / len + 1 : 0)) % mod;
		else
			(f[i] = f[i - 1] + (L <= p[i] && p[i] <= R)) >= mod && (f[i] -= mod);
}
void solve() {
	int ans = 0;
	for(int i = 3; i <= mx + 1; ++i)
		coeff[i] = (i + sqrt((LL)i * i - 4)) / 2;
	for(int i = 1; i <= mx; ++i) {
		int lft = f[i] - f[i - 1], rht = g[i] - g[i - 1];
		ans = (ans + (((LL)lft * rht) << 1)) % mod;
		if(!lft && !rht)
			continue;
		for(int L = i + 1, R, k; L <= mx; L = R + 1) {
			k = ((LL)i * i + (LL)L * L - 1) / ((LL)i * L) + 1;
			R = std::min((int)ceil(i * coeff[k]), mx);
			for( ; R < mx && ((LL)i * i + (LL)R * R - 1) / ((LL)i * R) + 1 <= k; ++R);
			for( ; ((LL)i * i + (LL)R * R - 1) / ((LL)i * R) + 1 > k; --R);
			ans = (ans + ((LL)(f[R] - f[L - 1]) * rht + (LL)lft * (g[R] - g[L - 1])) % mod * k) % mod;
		}
	}
	ans < 0 && (ans += mod);
	printf("%d\n", ans);
}
int main() {
	find_circle();
	count_times(f);
	count_times(g);
	solve();
	return 0;
}
