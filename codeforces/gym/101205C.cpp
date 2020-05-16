#include <bits/stdc++.h>
using namespace std;
const int maxn = 21, maxs = 1 << 20 | 1, INF = 0x3f3f3f3f;
int bits[maxs], n, m, e[maxn][maxn], f[maxs][maxn];
int main() {
	for(int i = 1; i < maxs; ++i)
		bits[i] = bits[i >> 1] + (i & 1);
	for(int Case = 1; scanf("%d%d", &n, &m) == 2; ++Case) {
		memset(e, 0x3f, sizeof e);
		memset(f, 0x3f, sizeof f);
		while(m--) {
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			if(e[u][v] <= w)
				continue;
			e[u][v] = e[v][u] = w;
		}
		for(int i = 0; i < n; ++i)
			e[i][i] = 0;
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j)
				for(int k = 0; k < n; ++k)
					e[j][k] = min(e[j][k], e[j][i] + e[i][k]);
		int half = (n + 1) >> 1, lft = 1 << 0, rht = 1 << (n - 1);
		f[lft][0] = f[rht][n - 1] = 0;
		for(int i = 0; i < 1 << n; ++i) {
			if(bits[i] > half || ((i & lft) && (i & rht)))
				continue;
			for(int j = 0; j < n; ++j) {
				if(f[i][j] == INF)
					continue;
				for(int k = 0; k < n; ++k)
					if(!((i >> k) & 1))
						f[i | 1 << k][k] = min(f[i | 1 << k][k], f[i][j] + e[j][k]);
			}
		}
		int ans = INF;
		for(int i = 0; i < 1 << n; ++i) {
			if(!(i & lft) || (i & rht) || bits[i] != half)
				continue;
			int S = ((1 << n) - 1) ^ i, T = i;
			int mx1 = INF, mx2 = INF;
			for(int j = 0; j < n; ++j) {
				if(!((S >> j) & 1))
					continue;
				for(int k = 0; k < n; ++k) {
					if(!((T >> k) & 1))
						continue;
					mx2 = (int)min((long long)mx2, (long long)f[S][j] + f[T][k] + e[j][k]);
				}
			}
			S ^= lft ^ rht;
			T ^= lft ^ rht;
			for(int j = 0; j < n; ++j) {
				if(!((S >> j) & 1))
					continue;
				for(int k = 0; k < n; ++k) {
					if(!((T >> k) & 1))
						continue;
					mx1 = (int)min((long long)mx1, (long long)f[S][j] + f[T][k] + e[j][k]);
				}
			}
			ans = min(ans, mx1 + mx2);
		}
		printf("Case %d: %d\n", Case, ans);
	}
	return 0;
}
