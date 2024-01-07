#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 101, mod = (int)1e9 + 7;
int t, n, pL[maxn], pR[maxn];
inline int mod_inv(int x) {
	return x <= 1 ? x : mod - (int)(mod / x * (LL)mod_inv(mod % x) % mod);
}
int solve(int adt, int lim) {
	int ret = 1;
	for(int i = 0; i < n; ++i) {
		int low = pL[i], upp = min(pR[i], lim);
		if(low > upp)
			return 0;
		int tmp = (upp - low + 1LL) * (adt - low + adt - upp) / 2 % mod;
		ret = (LL)ret * tmp % mod;
	}
	return ret;
}
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		int low = 0, upp = 0, dom = 1;
		for(int i = 0; i < n; ++i) {
			scanf("%d%d", pL + i, pR + i);
			low = max(low, pL[i]);
			upp = max(upp, pR[i]);
			dom = dom * (pR[i] - pL[i] + 1LL) % mod;
		}
		int ans = 0;
		for( ; low <= upp; ++low) {
			int val = solve(low + 1, low) - solve(low + 1, low - 1);
			val < 0 && (val += mod);
			(ans += val) >= mod && (ans -= mod);
		}
		ans = (LL)ans * mod_inv(dom) % mod;
		printf("%d\n", ans);
	}
	return 0;
} 
