#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef long double DB;
const int maxn = (int)3e5 + 1, maxd = 11, maxv = (int)1e9, mod[2] = {(int)1e9 + 7, (int)1e9 + 9};
const DB eps = 1e-9;
struct Hash {
	int val[2];
	bool operator == (Hash const &t) const {
		return val[0] == t.val[0] && val[1] == t.val[1];
	}
	Hash operator + (Hash const &t) const {
		int res[2] = {val[0] + t.val[0], val[1] + t.val[1]};
		return (Hash){{res[0] < mod[0] ? res[0] : res[0] - mod[0], res[1] < mod[1] ? res[1] : res[1] - mod[1]}};
	}
	Hash operator - (Hash const &t) const {
		int res[2] = {val[0] - t.val[0], val[1] - t.val[1]};
		return (Hash){{res[0] < 0 ? res[0] + mod[0] : res[0], res[1] < 0 ? res[1] + mod[1] : res[1]}};
	}
	Hash operator * (Hash const &t) const {
		return (Hash){{(int)((LL)val[0] * t.val[0] % mod[0]), (int)((LL)val[1] * t.val[1] % mod[1])}};
	}
} ;
const Hash ZERO = (Hash){{0, 0}}, ONE = (Hash){{1, 1}};
int t, n, m, pL[maxn], pR[maxn], p[maxn][maxd], seq[2][maxn];
Hash BASE, pw[maxn], hh[2][maxn];
DB sum[maxn];
int main() {
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		scanf("%d%d", &n, &m);
		BASE = (Hash){{n + 1, n + 1}};
		pw[0] = ONE;
		hh[0][0] = hh[1][0] = ZERO;
		sum[0] = 0;
		for(int i = 1; i <= n; ++i) {
			scanf("%d%d", pL + i, pR + i);
			int mx = pL[i];
			for(int j = pL[i], *pp = p[i] - pL[i]; j <= pR[i]; ++j) {
				scanf("%d", pp + j);
				if(pp[mx] < pp[j])
					mx = j;
			}
			seq[0][i] = mx;
			pw[i] = pw[i - 1] * BASE;
			hh[0][i] = hh[0][i - 1] * BASE + (Hash){{mx, mx}};
			sum[i] = sum[i - 1] + log(p[i][mx - pL[i]]) - log(maxv);
		}
		for(int i = 1; i <= m; ++i) {
			scanf("%d", seq[1] + i); 
			hh[1][i] = hh[1][i - 1] * BASE + (Hash){{seq[1][i], seq[1][i]}};
		}
		printf("Case #%d:\n", Case);
		for(int i = 1; i <= n - m + 1; ++i) {
			int len = 0;
			DB pr = 1, epr = 0;
			while(len < m && pr >= eps)
				if(seq[0][i + len] == seq[1][len + 1]) {
					int L = 1, R = m - len;
					while(L < R) {
						int M = (L + R + 1) >> 1;
						Hash lft = hh[0][i + len + M - 1] - hh[0][i + len - 1] * pw[M];
						Hash rht = hh[1][len + M] - hh[1][len] * pw[M];
						if(lft == rht)
							L = M;
						else
							R = M - 1;
					}
					epr += sum[i + len + L - 1] - sum[i + len - 1];
					len += L;
				} else {
					if(pL[i + len] <= seq[1][len + 1] && seq[1][len + 1] <= pR[i + len]) {
						pr *= (DB)p[i + len][seq[1][len + 1] - pL[i + len]] / maxv;
					} else {
						pr = 0;
					}
					++len;
				}
			printf("%.20f\n", (double)(pr * exp(epr)));
		}
	}
	return 0;
} 
