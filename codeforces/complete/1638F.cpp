#include <bits/stdc++.h>
using namespace std;

typedef signed i32;
typedef unsigned u32;
typedef long long i64;
typedef unsigned long long u64;
// typedef __int128_t i128;
// typedef __uint128_t u128;
typedef float f32;
typedef double f64;
typedef long double f128;

const int maxn = (int)1e4 + 3, maxm = (int)4e6 + 1;
const int maxd = 21, maxc = 26;
const int mod = (int)1e9 + 7, INF = 0x3f3f3f3f;
const f64 pi = acos((f64)-1), eps = 1e-12;

inline int sgn(f64 x) {
	return (x > eps) - (x < -eps);
}

void solve() {
	int n;
    scanf("%d", &n);
	static i64 h[maxn], pre[maxn];
	static int pL[maxn], pR[maxn];
	h[0] = h[n + 1] = pre[0] = 0;
	for(int i = 1; i <= n; ++i) {
		scanf("%lld", h + i);
		for(pL[i] = i - 1; h[pL[i]] >= h[i]; pL[i] = pL[pL[i]]);
		pre[i] = pre[i - 1];
		for(int L = pL[i], preL = i; preL > 0; preL = L, L = pL[L])
			pre[i] = max(pre[i], (i - L) * h[preL]);
	}
	i64 ans = 0;
	for(int i = n; i >= 1; --i) {
		for(pR[i] = i + 1; h[pR[i]] >= h[i]; pR[i] = pR[pR[i]]);
		ans = max(ans, (pR[i] - pL[i] - 1) * h[i]);
		{ // bound any any
			int L = pL[i], preL = i;
			int R = i;
			stack<int> preR;
			while(R <= n) {
				preR.push(R);
				R = pR[R];
			}
			while(L > 0) {
				preL = L;
				L = pL[L];
				while(h[preR.top()] <= h[i] - h[preL]) {
					R = preR.top();
					preR.pop();
				}
				i64 rht = (R - pL[i] - 1) * (h[i] - h[preL]);
				if(R <= n)
					rht = max(rht, (pR[R] - pL[i] - 1) * h[R]);
				ans = max(ans, (pR[i] - L - 1) * h[preL] + rht);
			}
		}
		{ // any any bound
			int R = pR[i], preR = i;
			int L = i;
			stack<int> preL;
			while(L > 0) {
				preL.push(L);
				L = pL[L];
			}
			ans = max(ans, pre[i - 1] + (R - i) * h[preR]);
			while(R <= n) {
				preR = R;
				R = pR[R];
				ans = max(ans, pre[i - 1] + (R - i) * h[preR]);
				while(h[preL.top()] <= h[i] - h[preR]) {
					L = preL.top();
					preL.pop();
				}
				i64 lft = (pR[i] - L - 1) * (h[i] - h[preR]);
				if(L > 0)
					lft = max(lft, (pR[i] - pL[L] - 1) * h[L]);
				ans = max(ans, lft + (R - pL[i] - 1) * h[preR]);
			}
		}
		{ // same bound same
			int L = pL[i], preL = i;
			int R = pR[i], preR = i;
			i64 cur = h[i];
			while(true) {
				ans = max(ans, (R - L - 1) * cur + (pR[i] - pL[i] - 1) * (h[i] - cur));
				if(L <= 0 && R > n)
					break;
				if(h[L] > h[R]) {
					cur = h[L];
					preL = L;
					L = pL[L];
				} else {
					cur = h[R];
					preR = R;
					R = pR[R];
				}
			}
		}
	}
	printf("%lld\n", ans);
}

int main() {
	int T = 1;
	// scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		// printf("Case #%d: ", Case);
		// printf("%d\n", solve());
		solve();
	}
	return 0;
}