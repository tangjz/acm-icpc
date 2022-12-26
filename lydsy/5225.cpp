#include <bits/stdc++.h>
using namespace std;
typedef double DB;
typedef long long LL;
const int maxn = (int)1e3 + 1, mod = 1004535809;
const DB pi = acos(-1.0), C = log(2 * pi) / 2, eps = 1e-9;
int t, p, q, ans = 1;
struct Gen {
	int a, b, c;
	void init() {
		scanf("%d%d%d", &a, &b, &c);
	}
	void next(int &x) const {
		x = ((LL)x * a + b) % c + 1;
	}
} A, B;
DB fact(int n) {
	if(n >= maxn)
		return (n + 0.5) * log(n) - n + C;
	static int mx = 1;
	static DB f[maxn] = {};
	for( ; mx <= n; ++mx)
		f[mx] = f[mx - 1] + log(mx);
	return f[n];
}
int solve(int p, int q) {
	DB x = q * log(p), t = max(log(x) - 1, 1.0), u = t, v = 0;
	for(int i = 0; i < 3 && fabs(u - v) > eps; ++i) {
		v = u;
		u = max(u * (1 - log(u) + t) / (u + 1), 1.0);
	}
	int n = max((int)ceil(x / u), 1);
	t = fact(n);
	for( ; t <= x; t += log(++n));
	for( ; t - (u = log(n)) > x; t -= u, --n);
	return n;
}
int main() {
	scanf("%d%d%d", &t, &p, &q);
	A.init();
	B.init();
	while(t--) {
		ans = (LL)ans * solve(p, q) % mod;
		A.next(p);
		B.next(q);
	}
	printf("%d\n", ans);
	return 0;
}
