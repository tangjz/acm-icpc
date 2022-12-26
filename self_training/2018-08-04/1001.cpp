#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e3 + 1, maxd = 10, maxs = 1 << maxd | 1;
int t, n, m, low, cnt[maxs], ans;
char buf[maxd + 1];
void dfs(int sel, int msk, int dist) {
	if(!sel) {
		ans += dist >= low;
		return;
	}
	dfs(sel >> 1, msk, dist);
	msk ^= sel;
	for(int i = msk; ; i = (i - 1) & msk) {
		dist -= cnt[i] * cnt[i | sel];
		cnt[i] += cnt[i | sel];
		if(!i)
			break;
	}
	dfs(sel >> 1, msk, dist);
	for(int i = msk; ; i = (i - 1) & msk) {
		cnt[i] -= cnt[i | sel];
		if(!i)
			break;
	}
}
int main() {
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		scanf("%d%d%d", &n, &m, &low);
		int all = 1 << m, dist = n * (n - 1) / 2;
		memset(cnt, 0, all * sizeof(int));
		while(n--) {
			int msk = 0;
			scanf("%s", buf);
			for(int i = 0; i < m; ++i)
				msk = msk << 1 | (buf[i] == 'A');
			dist -= cnt[msk]++;
		}
		ans = 0;
		dfs(all >> 1, all - 1, dist);
		printf("Case #%d: %d\n", Case, ans);
	}
	return 0;
}
