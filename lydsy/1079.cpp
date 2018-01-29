#include <bits/stdc++.h>
const int maxs = 6 << 20 | 1, mod = (int)1e9 + 7;
int f[maxs];
int dfs(int msk) {
	if(f[msk] != -1)
		return f[msk];
	int pre = msk >> 20, rem = msk ^ (pre << 20);
	if(!rem)
		return 1;
	long long ways = 0;
	for(int i = 0, pcnt; i < 5; ++i, rem >>= 4) {
		int cnt = rem & 15, coeff = cnt - (i + 1 < 5 && pre == i + 1);
		if(coeff > 0) {
			int nmsk = msk ^ ((pre ^ i) << 20) ^ ((cnt ^ (cnt - 1)) << (i << 2)) ^ (i ? ((pcnt ^ (pcnt + 1)) << ((i - 1) << 2)) : 0);
			ways += (long long)coeff * dfs(nmsk);
		}
		pcnt = cnt;
	}
	return f[msk] = ways % mod;
}
int main() {
	int k, x, cnt[5] = {};
	scanf("%d", &k);
	while(k--) {
		scanf("%d", &x);
		++cnt[--x];
	}
	memset(f, -1, sizeof f);
	x = 5;
	for(int i = 4; i >= 0; --i)
		x = x << 4 | cnt[i];
	printf("%d\n", dfs(x));
	return 0;
}
