#include <bits/stdc++.h>
using namespace std;
typedef unsigned int UL;
typedef long long LL;
typedef unsigned long long ULL;
typedef double DB;
typedef long double LDB;
const int maxn = 15, maxd = 1 << 15 | 1, mod = (int)1e9 + 7, INF = 0x3f3f3f3f;
const LL INFLL = 0x3f3f3f3f3f3f3f3fLL;
const DB pi = acos((DB)-1);
int n, a[maxn], s[maxd], ord[maxd], sz[maxd][maxn];
struct Info {
	int val : 8, pos : 8, msk : 16;
} dp[maxd][maxn][maxn];
int main() {
	int T = 1;
	scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		int n;
		static int a[maxn], s[maxd], ord[maxd];
		scanf("%d", &n);
		int all = (1 << n) - 1;
		for(int i = 0; i < n; ++i)
			scanf("%d", a + i);
		s[0] = ord[0] = 0;
		for(int i = 1; i <= all; ++i) {
			for(int j = 0; j < n; ++j)
				if((i >> j) & 1) {
					s[i] = s[i ^ (1 << j)] + a[j];
					break;
				}
			ord[i] = i;
		}
		sort(ord, ord + all + 1, [&](int const &u, int const &v) {
			return s[u] < s[v];
		});
		for(int i = 0; i <= all; ++i)
			for(int j = 0; j < n; ++j)
				sz[i][j] = 0;
		for(int t = 1; t <= all; ++t) {
			int msk = ord[t];
			for(int i = 0; i < n; ++i)
				if(((msk >> i) & 1) && !sz[msk][i])
					dp[msk][i][sz[msk][i]++] = (Info){1, i, msk};
			int rem = all ^ msk;
			for(int pre = rem; pre > 0; pre = (pre - 1) & rem) {
				Info best = (Info){0, 0, msk};
				for(int i = 0; i < n; ++i)
					if((msk >> i) & 1) {
						int &tot = sz[msk | pre][i];
						Info *F = dp[msk | pre][i];
						if(s[best.msk] < s[msk] && (!tot || F[tot - 1].val <= best.val)) {
							tot -= tot > 0 && s[F[tot - 1].msk] == s[msk];
							F[tot++] = (Info){best.val + 1, best.pos, msk};
						}
					} else {
						int &tot = sz[pre][i];
						Info *F = dp[pre][i];
						int idx = tot > 0 && s[F[tot - 1].msk] == s[msk] ? tot - 2 : tot - 1;
						if(idx >= 0 && best.val < F[idx].val) {
							best = F[idx];
							best.pos = i;
						}
					}
			}
		}
		int pos = 0, rem = all;
		Info best = (Info){1, 0, all};
		static int idx[maxn];
		for(int i = 0; i < n; ++i) {
			int &tot = sz[all][i];
			Info *F = dp[all][i];
			if(tot > 0 && best.val < F[tot - 1].val) {
				best = F[tot - 1];
				pos = i;
			}
			idx[i] = i;
		}
		printf("%d\n", n - best.val);
		while(rem > 0) {
			int msk = best.msk;
			for(int i = 0; i < n; ++i)
				if(i != pos && ((msk >> i) & 1)) {
					printf("%d %d\n", idx[i] + 1, idx[pos] + 1);
					for(int j = i + 1; j < n; ++j)
						--idx[j];
				}
			pos = best.pos;
			rem ^= msk;
			if(!rem)
				break;
			int &tot = sz[rem][pos];
			Info *F = dp[rem][pos];
			for( ; tot > 0 && s[F[tot - 1].msk] >= s[msk]; --tot);
			assert(tot > 0);
			best = F[tot - 1];
		}
	}
	return 0;
}