#include <bits/stdc++.h>
using namespace std;
 
typedef unsigned int UL;
typedef long long LL;
typedef unsigned long long ULL;
typedef	double DB;
typedef long double LD;
 
const int mod = (int)1e9 + 7, maxd = 61, maxc = 26;
const int maxn = (int)5e5 + 1, maxm = (int)2e6 + 1;
const DB eps = 1e-9, pi = acos((DB)-1);
 
inline int sgn(DB x) {
	return (x > eps) - (x < -eps);
}
 
inline void modInc(int &x, int y) {
	(x += y) >= mod && (x -= mod);
}
 
void solve() {
	int n, mx = 0;
	static int cnt[maxd], upp[maxd];
	static LL a[maxn];
	scanf("%d", &n);
	for(int i = 0; i < n; ++i) {
		scanf("%lld", a + i);
		LL tmp = a[i];
		for(int j = 0; tmp > 0; ++j, tmp >>= 1) {
			if(j == mx)
				cnt[mx++] = 0;
			cnt[j] += tmp & 1;
		}
	}
	for(int i = 0; i < mx; ++i) {
		LL mul = (1LL << i) % mod;
		cnt[i] = mul * cnt[i] % mod;
		upp[i] = mul * n % mod;
	}
	int ans = 0;
	for(int i = 0; i < n; ++i) {
		int lft = 0, rht = 0;
		LL tmp = a[i];
		for(int j = 0; j < mx; ++j, tmp >>= 1)
			if(tmp & 1) {
				modInc(lft, cnt[j]);
				modInc(rht, upp[j]);
			} else {
				modInc(rht, cnt[j]);
			}
		ans = (ans + (LL)lft * rht) % mod;
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