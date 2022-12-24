#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
inline LL calc(int n, LL m) {
	return m & 1 ? !(m & 2) : (m + !!(m & 2));
}
inline LL calc(int n, int x, LL l, LL r, LL t) {
	LL cnt = r - l + 1, all = 1LL << (n - x);
	if(cnt == all)
		return 0;
	l = (l + (t >> x)) & (all - 1);
	r = (r + (t >> x)) & (all - 1);
	LL ret = calc(n - x, r) ^ (l ? calc(n - x, l - 1) : 0);
	return (ret << x | (cnt & 1 ? t & ((1LL << x) - 1) : 0)) & ((1LL << (n - 1)) - 1);
}
inline LL solve(int n, int x, LL l, LL r, LL t) {
	if(n <= 1)
		return 0;
	LL mask = (1LL << (n - x)) - 1;
	LL pL = (l - 1) >> (n - x), qL = (l - 1) & mask;
	LL pR = (r - 1) >> (n - x), qR = (r - 1) & mask;
	if(pL == pR)
		return calc(n, x, qL, qR, pL + 1 + t);
	return calc(n, x, qL, mask, pL + 1 + t) ^ calc(n, x, 0, qR, pR + 1 + t);
}
int main() {
	int m, n, BASE;
	LL x, l, r, t, ans;
	scanf("%d%d%lld%lld%lld%lld%d", &m, &n, &x, &l, &r, &t, &BASE);
	ans = solve(n, x % n, l, r, t);
	for(int i = 1; i < m; ++i) {
		n = (ans + i - 1) % 5 + BASE;
		LL mask = (1LL << n) - 1, half = (1LL << (n >> 1)) - 1;
		l = ((ans + ans + l + i - 1) & mask) + 1;
		r = ((ans + 1 + ((l & half) << (n >> 1))) & mask) + 1;
		if(l > r)
			swap(l, r);
		x = (r - l + t + i - 1) & mask;
		t = (l + r) & mask;
		ans = solve(n, x % n, l, r, t);
	}
	printf("%lld\n", ans);
	return 0;
}