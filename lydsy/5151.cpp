#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxd = 10, maxl = 11, maxs = 47, maxv = (int)5e4 + 1;
set<LL> sp;
LL bit[maxd + 1];
bool vis[maxd + 1][maxs];
void dfs(int dep, int cnt, int sum, LL mask) {
	if(dep == maxd) {
		if(!(sum & 1) && vis[dep - 1][sum >> 1])
			sp.insert(mask);
		return;
	}
	memcpy(vis[dep], vis[dep - 1], sizeof vis[0]);
	dfs(dep + 1, cnt, sum, mask);
	while(cnt < maxl) {
		for(int j = maxs - 1; j >= dep; --j)
			vis[dep][j] |= vis[dep][j - dep];
		dfs(dep + 1, ++cnt, sum += dep, mask += bit[dep]);
	}
}
map<LL, int> f[maxl];
int calc(int len, LL msk) {
	if(len == 0)
		return sp.count(msk);
	if(f[len].count(msk))
		return f[len][msk];
	int ret = 0;
	for(int i = 0; i < maxd; ++i)
		ret += calc(len - 1, msk + bit[i]);
	return f[len][msk] = ret;
}
LL solve(LL lim) {
	char dig[maxl];
	int len = sprintf(dig, "%lld", lim);
	LL ret = 0, mask = 0;
	for(int i = 0; i < len; ++i) {
		dig[i] -= '0';
		for(int j = 0; j < dig[i]; ++j)
			ret += calc(len - i - 1, mask + bit[j]);
		mask += bit[dig[i]];
	}
	return ret;
}
int main() {
	bit[1] = 1;
	for(int i = 2; i < maxd; ++i)
		bit[i] = bit[i - 1] << 4;
	vis[0][0] = 1;
	dfs(1, 0, 0, 0);
	int t;
	scanf("%d", &t);
	while(t--) {
		LL L, R;
		scanf("%lld%lld", &L, &R);
		printf("%lld\n", solve(R + 1) - solve(L));
	}
	return 0;
}
