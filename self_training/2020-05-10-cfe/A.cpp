#include <bits/stdc++.h>
using namespace std;
typedef unsigned int UL;
typedef long long LL;
typedef unsigned long long ULL;
typedef double DB;
typedef long double LDB;
const int maxn = (int)3e5 + 1, maxd = 26, mod = (int)1e9 + 7, INF = 0x3f3f3f3f;
const LL INFLL = 0x3f3f3f3f3f3f3f3fLL;
const DB pi = acos((DB)-1);

int main() {
	int T = 1;
	scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		int x, y, a, b;
		scanf("%d%d%d%d", &x, &y, &a, &b);
		LL ans = (LL)a * (abs(x) + abs(y));
		auto check = [&](int u, int v) {
			ans = min(ans, (LL)b * abs(u) + (LL)a * abs(v - u));
		};
		check(x, y);
		check(y, x);
		printf("%lld\n", ans);
	}
	return 0;
}