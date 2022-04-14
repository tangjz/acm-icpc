#include <set>
#include <map>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <cctype>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
using namespace std;
typedef unsigned int UL;
typedef long long LL;
typedef unsigned long long ULL;
typedef	double DB;
typedef long double LD;
const int mod = (int)1e9 + 7, maxd = 10, maxc = 26;
const int maxn = (int)1e5 + 9, maxm = (int)1e6 + 1;
const DB eps = 1e-9;

inline int sgn(DB x) {
	return (x > eps) - (x < -eps);
}

void solve() {
	int n;
	static int a[maxn];
	scanf("%d", &n);
	scanf("%d", a + n + 1);
	a[0] = 0;
	for(int i = 1; i <= n; ++i)
		scanf("%d", a + i);

	static DB lft[maxn], rht[maxn];
	lft[0] = 0;
	for(int i = 1; i <= n + 1; ++i)
		lft[i] = lft[i - 1] + (a[i] - a[i - 1]) / (DB)i;
	rht[n + 1] = 0;
	for(int i = n; i >= 0; --i)
		rht[i] = rht[i + 1] + (a[i + 1] - a[i]) / (DB)(n + 1 - i);
	DB ans = a[n + 1];
	for(int i = 0; i <= n; ++i) {
		// printf("%d: lft [%f, %f] rht [%f, %f]\n", i, lft[i], lft[i + 1], rht[i + 1], rht[i]);
		DB tL = max(lft[i], rht[i + 1]), tR = min(lft[i + 1], rht[i]);
		if(sgn(tL - tR) > 0)
			continue;
		DB dist = a[i + 1] - a[i];
		dist -= (tL - lft[i]) * (i + 1);
		dist -= (tL - rht[i + 1]) * (n + 1 - i);
		if(sgn(dist) < 0) {
			// puts("???");
			continue;
		}
		// printf("dist=%f\n", dist);
		DB tmp = tL + dist / (n + 2);
		if(sgn(tmp - tR) > 0) {
			// puts("????");
			continue;
		}
		ans = min(ans, tmp);
	}
	printf("%.20f\n", ans);
}

int main() {
	int T = 1;
	scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		// printf("Case #%d: ", Case);
		solve();
	}
	return 0;
}