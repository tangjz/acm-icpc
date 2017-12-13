#include <bits/stdc++.h>
using namespace std;
const int maxn = 100001, maxm = 15, maxs = 1 << maxm | 1, mod = (int)1e9 + 7;
int t, n, m, all, pw[maxn], bits[maxs], cnt[maxs], f[maxs];
void dfs(int sel, int msk, int ways) { // 0: any, 1: strict
	if(sel > all) {
		f[msk] = bits[msk] && ways ? mod - ways : ways;
		return;
	}
	dfs(sel << 1, msk, ways);
	msk ^= sel;
	for(int i = msk; ; i = (i - 1) & msk) { // merge by any log(sel)-bit
		(ways -= pw[cnt[i]] - 1) < 0 && (ways += mod);
		(ways -= pw[cnt[i | sel]] - 1) < 0 && (ways += mod);
		cnt[i] += cnt[i | sel];
		(ways += pw[cnt[i]] - 1) >= mod && (ways -= mod);
		if(!i)
			break;
	}
	dfs(sel << 1, msk, ways);
	for(int i = msk; ; i = (i - 1) & msk) {
		cnt[i] -= cnt[i | sel];
		if(!i)
			break;
	}
}
int main() {
	pw[0] = 1;
	for(int i = 1; i < maxn; ++i)
		(pw[i] = pw[i - 1] << 1) >= mod && (pw[i] -= mod);
	for(int i = 1; i < maxs; ++i)
		bits[i] = bits[i >> 1] ^ (i & 1);
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		scanf("%d%d", &n, &m);
		all = (1 << m) - 1;
		memset(cnt, 0, (all + 1) * sizeof(int));
		while(n--) {
			int msk = 0;
			static char buf[maxm + 2];
			scanf("%s", buf);
			for(int i = 0; i < m; ++i)
				msk |= (buf[i] == 'Y') << i;
			++cnt[msk];
		}
		int ways = 0;
		for(int i = 0; i <= all; ++i)
			(ways += pw[cnt[i]] - 1) >= mod && (ways -= mod);
		dfs(1, all, ways);
		for(int i = 1; i <= all; i <<= 1)
			for(int msk = all ^ i, j = msk; ; j = (j - 1) & msk) {
				(f[j | i] += f[j]) >= mod && (f[j | i] -= mod);
				if(!j)
					break;
			}
		int ans = 0;
		for(int i = 1; i <= all; ++i)
			ans ^= f[i];
		printf("Case #%d: %d\n", Case, ans);
	}
	return 0;
}
