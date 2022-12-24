#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ULL;
const int maxs = (int)1e4 + 1, mod = (int)1e9 + 7;
int n, m, BMSK, tot, nxt[4][maxs], o, dp[2][maxs];
pair<int, ULL> que[maxs];
map<pair<int, ULL>, int> Hash;
inline void mod_inc(int &x, int y) {
	(x += y) >= mod && (x -= mod);
}
inline int getID(int u, ULL v) {
	que[tot] = make_pair(u, v);
	map<pair<int, ULL>, int>::iterator it = Hash.find(que[tot]);
	if(it != Hash.end())
		return it -> second;
	nxt[0][tot] = nxt[1][tot] = nxt[2][tot] = nxt[3][tot] = -1;
	Hash.insert(make_pair(que[tot], tot));
	return tot++;
}
inline int nxtID(int x, int k) {
	if(nxt[k][x] != -1)
		return nxt[k][x];
	int S = que[x].first, T = (S << 1 | (k & 1)) & BMSK;
	ULL f = que[x].second, g = 0;
	while(f != 0) {
		ULL lbt = f & -f;
		f ^= lbt;
		int tmp = 63 - __builtin_clzll(lbt);
		if((tmp >> (n - 1)) & 1) {
			g |= 1ULL << ((tmp << 1) & BMSK);
			if((k & 2) && !(tmp & 1) && (S & 1) != (k & 1))
				g |= 1ULL << ((tmp << 1 | 3) & BMSK);
		} else if(((S >> (n - 1)) & 1) != (k & 1)) {
			g |= 1ULL << (tmp << 1 | 1);
		}
	}
	return nxt[k][x] = getID(T, g);
}
int main() {
	scanf("%d%d", &n, &m);
	BMSK = (1 << n) - 1;
	for(int i = 0; i <= BMSK; ++i) {
		ULL f = 1;
		for(int j = n - 2; j >= 0; --j) {
			ULL g = 0;
			while(f != 0) {
				ULL lbt = f & -f;
				f ^= lbt;
				int tmp = 63 - __builtin_clzll(lbt);
				g |= 1ULL << (tmp << 1);
				if(!(tmp & 1) && ((i >> j) & 1) != ((i >> (j + 1)) & 1))
					g |= 1ULL << (tmp << 1 | 3);
			}
			f = g;
		}
		mod_inc(dp[o][getID(i, f)], 1);
	}
	for(int i = 1; i < m; ++i) {
		for(int j = 0; j < n; ++j) {
			o = !o;
			memset(dp[o], 0, tot * sizeof(int));
			for(int x = 0, k = (j > 0) << 1; x < tot; ++x) {
				if(!dp[!o][x])
					continue;
				mod_inc(dp[o][nxtID(x, k)], dp[!o][x]);
				mod_inc(dp[o][nxtID(x, k | 1)], dp[!o][x]);
			}
		}
	}
	int ans = 0;
	for(int i = 0; i < tot; ++i)
		if((que[i].second >> BMSK) & 1)
			mod_inc(ans, dp[o][i]);
	printf("%d\n", ans);
	return 0;
}