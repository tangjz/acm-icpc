#include <bits/stdc++.h>
using namespace std;

typedef unsigned int UL;
typedef long long LL;
typedef unsigned long long ULL;
typedef	double DB;
typedef long double LD;

const int mod = (int)1e9 + 7, maxd = 10, maxc = 26;
const int maxn = (int)3e5 + 1, maxm = (int)2e6 + 1;
const DB eps = 1e-9, pi = acos((DB)-1);

inline int sgn(DB x) {
	return (x > eps) - (x < -eps);
}

void solve() {
	int n, m;
	static char buf[maxn];
	scanf("%d%d%s", &n, &m, buf);

	int ans = 0, tot = 0;
	static pair<int, int> arr[maxn];
	for(int i = 0, j; i < n; ) {
		if(buf[i] == 'W') {
			++ans;
			if(i > 0 && buf[i - 1] == 'W')
				++ans;
			++i;
			continue;
		}
		for(j = i; j < n && buf[j] != 'W'; ++j);
		int fir = (i > 0) + (j < n);
		int sec = j - i;
		// printf("%d %d: %d %d\n", i, j, fir, sec);
		arr[tot++] = {-fir, sec};
		i = j;
	}
	// full: 2t+1
	// half: 2t
	// none: 2t-1
	if(tot == 1 && !arr[0].first) {
		// none
		int adt = min(arr[0].second, m);
		if(adt > 0)
			ans += adt + adt - 1;
	} else {
		sort(arr, arr + tot);
		int rem = 0;
		for(int i = 0; i < tot; ++i) {
			int fir = -arr[i].first;
			int sec = arr[i].second;
			if(m >= sec) {
				// full or half
				// printf("%d %d\n", fir, sec);
				ans += sec + sec - 1 + fir;
				m -= sec;
			} else {
				rem += sec;
			}
		}
		// half
		int adt = min(rem, m);
		if(adt > 0)
			ans += adt + adt;
	}
	printf("%d\n", ans);
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