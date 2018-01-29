#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)5e6 + 1;
int tot, pr[maxn], d[maxn], seq[3];
LL lim, s[maxn];
bool vis[maxn];
LL iPow(LL x, int k) {
	LL ret = 1;
	for( ; k > 0; k >>= 1, x *= x)
		(k & 1) && (ret *= x);
	return ret;
}
LL dfs(int dep, LL val) {
	LL upp = lim / val;
	if(dep < 0)
		return val * s[upp];
	LL ret = 0, vLim = (LL)ceil(pow(upp, 1.0 / seq[dep]));
	for( ; pow(vLim, seq[dep]) <= 1e15 && iPow(vLim, seq[dep]) <= upp; ++vLim);
	for( ; pow(vLim, seq[dep]) > 1e15 || iPow(vLim, seq[dep]) > upp; --vLim);
	for(LL i = 1; i <= vLim; i += 4)
		if(!vis[i] && d[i] == i) {
			vis[i] = 1;
			ret += dfs(dep - 1, val * iPow(i, seq[dep]));
			vis[i] = 0;
		}
	return ret;
}
int main() {
	s[1] = 1;
	for(int i = 2; i < maxn; ++i) {
		if(!d[i])
			pr[tot++] = d[i] = i;
		for(int j = 0, k; (k = i * pr[j]) < maxn; ++j) {
			d[k] = pr[j];
			if(d[i] == pr[j])
				break;
		}
		bool chk = 1;
		for(int tmp = i; tmp > 1 && (chk &= d[tmp] == 2 || (d[tmp] & 3) == 3); tmp /= d[tmp] == 2 ? d[tmp] : d[tmp]);
		s[i] = s[i - 1] + (chk ? i : 0);
	}
	while(scanf("%lld", &lim) == 1) {
		LL ans = 0;
		seq[0] = 52;
		ans += dfs(0, 1);
		seq[0] = 1, seq[1] = 17;
		ans += dfs(1, 1);
		seq[0] = 2, seq[1] = 10;
		ans += dfs(1, 1);
		seq[0] = 3, seq[1] = 7;
		ans += dfs(1, 1);
		seq[0] = 1, seq[1] = 2, seq[2] = 3;
		ans += dfs(2, 1);
		printf("%lld\n", ans);
	}
	return 0;
}
