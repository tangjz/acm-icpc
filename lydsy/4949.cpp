#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 51, maxp = 4, maxs = 325, maxd = 1 << 21, num[maxp] = {5, 5, 4, 4};
int n, sz[maxp], lim[maxp][maxn], bits[maxd | 1], ban, sel[maxp + 1], tot, ans[maxs];
char buf[5];
bool dfs(int dep, int msk, int rem) {
	if(dep == maxp)
		return 1;
	if(bits[msk] == num[dep]) {
		for(int i = 0; i < sz[dep]; ++i)
			if((bits[msk & lim[dep][i]] > 0) != ((lim[dep][i] & maxd) > 0))
				return 0;
		ban ^= msk ^ sel[dep];
		int ret = dfs(dep + 1, sel[dep + 1], ~ban);
		ban ^= msk ^ sel[dep];
		return ret;
	}
	while(1) {
		int lbt = rem & -rem;
		if(lbt >= maxd)
			break;
		if(dfs(dep, msk | lbt, rem ^= lbt))
			return 1;
	}
	return 0;
}
inline int nextp(int curp) {
	return curp + 1 < maxp ? curp + 1 : 0;
}
int main() {
	int i, j, k, msk;
	scanf("%d", &n);
	for(i = 0; i < 5; ++i) {
		scanf("%s", buf);
		sel[0] |= 1 << (buf[0] - 'A');
	}
	for(i = 0; i < n; ++i) {
		for(j = 0, msk = 0; j < 3; ++j) {
			scanf("%s", buf);
			msk |= 1 << (buf[0] - 'A');
		}
		for(j = 1, k = nextp(i % maxp); j < maxp; ++j, k = nextp(k)) {
			scanf("%s", buf);
			if(buf[0] == '-') {
				lim[k][sz[k]++] = msk;
			} else {
				if(buf[0] == '*')
					lim[k][sz[k]++] = msk | maxd;
				else
					sel[k] |= 1 << (buf[0] - 'A');
				break;
			}
		}
	}
	for(i = 0; i < maxp; ++i) {
		ban |= sel[i];
		sort(lim[i], lim[i] + sz[i]);
		sz[i] = unique(lim[i], lim[i] + sz[i]) - lim[i];
	}
	for(i = 1; i < maxd; ++i)
		bits[i] = bits[i >> 1] + (i & 1);
	for(i = 0; i < 6; ++i)
		if(~ban & (1 << i))
			for(j = 6; j < 12; ++j)
				if(~ban & (1 << j))
					for(k = 12; k < 21; ++k)
						if(~ban & (1 << k)) {
							msk = (1 << i) + (1 << j) + (1 << k);
							ban ^= msk;
							if(dfs(1, sel[1], ~ban))
								ans[tot++] = msk;
							ban ^= msk;
						}
	for(i = 0; i < 6; ++i) {
		for(j = 0; j < tot; ++j)
			if(~ans[j] & (1 << i))
				break;
		if(j == tot) {
			buf[0] = 'A' + i;
			break;
		}
	}
	if(i == 6)
		buf[0] = '?';
	for(i = 6; i < 12; ++i) {
		for(j = 0; j < tot; ++j)
			if(~ans[j] & (1 << i))
				break;
		if(j == tot) {
			buf[1] = 'A' + i;
			break;
		}
	}
	if(i == 12)
		buf[1] = '?';
	for(i = 12; i < 21; ++i) {
		for(j = 0; j < tot; ++j)
			if(~ans[j] & (1 << i))
				break;
		if(j == tot) {
			buf[2] = 'A' + i;
			break;
		}
	}
	if(i == 21)
		buf[2] = '?';
	buf[3] = '\0';
	puts(buf);
	return 0;
}