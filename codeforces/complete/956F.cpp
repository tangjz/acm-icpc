#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxd = 10, maxl = 18, maxs = 81, BLEN = 5, BMSK = 31, maxv = 32175, maxv2 = 191791;
int htot, cnt[maxv], inc[maxv][maxd + 1], sub[maxv][maxd + 1], ptot, pos[maxl + 1][maxv];
map<LL, int> Hash;
LL bit[maxd + 1], c[2][maxl + 1];
LL seq[maxv], f[maxv2][maxd + 1][maxd - 1];
bitset<maxs + 1> vis[maxd + 1];
inline int getID(LL msk) {
	map<LL, int>::iterator it = Hash.find(msk);
	if(it != Hash.end())
		return it -> second;
	seq[htot] = msk;
	return Hash[msk] = htot++;
}
void dfs(int dep, int cnt, int sum, LL msk) {
	if(dep == maxd) {
		for(int i = sum >> 1; i >= 0; --i)
			if(vis[dep - 1].test(i)) {
				int dif = sum - i - i;
				if(dif > 1) {
					int idx = getID(msk);
					pos[0][idx] = idx;
					f[idx][maxd - 1][dif - 1] = 1;
				}
				break;
			}
		return;
	}
	vis[dep] = vis[dep - 1];
	dfs(dep + 1, cnt, sum, msk);
	while(cnt < maxl) {
		vis[dep] |= vis[dep] << dep;
		dfs(dep + 1, ++cnt, sum += dep, msk += bit[dep]);
	}
}
LL solve(LL lim, int dif) {
	if(dif >= maxd - 1)
		return lim;
	char dig[maxl + 3];
	int len = sprintf(dig, "%lld", lim), hidx = getID(0), part = 0;
	LL ret = lim;
	for(int i = 0; i < len; ++i) {
		dig[i] -= '0';
		if(!dif) {
			int odd = dig[i] >> 1, even = (dig[i] + 1) >> 1;
			ret -= c[part][len - 1 - i] * odd + c[part ^ 1][len - 1 - i] * even;
			part ^= dig[i] & 1;
		}
		if(hidx >= 0) {
			if(len - i > maxl) {
				for(int j = 0; j < dig[i]; ++j) {
					int hidx2 = inc[hidx][j];
					if(hidx2 >= 0) {
						int pidx = pos[len - i - 1][hidx2];
						if(pidx >= 0)
							ret -= f[pidx][maxd - 1][dif];
					}
				}
			} else if(dig[i]) {
				int pidx = pos[len - i][hidx];
				if(pidx >= 0)
					ret -= f[pidx][dig[i] - 1][dif];
			}
			hidx = inc[hidx][dig[i]];
		}
	}
	return ret;
}
int main() {
	bit[1] = 1;
	for(int i = 2; i < maxd; ++i)
		bit[i] = bit[i - 1] << BLEN;
	c[0][0] = 1;
	for(int i = 0; i < maxl; ++i) {
		int odd = maxd >> 1, even = (maxd + 1) >> 1;
		c[0][i + 1] = c[0][i] * even + c[1][i] * odd;
		c[1][i + 1] = c[0][i] * odd + c[1][i] * even;
	}
	memset(inc, -1, sizeof inc);
	memset(sub, -1, sizeof sub);
	memset(pos, -1, sizeof pos);
	vis[0].set(0);
	dfs(1, 0, 0, 0);
	ptot = htot;
	for(int i = 0; i < htot; ++i) {
		LL msk = seq[i], tmp = msk;
		inc[i][0] = sub[i][0] = i;
		for(int j = 1; j < maxd; ++j, tmp >>= BLEN) {
			int rem = tmp & BMSK;
			if(!rem)
				continue;
			cnt[i] += rem;
			int idx = getID(msk - bit[j]);
			inc[idx][j] = i;
			sub[i][j] = idx;
		}
	}
	for(int i = 0; i <= maxl; ++i) {
		for(int hidx = 0; hidx < htot; ++hidx) {
			int pidx = pos[i][hidx];
			if(pidx < 0)
				continue;
			for(int k = 1; k < maxd; ++k)
				for(int d = 1; d < maxd - 1; ++d)
					f[pidx][k][d] += f[pidx][k - 1][d];
			if(i + cnt[hidx] < maxl) {
				int pidx2 = pos[i + 1][hidx];
				if(pidx2 < 0)
					pos[i + 1][hidx] = pidx2 = ptot++;
				for(int d = 0; d < maxd - 1; ++d)
					f[pidx2][0][d] += f[pidx][maxd - 1][d];
			}
			for(int k = 1; k < maxd; ++k) {
				int hidx2 = sub[hidx][k];
				if(hidx2 < 0)
					continue;
				int pidx2 = pos[i + 1][hidx2];
				if(pidx2 < 0)
					pos[i + 1][hidx2] = pidx2 = ptot++;
				for(int d = 1; d < maxd - 1; ++d)
					f[pidx2][k][d] += f[pidx][maxd - 1][d];
			}
			for(int k = 0; k < maxd; ++k) {
				for(int d = 1; d < maxd - 1; d += 2)
					f[pidx][k][0] += f[pidx][k][d];
				for(int d = maxd - 2; d > 1; --d)
					f[pidx][k][d - 1] += f[pidx][k][d];
			}
		}
	}
	int t;
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		LL L, R;
		int k;
		scanf("%lld%lld%d", &L, &R, &k);
		printf("%lld\n", solve(R + 1, k) - solve(L, k));
	}
	return 0;
}
