#include <bits/stdc++.h>
using namespace std;

typedef unsigned int UL;
typedef long long LL;
typedef unsigned long long ULL;
typedef	double DB;
typedef long double LD;

const int mod = (int)1e9 + 7, maxd = 10, maxc = 26;
const int maxn = (int)1e5 + 9, maxm = (int)1e6 + 1;
const DB eps = 1e-9, pi = acos((DB)-1);

inline int sgn(DB x) {
	return (x > eps) - (x < -eps);
}

int exgcd(int a, int b, int &x, int &y) {
	if(!b) {
		x = 1;
		y = 0;
		return a;
	}
	int r = exgcd(b, a % b, y, x);
	y -= a / b * x;
	return r;
}

void solve() {
	int n, m;
	LL q;
	scanf("%d%d%lld", &n, &m, &q);
	int x, y, r = exgcd(n, m, x, y);
	LL lcm = m / r * (LL)n;

	int upp = max(n, m) * 2;
	static pair<int, int> pos[maxm];
	memset(pos + 1, 0, upp * sizeof(pos[0]));
	for(int i = 1; i <= n + m; ++i) {
		int val;
		scanf("%d", &val);
		if(i <= n) {
			pos[val].first = i;
		} else {
			pos[val].second = i - n;
		}
	}

	LL L = 1, R = q * upp;
	while(L < R) {
		LL M = (L + R) >> 1;
		LL ctr = M;
		for(int i = 1; i <= upp; ++i) {
			int const &u = pos[i].first;
			int const &v = pos[i].second;
			if(!u || !v || (v - u) % r != 0)
				continue;
			int xx = (v - u) * (LL)x % m;
			if(xx < 0)
				xx += m;
			LL sta = xx / r * (LL)n + u;
			if(M >= sta)
				ctr -= (M - sta) / lcm + 1;
		}
		if(ctr < q) {
			L = M + 1;
		} else {
			R = M;
		}
	}
	printf("%lld\n", L);
}

int main() {
	int T = 1;
	// scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		// printf("Case #%d: ", Case);
		solve();
	}
	return 0;
}