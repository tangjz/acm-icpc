#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 51;
int n;
LL e[maxn], f[maxn];
char buf[maxn];
LL dfs(LL msk) {
	if(!msk)
		return 1;
	static int tot, pos[maxn], upp, deg[maxn];
	static LL val[maxn];
	tot = upp = 0;
	for(LL rem = msk; rem; rem ^= val[tot++]) {
		val[tot] = rem & -rem;
		pos[tot] = __builtin_ctzll(val[tot]);
		deg[tot] = __builtin_popcountll(msk & e[pos[tot]]);
		if(!deg[tot])
			return dfs(msk ^ val[tot]) << 1;
		if(deg[upp] < deg[tot])
			upp = tot;
	}
	if(deg[upp] >= 3) {
		msk ^= val[upp];
		return dfs(msk ^ (msk & e[pos[upp]])) + dfs(msk);
	}
	LL ret = 1, vis = 0;
	static int ord[maxn], que[maxn];
	for(int i = 0; i < tot; ++i)
		ord[pos[i]] = i;
	for(int i = 0; i < tot; ++i) {
		if(vis & val[i])
			continue;
		int cnt = 0;
		bool hasEnd = 0;
		vis |= val[i];
		hasEnd |= deg[i] == 1;
		que[cnt++] = i;
		for(int j = 0; j < cnt; ++j) {
			int u = que[j], v;
			for(LL rem = (msk ^ vis) & e[pos[u]]; rem; rem ^= val[v]) {
				v = ord[__builtin_ctzll(rem & -rem)];
				vis |= val[v];
				hasEnd |= deg[v] == 1;
				que[cnt++] = v;
			}
		}
		ret *= hasEnd ? f[cnt] : f[cnt - 1] + f[cnt - 3];
	}
	return ret;
}
int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; ++i) {
		scanf("%s", buf);
		buf[i] = '1';
		for(int j = n - 1; j >= 0; --j)
			e[i] = e[i] << 1 | (buf[j] == '0');
	}
	f[0] = 1;
	f[1] = 2;
	for(int i = 2; i <= n; ++i)
		f[i] = f[i - 1] + f[i - 2];
	printf("%lld\n", dfs((1LL << n) - 1));
	return 0;
}
