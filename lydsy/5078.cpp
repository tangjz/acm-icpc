#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 40, maxs = 3276800;
int n, m, rk, bel[maxn + 1];
LL vec[maxn + 1];
char buf[maxn + 1];
int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; ++i) {
		scanf("%s", buf);
		for(int j = maxn - 1; j >= 0; --j)
			vec[i] = vec[i] << 1 | (buf[j] == '1');
	}
	memset(bel, -1, sizeof bel);
	for(int i = 0; i < maxn; ++i) {
		for(int j = rk; j < n; ++j)
			if(((vec[j] >> i) & 1)) {
				swap(vec[rk], vec[j]);
				break;
			}
		if(!((vec[rk] >> i) & 1))
			continue;
		bel[i] = rk;
		for(int j = 0; j < n; ++j)
			if(j != rk && ((vec[j] >> i) & 1))
				vec[j] ^= vec[rk];
		if((++rk) == n)
			break;
	}
	scanf("%d%s", &m, buf);
	LL ans = 0;
	if(((maxn - m + 1LL) << rk) <= (((m + 1LL) * maxn) << (maxn - rk))) {
		LL pat = 0, msk = (1LL << m) - 1;
		for(int i = m - 1; i >= 0; --i)
			pat = pat << 1 | (buf[i] == '1');
		LL val = 0, tmp;
		ans += !pat;
		for(int i = 1, j; i < (1 << rk); ++i) {
			for(j = 0, tmp = i; ; ++j, tmp >>= 1) {
				val ^= vec[j];
				if(tmp & 1)
					break;
			}
			for(j = m, tmp = val; j <= maxn; ++j, tmp >>= 1)
				if(pat == (tmp & msk)) {
					++ans;
					break;
				}
		}
	} else {
		static int f[maxn + 1], nxt[maxn + 1][2];
		f[0] = 0;
		for(int i = 1, j = 0; i < m; ++i) {
			for( ; j && buf[j] != buf[i]; j = f[j]);
			f[i + 1] = buf[j] == buf[i] ? ++j : 0;
		}
		for(int i = 0; i < m; ++i) {
			int j = buf[i] - '0', k = i;
			for( ; k && buf[k] == buf[i]; k = f[k]);
			nxt[i][j] = i + 1;
			nxt[i][!j] = buf[k] != buf[i] ? ++k : 0;
		}
		static int idx[maxn + 1], msk[maxn + 1];
		for(int i = maxn - 1, tot = 0; i >= 0; --i)
			if(bel[i] == -1) {
				idx[i] = tot++;
			} else {
				msk[i] = 0;
				for(int j = i + 1; j < maxn; ++j)
					if((vec[bel[i]] >> j) & 1)
						msk[i] |= 1 << idx[j];
			}
		int o = 0, len = maxn - rk, all = m << len;
		static LL dp[2][maxs + 1];
		memset(dp[o], 0, all * sizeof(LL));
		dp[o][0] = 1;
		for(int i = 0, rem = rk; i < maxn; ++i) {
			o = !o;
			memset(dp[o], 0, all * sizeof(LL));
			bool upd = 0;
			if(bel[i] != -1) {
				--rem;
				for(int j = 0; j < all; ++j) {
					if(!dp[!o][j])
						continue;
					upd = 1;
					int u = j >> len;
					if(nxt[u][0] == m) {
						ans += dp[!o][j] << rem;
					} else {
						dp[o][j ^ ((u ^ nxt[u][0]) << len)] += dp[!o][j];
					}
					if(nxt[u][1] == m) {
						ans += dp[!o][j] << rem;
					} else {
						dp[o][j ^ ((u ^ nxt[u][1]) << len | msk[i])] += dp[!o][j];
					}
				}
			} else {
				for(int j = 0; j < all; ++j) {
					if(!dp[!o][j])
						continue;
					upd = 1;
					int u = j >> len, ch = (j >> idx[i]) & 1;
					if(nxt[u][ch] == m) {
						ans += dp[!o][j] << rem;
					} else {
						dp[o][j ^ ((u ^ nxt[u][ch]) << len)] += dp[!o][j];
					}
				}
			}
			if(!upd)
				break;
		}
	}
	ans <<= n - rk;
	printf("%lld\n", ans);
	return 0;
}